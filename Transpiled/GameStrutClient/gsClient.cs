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
			__eState = CONNECT;
			__pSyncInnerVector = new OwnedVector<gsSyncInner>();
			__ROOM_JOIN_HASH = ExternalString.GetChecksum("__RoomJoin");
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
							ushort nMagic;
							ushort nVersion;
							bool bSuccess;
							if (pReceiveBlob.UnpackUint16(nMagic) && pReceiveBlob.UnpackUint16(nVersion) && pReceiveBlob.UnpackBool(bSuccess))
							{
								if (nMagic == gsClient.MAGIC_WORD && bSuccess)
								{
									if (!pReceiveBlob.UnpackUint32(__nClientId))
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
						bool bSyncResponse;
						uint nSyncId;
						if (!pReceiveBlob.UnpackBool(bSyncResponse) || !pReceiveBlob.UnpackUint32(nSyncId))
						{
							Console.Log("bad blob?");
							Assert.Plz(false);
						}
						if (bSyncResponse)
						{
							gsSyncInner pSyncInner = GetSyncInnerBySyncId(nSyncId);
							Assert.Plz(pSyncInner != null);
							gsBlob pSyncBlob = new gsBlob();
							if (!pReceiveBlob.UnpackBlob(pSyncBlob))
								Assert.Plz(false);
							if (pSyncInner.__pSync != null)
								pSyncInner.OnComplete(pSyncBlob);
						}
						else
						{
							uint nRoomId;
							int nMessageType;
							if (!pReceiveBlob.UnpackUint32(nRoomId) || !pReceiveBlob.UnpackInt32(nMessageType))
								Assert.Plz(false);
							gsBlob pMessageBlob = new gsBlob();
							if (!pReceiveBlob.UnpackBlob(pMessageBlob))
								Assert.Plz(false);
							if (nRoomId == 0)
							{
								if (nMessageType == __ROOM_JOIN_HASH)
								{
									uint nRoomId;
									int nRoomType;
									bool bPrimary;
									if (!pMessageBlob.UnpackUint32(nRoomId) || !pMessageBlob.UnpackInt32(nRoomType) || !pMessageBlob.UnpackBool(bPrimary))
										Assert.Plz(false);
									gsBlob pJoinBlob = new gsBlob();
									if (!pMessageBlob.UnpackBlob(pJoinBlob))
										Assert.Plz(false);
									gsClientRoom pRoom = OnRoomJoin(nRoomId, nRoomType, bPrimary, pJoinBlob);
									Assert.Plz(pRoom != null);
									NumbatLogic.gsClientRoom __3132352023 = pRoom;
									pRoom = null;
									__pRoomVector.PushBack(__3132352023);
								}
								else
								{
									Console.Log("unknown hash");
									Assert.Plz(false);
								}
							}
						}
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
				}

			}
		}

		public delegate void CompleteCallback();
		public void SyncSend(gsSync pSync, string sxSyncType, gsBlob pBlob, bool mayChangeRoom, gsClientRoom pRoom)
		{
			gsSync pOwnedSync = pSync;
			NumbatLogic.gsSync __705409795 = pOwnedSync;
			pOwnedSync = null;
			gsSyncInner pSyncInner = new gsSyncInner(__705409795, ++__nLastSyncId, sxSyncType, pRoom, this);
			gsBlob pSendBlob = new gsBlob();
			pSendBlob.PackUint32(pSyncInner.__nSyncId);
			pSendBlob.PackUint32(0);
			if (pRoom != null)
				pSendBlob.PackUint32(pRoom.__nRoomId);
			else
				pSendBlob.PackUint32(0);
			pSendBlob.PackInt32(pSyncInner.__nSyncType);
			pSendBlob.PackBlob(pBlob);
			__pClientSocket.Send(pSendBlob);
			pSyncInner.__pSync.__pSyncInner = pSyncInner;
			NumbatLogic.gsSyncInner __3933501000 = pSyncInner;
			pSyncInner = null;
			__pSyncInnerVector.PushBack(__3933501000);
		}

		public bool GetPending()
		{
			return __pClientSocket.Pending();
		}

		public virtual gsClientRoom OnRoomJoin(uint nRoomId, int nRoomType, bool bPrimary, gsBlob pJoinBlob)
		{
			return new gsClientRoom(nRoomId, null, nRoomType, bPrimary, this);
		}

		public const ushort MAGIC_WORD = 619;
		public OwnedVector<gsClientRoom> __pRoomVector;
		public gsClientSocket __pClientSocket;
		public ushort __nVersion;
		public uint __nClientId;
		public uint __nLastSyncId;
		public OwnedVector<gsSyncInner> __pSyncInnerVector;
		public State __eState;
		public uint __ROOM_JOIN_HASH;
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

