namespace NumbatLogic
{
	class gsServerClient
	{
		public void Send(gsServerRoom pRoom, uint nMessageTypeHash, gsBlob pBlob)
		{
			gsBlob pSendBlob = new gsBlob();
			uint nSyncId = __nLastSyncId++;
			pSendBlob.PackBool(false);
			pSendBlob.PackUint32(nSyncId);
			pSendBlob.PackUint32(pRoom == null ? 0 : pRoom.__nRoomId);
			pSendBlob.PackUint32(nMessageTypeHash);
			pSendBlob.PackBlob(pBlob);
			__pClientSocket.Send(pSendBlob);
		}

		public virtual void OnInitialJoin()
		{
		}

		public gsServerRoom GetRoomByRoomId(uint nRoomId)
		{
			for (int i = 0; i < __pRoomVector.GetSize(); i++)
			{
				gsServerRoom pRoom = __pRoomVector.Get(i);
				if (pRoom.__nRoomId == nRoomId)
					return pRoom;
			}
			return null;
		}

		public void SyncRespond(uint nSyncId, byte nResult, bool bAwaitRoomChange, gsBlob pBlob)
		{
			gsBlob pRespondBlob = new gsBlob();
			pRespondBlob.PackBool(true);
			pRespondBlob.PackUint32(nSyncId);
			pRespondBlob.PackUint8(nResult);
			pRespondBlob.PackBool(bAwaitRoomChange);
			if (pBlob != null)
			{
				pRespondBlob.PackBool(true);
				pRespondBlob.PackBlob(pBlob);
			}
			else
			{
				pRespondBlob.PackBool(false);
			}
			__pClientSocket.Send(pRespondBlob);
		}

		public uint __nClientId;
		public gsServer __pServer;
		public gsClientSocket __pClientSocket;
		public gsClient.State __eState;
		public Vector<gsServerRoom> __pRoomVector;
		public uint __nLastSyncId;
		public gsServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer)
		{
			__nClientId = nClientId;
			__pServer = pServer;
			__pClientSocket = pClientSocket;
			__eState = gsClient.State.CONNECT;
			__pRoomVector = new Vector<gsServerRoom>();
		}

		public void __Update()
		{
			__pClientSocket.Update();
			switch (__eState)
			{
				case gsClient.State.CONNECT:
				{
					__eState = gsClient.State.HANDSHAKE;
					break;
				}

				case gsClient.State.HANDSHAKE:
				{
					gsBlob pReceiveBlob = __pClientSocket.Receive();
					if (pReceiveBlob != null)
					{
						ushort nMagic = 0;
						ushort nVersion = 0;
						byte nAuthMode = 0;
						if (pReceiveBlob.UnpackUint16(ref nMagic) && pReceiveBlob.UnpackUint16(ref nVersion) && pReceiveBlob.UnpackUint8(ref nAuthMode))
						{
							if (nMagic == gsClient.MAGIC_WORD && nVersion == __pServer.__nVersion)
							{
								if (nAuthMode == 0)
								{
									InternalString sName = new InternalString("");
									InternalString sPassword = new InternalString("");
									if (pReceiveBlob.UnpackInternalString(sName))
									{
										if (pReceiveBlob.UnpackInternalString(sPassword))
										{
											gsBlob pSendBlob = new gsBlob();
											pSendBlob.PackUint16(gsClient.MAGIC_WORD);
											pSendBlob.PackUint16(__pServer.__nVersion);
											pSendBlob.PackBool(true);
											pSendBlob.PackUint32(__nClientId);
											__pClientSocket.Send(pSendBlob);
											__eState = gsClient.State.CONNECTED;
											OnInitialJoin();
											break;
										}
									}
								}
							}
						}
						{
							Console.Log("Bad handshake, disconnecting");
							gsBlob pResponseBlob = new gsBlob();
							pResponseBlob.PackUint8((byte)(gsError.Error.BAD_HANDSHAKE));
							__pClientSocket.Disconnect();
							return;
						}
					}
					else
					{
					}
					break;
				}

				case gsClient.State.CONNECTED:
				{
					gsBlob pReceiveBlob = __pClientSocket.Receive();
					if (pReceiveBlob != null)
					{
						uint nSyncId = 0;
						uint nLastSyncId = 0;
						uint nRoomId = 0;
						uint nSyncType = 0;
						gsBlob pSyncBlob = new gsBlob();
						if (pReceiveBlob.UnpackUint32(ref nSyncId) && pReceiveBlob.UnpackUint32(ref nLastSyncId) && pReceiveBlob.UnpackUint32(ref nRoomId) && pReceiveBlob.UnpackUint32(ref nSyncType) && pReceiveBlob.UnpackBlob(pSyncBlob))
						{
							if (nRoomId > 0)
							{
								gsServerRoom pRoom = GetRoomByRoomId(nRoomId);
								if (pRoom == null)
								{
									ErrorDisconnect("Bad room");
									return;
								}
								pRoom.OnSync(nSyncId, nSyncType, pSyncBlob, this);
							}
							else
							{
							}
						}
						else
						{
							Assert.Plz(false);
						}
					}
					break;
				}

				case gsClient.State.DISCONNECTED:
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

		public void ErrorDisconnect(string sxErrorMessage)
		{
			Console.Log("Error disconnect");
			Console.Log(sxErrorMessage);
			__pClientSocket.Disconnect();
		}

		~gsServerClient()
		{
		}

	}
}

