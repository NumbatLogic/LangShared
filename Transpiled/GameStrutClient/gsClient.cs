namespace NumbatLogic
{
	class gsClient
	{
		public enum State
		{
			CONNECT,
			HANDSHAKE,
			CONNECTED,
			DISCONNECTED,
		}

		public gsClient(string sxAddress, ushort nPort, ushort nVersion)
		{
			__pRoomVector = new OwnedVector<gsClientRoom>();
			__pClientSocket = new gsClientSocket();
			__pClientSocket.Connect(sxAddress, nPort);
			__nVersion = nVersion;
			__eState = State.CONNECT;
			__pSyncInnerVector = new OwnedVector<gsSyncInner>();
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
							bool bAwaitRoomChange = false;
							if (!pReceiveBlob.UnpackBool(ref bAwaitRoomChange))
								Assert.Plz(false);
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
							pSyncInner.OnComplete(nResult, bAwaitRoomChange, pSyncBlob);
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
								if (nMessageType == __ROOM_JOIN_HASH)
								{
									uint nRoomType = 0;
									bool bPrimary = false;
									if (!pMessageBlob.UnpackUint32(ref nRoomId) || !pMessageBlob.UnpackUint32(ref nRoomType) || !pMessageBlob.UnpackBool(ref bPrimary))
										Assert.Plz(false);
									gsBlob pJoinBlob = new gsBlob();
									if (!pMessageBlob.UnpackBlob(pJoinBlob))
										Assert.Plz(false);
									gsClientRoom pRoom = OnRoomJoin(nRoomId, nRoomType, bPrimary, pJoinBlob);
									Assert.Plz(pRoom != null);
									NumbatLogic.gsClientRoom __3925240554 = pRoom;
									pRoom = null;
									__pRoomVector.PushBack(__3925240554);
								}
								else
									if (nMessageType == __ROOM_LEAVE_HASH)
									{
										uint nLeaveRoomId = 0;
										uint nLeaveRoomType = 0;
										if (!pMessageBlob.UnpackUint32(ref nLeaveRoomId) || !pMessageBlob.UnpackUint32(ref nLeaveRoomType))
											Assert.Plz(false);
										bool bRemoved = false;
										for (int i = 0; i < __pRoomVector.GetSize(); i++)
										{
											gsClientRoom pRoom = __pRoomVector.Get(i);
											if (pRoom.__nRoomId == nLeaveRoomId)
											{
												__pRoomVector.Erase(i);
												bRemoved = true;
												break;
											}
										}
										Assert.Plz(bRemoved);
									}
									else
									{
										Console.Log("unknown hash");
										Assert.Plz(false);
									}
							}
						}
					}
					int i = 0;
					while (i < __pSyncInnerVector.GetSize())
					{
						gsSyncInner pSyncInner = __pSyncInnerVector.Get(i);
						if (pSyncInner.__bAwaitRoomChange && !pSyncInner.__bComplete)
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
								pSyncInner.__bAwaitRoomChange = false;
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

				default:
				{
					Assert.Plz(false);
					break;
				}

			}
		}

		public delegate void CompleteCallback();
		public void SyncSend(gsSync pSync, string sxSyncType, gsBlob pBlob, bool mayChangeRoom, gsClientRoom pRoom)
		{
			gsSyncInner pSyncInner = new gsSyncInner(pSync, ++__nLastSyncId, sxSyncType, pRoom, this);
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
			NumbatLogic.gsSyncInner __3131101350 = pSyncInner;
			pSyncInner = null;
			__pSyncInnerVector.PushBack(__3131101350);
		}

		public bool GetPending()
		{
			if (__pClientSocket.Pending())
				return true;
			for (int i = 0; i < __pSyncInnerVector.GetSize(); i++)
			{
				gsSyncInner pSyncInner = __pSyncInnerVector.Get(i);
				if (!pSyncInner.__bComplete)
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
		public State __eState;
		public static uint __ROOM_JOIN_HASH = 1895086341;
		public static uint __ROOM_LEAVE_HASH = 938124572;
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

