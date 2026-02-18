namespace NumbatLogic
{
	class gsClient_SyncHandler
	{
		public delegate void SyncHandler(gsClient pClient, uint nSyncId, gsBlob pMessageBlob);
		public uint __nHash;
		public SyncHandler __pHandler;
		public gsClient_SyncHandler(uint nHash, SyncHandler pHandler)
		{
			__nHash = nHash;
			__pHandler = pHandler;
		}

	}
	class gsClient
	{
		public enum State
		{
			CONNECT,
			HANDSHAKE,
			CONNECTED,
			DISCONNECTED,
			ERRORED,
		}

		public gsClient(string sxAddress, ushort nPort, ushort nVersion)
		{
			__pRoomVector = new OwnedVector<gsClientRoom>();
			__pClientSocket = new gsClientSocket();
			__pClientSocket.Connect(sxAddress, nPort);
			__nVersion = nVersion;
			__eState = State.CONNECT;
			__pSyncInnerVector = new OwnedVector<gsSyncInner>();
			__pSyncHandlerVector = new OwnedVector<gsClient_SyncHandler>();
			RegisterHandler(__ROOM_JOIN_HASH, __OnRoomJoin);
			RegisterHandler(__ROOM_LEAVE_HASH, __OnRoomLeave);
		}

		~gsClient()
		{
			__pClientSocket.Disconnect();
		}

		public void Update()
		{
			__pClientSocket.Update();
			switch (__eState)
			{
				case State.CONNECT:
				{
					if (!__pClientSocket.Pending())
					{
						__eState = State.HANDSHAKE;
						gsBlob pSendBlob = new gsBlob();
						pSendBlob.PackUint16(MAGIC_WORD);
						pSendBlob.PackUint16(__nVersion);
						pSendBlob.PackUint8(0);
						InternalString sName = new InternalString("cliffya");
						pSendBlob.PackInternalString(sName);
						InternalString sPassword = new InternalString("password");
						pSendBlob.PackInternalString(sPassword);
						__pClientSocket.Send(pSendBlob);
					}
					break;
				}

				case State.HANDSHAKE:
				{
					gsBlob pReceiveBlob = __pClientSocket.Receive();
					if (pReceiveBlob != null)
					{
						const int INITIAL_SIZE = 2 + 2 + 1 + 4;
						if (pReceiveBlob.GetSize() == INITIAL_SIZE)
						{
							ushort nMagic = 0;
							ushort nVersion = 0;
							bool bSuccess = false;
							if (pReceiveBlob.UnpackUint16(ref nMagic) && pReceiveBlob.UnpackUint16(ref nVersion) && pReceiveBlob.UnpackBool(ref bSuccess))
							{
								if (nMagic == gsClient.MAGIC_WORD && bSuccess)
								{
									if (!pReceiveBlob.UnpackUint32(ref __nClientId))
										Assert.Plz(false);
									__eState = State.CONNECTED;
									break;
								}
							}
						}
						Console.Log("bad handshake?");
						Assert.Plz(false);
					}
					break;
				}

				case State.CONNECTED:
				{
					gsBlob pReceiveBlob = __pClientSocket.Receive();
					if (pReceiveBlob != null)
					{
						bool bSyncResponse = false;
						uint nSyncId = 0;
						if (!pReceiveBlob.UnpackBool(ref bSyncResponse) || !pReceiveBlob.UnpackUint32(ref nSyncId))
						{
							Console.Log("bad blob?");
							Assert.Plz(false);
						}
						if (bSyncResponse)
						{
							gsSyncInner pSyncInner = GetSyncInnerBySyncId(nSyncId);
							Assert.Plz(pSyncInner != null);
							byte nResult = 0;
							if (!pReceiveBlob.UnpackUint8(ref nResult))
								Assert.Plz(false);
							byte nResponseRaw = 0;
							if (!pReceiveBlob.UnpackUint8(ref nResponseRaw))
								Assert.Plz(false);
							gsSync.Response eResponse = (gsSync.Response)(nResponseRaw);
							if (nResult == gsSync.RESULT_SUCCESS && eResponse != pSyncInner.__eResponse)
							{
								ErrorDisconnect("Response expectation mismatch");
								return;
							}
							bool bHasBlob = false;
							if (!pReceiveBlob.UnpackBool(ref bHasBlob))
								Assert.Plz(false);
							gsBlob pSyncBlob = null;
							if (bHasBlob)
							{
								pSyncBlob = new gsBlob();
								if (!pReceiveBlob.UnpackBlob(pSyncBlob))
									Assert.Plz(false);
							}
							if (eResponse != gsSync.Response.EXPECT_ROOM_CHANGE)
								pSyncInner.__bComplete = true;
							pSyncInner.__nResult = nResult;
							if (pSyncInner.__pSync != null)
								pSyncInner.__pSync.OnComplete(nResult, pSyncBlob);
						}
						else
						{
							uint nRoomId = 0;
							uint nMessageType = 0;
							if (!pReceiveBlob.UnpackUint32(ref nRoomId) || !pReceiveBlob.UnpackUint32(ref nMessageType))
								Assert.Plz(false);
							gsBlob pMessageBlob = new gsBlob();
							if (!pReceiveBlob.UnpackBlob(pMessageBlob))
								Assert.Plz(false);
							if (nRoomId == 0)
							{
								gsClient_SyncHandler pHandler = __GetSyncHandler(nMessageType);
								if (pHandler == null)
								{
									ErrorDisconnect("No handler registered for sync message");
									return;
								}
								pHandler.__pHandler(this, nSyncId, pMessageBlob);
							}
							else
							{
								gsClientRoom pRoom = GetRoomByRoomId(nRoomId);
								if (pRoom == null)
								{
									ErrorDisconnect("Bad room id");
									return;
								}
								gsClientRoom_SyncHandler pHandler = pRoom.__GetSyncHandler(nMessageType);
								if (pHandler == null)
								{
									ErrorDisconnect("No handler registered for room sync message");
									return;
								}
								pHandler.__pHandler(this, pRoom, nSyncId, pMessageBlob);
							}
						}
					}
					int i = 0;
					while (i < __pSyncInnerVector.GetSize())
					{
						gsSyncInner pSyncInner = __pSyncInnerVector.Get(i);
						if (pSyncInner.__eResponse == gsSync.Response.EXPECT_ROOM_CHANGE && !pSyncInner.__bComplete)
						{
							int j = 0;
							for (j = 0; j < __pRoomVector.GetSize(); j++)
							{
								gsClientRoom pRoom = __pRoomVector.Get(j);
								if (pRoom.__nRoomId == pSyncInner.__nRoomId)
									break;
							}
							if (j == __pRoomVector.GetSize())
							{
								pSyncInner.__eResponse = gsSync.Response.NO_RESPONSE;
								pSyncInner.__bComplete = true;
							}
						}
						if (pSyncInner.__bComplete && pSyncInner.__pSync == null)
						{
							__pSyncInnerVector.Erase(i);
							continue;
						}
						i++;
					}
					break;
				}

				case State.DISCONNECTED:
				{
					break;
				}

				case State.ERRORED:
				{
					break;
				}

				default:
				{
					Assert.Plz(false);
					break;
				}

			}
		}

		public static void __OnRoomJoin(gsClient pClient, uint nSyncId, gsBlob pMessageBlob)
		{
			uint nRoomId = 0;
			uint nRoomType = 0;
			bool bPrimary = false;
			if (pMessageBlob.UnpackUint32(ref nRoomId) && pMessageBlob.UnpackUint32(ref nRoomType) && pMessageBlob.UnpackBool(ref bPrimary))
			{
				gsBlob pJoinBlob = new gsBlob();
				if (pMessageBlob.UnpackBlob(pJoinBlob))
				{
					gsClientRoom pRoom = pClient.OnRoomJoin(nRoomId, nRoomType, bPrimary, pJoinBlob);
					if (pRoom != null)
					{
						NumbatLogic.gsClientRoom __3933567651 = pRoom;
						pRoom = null;
						pClient.__pRoomVector.PushBack(__3933567651);
						return;
					}
				}
			}
			pClient.ErrorDisconnect("Room join failed");
		}

		public static void __OnRoomLeave(gsClient pClient, uint nSyncId, gsBlob pMessageBlob)
		{
			uint nLeaveRoomId = 0;
			uint nLeaveRoomType = 0;
			if (pMessageBlob.UnpackUint32(ref nLeaveRoomId) && pMessageBlob.UnpackUint32(ref nLeaveRoomType))
			{
				for (int i = 0; i < pClient.__pRoomVector.GetSize(); i++)
				{
					if (pClient.__pRoomVector.Get(i).__nRoomId == nLeaveRoomId)
					{
						pClient.__pRoomVector.Erase(i);
						return;
					}
				}
			}
			pClient.ErrorDisconnect("Room leave failed");
		}

		public void RegisterHandler(uint nMessageType, gsClient_SyncHandler.SyncHandler pHandler)
		{
			if (__GetSyncHandler(nMessageType) != null)
			{
				Console.Log("Sync handler hash already registered!");
				Assert.Plz(false);
			}
			__pSyncHandlerVector.PushBack(new gsClient_SyncHandler(nMessageType, pHandler));
		}

		public gsClient_SyncHandler __GetSyncHandler(uint nMessageType)
		{
			for (int i = 0; i < __pSyncHandlerVector.GetSize(); i++)
			{
				gsClient_SyncHandler pInfo = __pSyncHandlerVector.Get(i);
				if (pInfo.__nHash == nMessageType)
					return pInfo;
			}
			return null;
		}

		public void SyncSend(gsSync pSync, string sxSyncType, gsBlob pBlob, gsSync.Response eResponse, gsClientRoom pRoom)
		{
			gsSyncInner pSyncInner = new gsSyncInner(pSync, ++__nLastSyncId, sxSyncType, pRoom, this);
			pSyncInner.__eResponse = eResponse;
			gsBlob pSendBlob = new gsBlob();
			pSendBlob.PackUint32(pSyncInner.__nSyncId);
			pSendBlob.PackUint32(0);
			if (pRoom != null)
				pSendBlob.PackUint32(pRoom.__nRoomId);
			else
				pSendBlob.PackUint32(0);
			pSendBlob.PackUint32(pSyncInner.__nSyncType);
			pSendBlob.PackBlob(pBlob);
			__pClientSocket.Send(pSendBlob);
			pSyncInner.__pSync.__pSyncInner = pSyncInner;
			if (pSyncInner.__eResponse == gsSync.Response.NO_RESPONSE)
				pSyncInner.__bComplete = true;
			NumbatLogic.gsSyncInner __3139231654 = pSyncInner;
			pSyncInner = null;
			__pSyncInnerVector.PushBack(__3139231654);
		}

		public bool GetPending()
		{
			if (__eState == State.ERRORED)
				return false;
			if (__pClientSocket.Pending())
				return true;
			if (!__pClientSocket.GetConnected())
				return false;
			for (int i = 0; i < __pSyncInnerVector.GetSize(); i++)
			{
				gsSyncInner pSyncInner = __pSyncInnerVector.Get(i);
				if (!pSyncInner.__bComplete)
					return true;
			}
			return false;
		}

		public bool HasActiveSync()
		{
			for (int i = 0; i < __pSyncInnerVector.GetSize(); i++)
			{
				gsSyncInner pSyncInner = __pSyncInnerVector.Get(i);
				if (!pSyncInner.__bComplete)
					return true;
			}
			return false;
		}

		public bool HasActiveSyncByRoom(gsClientRoom pRoom)
		{
			for (int i = 0; i < __pSyncInnerVector.GetSize(); i++)
			{
				gsSyncInner pSyncInner = __pSyncInnerVector.Get(i);
				if (pSyncInner.__nRoomId == pRoom.__nRoomId && !pSyncInner.__bComplete)
					return true;
			}
			return false;
		}

		public virtual gsClientRoom OnRoomJoin(uint nRoomId, uint nRoomTypeHash, bool bPrimary, gsBlob pJoinBlob)
		{
			return new gsClientRoom(nRoomId, null, nRoomTypeHash, bPrimary, this);
		}

		public const ushort MAGIC_WORD = 619;
		public OwnedVector<gsClientRoom> __pRoomVector;
		public gsClientSocket __pClientSocket;
		public ushort __nVersion;
		public uint __nClientId;
		public uint __nLastSyncId;
		public OwnedVector<gsSyncInner> __pSyncInnerVector;
		public OwnedVector<gsClient_SyncHandler> __pSyncHandlerVector;
		public State __eState;
		public InternalString __sErrorMessage;
		public static uint __ROOM_JOIN_HASH = 1895086341;
		public static uint __ROOM_LEAVE_HASH = 938124572;
		public gsClientRoom GetRoomByRoomId(uint nRoomId)
		{
			for (int i = 0; i < __pRoomVector.GetSize(); i++)
			{
				gsClientRoom pRoom = __pRoomVector.Get(i);
				if (pRoom.__nRoomId == nRoomId)
					return pRoom;
			}
			return null;
		}

		public void ErrorDisconnect(string sxErrorMessage)
		{
			Console.Log("Error disconnect");
			Console.Log(sxErrorMessage);
			__sErrorMessage = new InternalString(sxErrorMessage);
			__eState = State.ERRORED;
			__pClientSocket.Disconnect();
		}

		public string GetErrorMessage()
		{
			Assert.Plz(__eState == State.ERRORED);
			return __sErrorMessage.GetExternalString();
		}

		public gsSyncInner GetSyncInnerBySyncId(uint nSyncId)
		{
			for (int i = 0; i < __pSyncInnerVector.GetSize(); i++)
			{
				gsSyncInner pSyncInner = __pSyncInnerVector.Get(i);
				if (nSyncId == pSyncInner.__nSyncId)
					return pSyncInner;
			}
			return null;
		}

	}
}

