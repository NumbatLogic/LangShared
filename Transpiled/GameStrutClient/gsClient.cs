#line 1 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
namespace NumbatLogic
{
	class gsClient_SyncHandler
	{
		public delegate void SyncHandler(gsClient pClient, uint nSyncId, gsBlob pMessageBlob);
#line 7 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public uint __nHash;
		public SyncHandler __pHandler;
#line 10 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
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

#line 27 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public gsClient(string sxAddress, ushort nPort, ushort nVersion)
		{
			__pRoomVector = new OwnedVector<gsClientRoom>();
#line 31 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
			__pClientSocket = new gsClientSocket();
			__pClientSocket.Connect(sxAddress, nPort);
			__nVersion = nVersion;
			__eState = State.CONNECT;
			__pSyncInnerVector = new OwnedVector<gsSyncInner>();
			__pSyncHandlerVector = new OwnedVector<gsClient_SyncHandler>();
#line 38 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
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
#line 51 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
			switch (__eState)
			{
				case State.CONNECT:
				{
					if (!__pClientSocket.Pending())
					{
						__eState = State.HANDSHAKE;
#line 59 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						gsBlob pSendBlob = new gsBlob();
						pSendBlob.PackUint16(MAGIC_WORD);
						pSendBlob.PackUint16(__nVersion);
#line 63 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						pSendBlob.PackUint8(0);
#line 65 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						InternalString sName = new InternalString("cliffya");
						pSendBlob.PackInternalString(sName);
#line 68 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						InternalString sPassword = new InternalString("password");
						pSendBlob.PackInternalString(sPassword);
#line 71 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						__pClientSocket.Send(pSendBlob);
					}
					break;
				}

				case State.HANDSHAKE:
				{
#line 77 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
					gsBlob pReceiveBlob = __pClientSocket.Receive();
					if (pReceiveBlob != null)
					{
#line 81 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						const int INITIAL_SIZE = 2 + 2 + 1 + 4;
						if (pReceiveBlob.GetSize() == INITIAL_SIZE)
						{
							ushort nMagic = 0;
							ushort nVersion = 0;
							bool bSuccess = false;
#line 88 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
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
#line 101 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						Console.Log("bad handshake?");
						Assert.Plz(false);
					}
					break;
				}

				case State.CONNECTED:
				{
#line 108 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
					gsBlob pReceiveBlob = __pClientSocket.Receive();
					if (pReceiveBlob != null)
					{
						bool bSyncResponse = false;
						uint nSyncId = 0;
#line 114 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						if (!pReceiveBlob.UnpackBool(ref bSyncResponse) || !pReceiveBlob.UnpackUint32(ref nSyncId))
						{
							Console.Log("bad blob?");
							Assert.Plz(false);
						}
#line 120 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						if (bSyncResponse)
						{
							gsSyncInner pSyncInner = GetSyncInnerBySyncId(nSyncId);
							Assert.Plz(pSyncInner != null);
#line 125 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
							byte nResult = 0;
							if (!pReceiveBlob.UnpackUint8(ref nResult))
								Assert.Plz(false);
#line 129 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
							byte nResponseRaw = 0;
							if (!pReceiveBlob.UnpackUint8(ref nResponseRaw))
								Assert.Plz(false);
							gsSync.Response eResponse = (gsSync.Response)(nResponseRaw);
#line 134 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
							if (nResult == gsSync.RESULT_SUCCESS && eResponse != pSyncInner.__eResponse)
							{
								ErrorDisconnect("Response expectation mismatch");
								return;
							}
#line 140 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
							bool bHasBlob = false;
							if (!pReceiveBlob.UnpackBool(ref bHasBlob))
								Assert.Plz(false);
#line 144 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
							gsBlob pSyncBlob = null;
							if (bHasBlob)
							{
								pSyncBlob = new gsBlob();
								if (!pReceiveBlob.UnpackBlob(pSyncBlob))
									Assert.Plz(false);
							}
#line 152 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
							if (eResponse != gsSync.Response.EXPECT_ROOM_CHANGE)
								pSyncInner.__bComplete = true;
#line 155 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
							pSyncInner.__nResult = nResult;
							if (nResult == gsSync.RESULT_SUCCESS && pSyncInner.__pSync != null)
								pSyncInner.__pSync.OnComplete(nResult, pSyncBlob);
						}
						else
						{
							uint nRoomId = 0;
							uint nMessageType = 0;
#line 164 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
							if (!pReceiveBlob.UnpackUint32(ref nRoomId) || !pReceiveBlob.UnpackUint32(ref nMessageType))
								Assert.Plz(false);
#line 167 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
							gsBlob pMessageBlob = new gsBlob();
							if (!pReceiveBlob.UnpackBlob(pMessageBlob))
								Assert.Plz(false);
#line 171 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
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
#line 200 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
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
#line 214 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
							if (j == __pRoomVector.GetSize())
							{
								pSyncInner.__eResponse = gsSync.Response.NO_RESPONSE;
								pSyncInner.__bComplete = true;
							}
						}
#line 221 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						if (pSyncInner.__bComplete && pSyncInner.__pSync == null)
						{
							__pSyncInnerVector.Erase(i);
							continue;
						}
						i++;
					}
#line 230 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
					break;
				}

				case State.DISCONNECTED:
				{
#line 234 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
					break;
				}

				case State.ERRORED:
				{
#line 238 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
					break;
				}

				default:
				{
#line 242 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
					Assert.Plz(false);
					break;
				}

			}
		}

#line 248 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
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
						NumbatLogic.gsClientRoom __3933567650 = pRoom;
#line 261 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						pRoom = null;
#line 261 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						pClient.__pRoomVector.PushBack(__3933567650);
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
			if (eResponse == gsSync.Response.EXPECT_ROOM_CHANGE)
				Assert.Plz(!HasRoomChangeSyncInFlight(pRoom));
#line 313 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
			gsSyncInner pSyncInner = new gsSyncInner(pSync, ++__nLastSyncId, sxSyncType, pRoom, this);
			pSyncInner.__eResponse = eResponse;
#line 316 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
			gsBlob pSendBlob = new gsBlob();
			pSendBlob.PackUint32(pSyncInner.__nSyncId);
			pSendBlob.PackUint32(0);
			if (pRoom != null)
				pSendBlob.PackUint32(pRoom.__nRoomId);
			else
				pSendBlob.PackUint32(0);
			pSendBlob.PackUint32(pSyncInner.__nSyncType);
			pSendBlob.PackBlob(pBlob);
#line 326 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
			__pClientSocket.Send(pSendBlob);
#line 328 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
			pSyncInner.__pSync.__pSyncInner = pSyncInner;
#line 330 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
			if (pSyncInner.__eResponse == gsSync.Response.NO_RESPONSE)
				pSyncInner.__bComplete = true;
			NumbatLogic.gsSyncInner __3139231656 = pSyncInner;
			pSyncInner = null;
#line 333 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
			__pSyncInnerVector.PushBack(__3139231656);
		}

