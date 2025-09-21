namespace NumbatLogic
{
	class gsServerClient
	{
		public void Send(gsServerRoom pRoom, string sxMessageType, gsBlob pBlob)
		{
			gsBlob pSendBlob = new gsBlob();
			uint nSyncId = __nLastSyncId++;
			int nMessageTypeHash = ExternalString.GetChecksum(sxMessageType);
			pSendBlob.PackBool(false);
			pSendBlob.PackUint32(nSyncId);
			pSendBlob.PackUint32(pRoom == null ? 0 : pRoom.__nRoomId);
			pSendBlob.PackInt32(nMessageTypeHash);
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

		public void SyncRespond(uint nSyncId, gsBlob pBlob)
		{
			gsBlob pRespondBlob = new gsBlob();
			pRespondBlob.PackBool(true);
			pRespondBlob.PackUint32(nSyncId);
			pRespondBlob.PackBlob(pBlob);
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
						ushort nMagic;
						ushort nVersion;
						byte nAuthMode;
						if (pReceiveBlob.UnpackUint16(nMagic) && pReceiveBlob.UnpackUint16(nVersion) && pReceiveBlob.UnpackUint8(nAuthMode))
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
							pResponseBlob.PackUint8(gsError.Error.BAD_HANDSHAKE);
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
						uint nSyncId;
						uint nLastSyncId;
						uint nRoomId;
						int nSyncType;
						gsBlob pSyncBlob = new gsBlob();
						if (pReceiveBlob.UnpackUint32(nSyncId) && pReceiveBlob.UnpackUint32(nLastSyncId) && pReceiveBlob.UnpackUint32(nRoomId) && pReceiveBlob.UnpackInt32(nSyncType) && pReceiveBlob.UnpackBlob(pSyncBlob))
						{
							if (nRoomId > 0)
							{
								gsServerRoom pRoom = GetRoomByRoomId(nRoomId);
								if (!pRoom)
									Assert.Plz(false);
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
				}

			}
		}

		~gsServerClient()
		{
		}

	}
}

