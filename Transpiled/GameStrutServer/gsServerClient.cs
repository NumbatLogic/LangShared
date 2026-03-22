#line 1 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
namespace NumbatLogic
{
	class gsServerClient
	{
		public void Send(gsServerRoom pRoom, uint nMessageTypeHash, gsBlob pBlob)
		{
			gsBlob pSendBlob = new gsBlob();
#line 9 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
			uint nSyncId = __nLastSyncId++;
#line 11 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
			pSendBlob.PackBool(false);
			pSendBlob.PackUint32(nSyncId);
			pSendBlob.PackUint32(pRoom == null ? 0 : pRoom.__nRoomId);
			pSendBlob.PackUint32(nMessageTypeHash);
			pSendBlob.PackBlob(pBlob);
#line 17 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
			__pClientSocket.Send(pSendBlob);
		}

#line 23 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
		public virtual void OnInitialJoin()
		{
		}

#line 30 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
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

#line 43 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
		public void SyncRespond(uint nSyncId, byte nResult, gsSync.Response eResponse, gsBlob pBlob)
		{
			gsBlob pRespondBlob = new gsBlob();
#line 47 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
			pRespondBlob.PackBool(true);
			pRespondBlob.PackUint32(nSyncId);
			pRespondBlob.PackUint8(nResult);
			pRespondBlob.PackUint8((byte)(eResponse));
#line 52 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
			if (pBlob != null)
			{
				pRespondBlob.PackBool(true);
				pRespondBlob.PackBlob(pBlob);
			}
			else
			{
				pRespondBlob.PackBool(false);
			}
#line 62 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
			__pClientSocket.Send(pRespondBlob);
		}

#line 87 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
		public uint __nClientId;
		public gsServer __pServer;
		public gsClientSocket __pClientSocket;
		public gsClient.State __eState;
		public Vector<gsServerRoom> __pRoomVector;
#line 93 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
		public uint __nLastSyncId;
#line 95 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
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
#line 108 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
			switch (__eState)
			{
				case gsClient.State.CONNECT:
				{
					__eState = gsClient.State.HANDSHAKE;
					break;
				}

				case gsClient.State.HANDSHAKE:
				{
#line 117 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
					gsBlob pReceiveBlob = __pClientSocket.Receive();
					if (pReceiveBlob != null)
					{
						ushort nMagic = 0;
						ushort nVersion = 0;
						byte nAuthMode = 0;
#line 124 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
						if (pReceiveBlob.UnpackUint16(ref nMagic) && pReceiveBlob.UnpackUint16(ref nVersion) && pReceiveBlob.UnpackUint8(ref nAuthMode))
						{
							if (nMagic == gsClient.MAGIC_WORD && nVersion == __pServer.__nVersion)
							{
#line 129 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
								if (nAuthMode == 0)
								{
									InternalString sName = new InternalString("");
									InternalString sPassword = new InternalString("");
#line 134 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
									if (pReceiveBlob.UnpackInternalString(sName))
									{
										if (pReceiveBlob.UnpackInternalString(sPassword))
										{
#line 140 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
											gsBlob pSendBlob = new gsBlob();
											pSendBlob.PackUint16(gsClient.MAGIC_WORD);
											pSendBlob.PackUint16(__pServer.__nVersion);
											pSendBlob.PackBool(true);
											pSendBlob.PackUint32(__nClientId);
											__pClientSocket.Send(pSendBlob);
#line 147 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
											__eState = gsClient.State.CONNECTED;
#line 149 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
											OnInitialJoin();
											break;
										}
									}
								}
							}
						}
						{
#line 158 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
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
#line 169 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
					break;
				}

				case gsClient.State.CONNECTED:
				{
#line 173 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
					gsBlob pReceiveBlob = __pClientSocket.Receive();
					if (pReceiveBlob != null)
					{
						uint nSyncId = 0;
						uint nLastSyncId = 0;
						uint nRoomId = 0;
						uint nSyncType = 0;
						gsBlob pSyncBlob = new gsBlob();
#line 182 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
						if (pReceiveBlob.UnpackUint32(ref nSyncId) && pReceiveBlob.UnpackUint32(ref nLastSyncId) && pReceiveBlob.UnpackUint32(ref nRoomId) && pReceiveBlob.UnpackUint32(ref nSyncType) && pReceiveBlob.UnpackBlob(pSyncBlob))
						{
#line 188 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
							if (nRoomId > 0)
							{
								gsServerRoom pRoom = GetRoomByRoomId(nRoomId);
#line 192 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
								if (pRoom == null)
								{
									ErrorDisconnect("Bad room");
									return;
								}
								gsServerRoom_SyncHandler pHandler = pRoom.__GetSyncHandler(nSyncType);
								if (pHandler == null)
								{
									ErrorDisconnect("No handler for room sync");
									return;
								}
								pHandler.__pHandler(pRoom, nSyncId, nSyncType, pSyncBlob, this);
							}
							else
							{
							}
						}
						else
						{
#line 213 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
							Assert.Plz(false);
						}
					}
					break;
				}

				case gsClient.State.DISCONNECTED:
				{
#line 220 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
					break;
				}

				default:
				{
#line 224 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
					Assert.Plz(false);
					break;
				}

			}
		}

#line 230 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
		public void ErrorDisconnect(string sxErrorMessage)
		{
			Console.Log("Error disconnect");
			Console.Log(sxErrorMessage);
#line 240 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
			__pClientSocket.Disconnect();
		}

#line 3 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
		~gsServerClient()
		{
		}

	}
}