		public bool GetPending()
		{
			if (__eState == State.ERRORED)
				return false;
#line 341 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
			if (__pClientSocket.Pending())
				return true;
#line 344 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
			if (!__pClientSocket.GetConnected())
				return false;
#line 347 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
			for (int i = 0; i < __pSyncInnerVector.GetSize(); i++)
			{
				gsSyncInner pSyncInner = __pSyncInnerVector.Get(i);
				if (!pSyncInner.__bComplete)
					return true;
			}
#line 354 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
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

		public bool HasRoomChangeSyncInFlight(gsClientRoom pRoom)
		{
			uint nRoomId = pRoom != null ? pRoom.__nRoomId : 0;
			for (int i = 0; i < __pSyncInnerVector.GetSize(); i++)
			{
				gsSyncInner pSyncInner = __pSyncInnerVector.Get(i);
				if (pSyncInner.__eResponse == gsSync.Response.EXPECT_ROOM_CHANGE && !pSyncInner.__bComplete && pSyncInner.__nRoomId == nRoomId)
					return true;
			}
			return false;
		}

		public virtual gsClientRoom OnRoomJoin(uint nRoomId, uint nRoomTypeHash, bool bPrimary, gsBlob pJoinBlob)
		{
			return new gsClientRoom(nRoomId, null, nRoomTypeHash, bPrimary, this);
		}

#line 399 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public const ushort MAGIC_WORD = 619;
#line 401 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public OwnedVector<gsClientRoom> __pRoomVector;
#line 404 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public gsClientSocket __pClientSocket;
		public ushort __nVersion;
#line 407 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public uint __nClientId;
#line 409 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public uint __nLastSyncId;
		public OwnedVector<gsSyncInner> __pSyncInnerVector;
		public OwnedVector<gsClient_SyncHandler> __pSyncHandlerVector;
#line 414 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public State __eState;
		public InternalString __sErrorMessage;
#line 417 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public static uint __ROOM_JOIN_HASH = 1895086341;
		public static uint __ROOM_LEAVE_HASH = 938124572;
#line 422 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
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

