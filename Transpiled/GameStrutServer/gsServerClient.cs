#line 1 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
	class gsServerClient
	{
#line 6 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public void Send(gsServerRoom pRoom, uint nMessageTypeHash, gsBlob pBlob)
		{
			gsBlob pSendBlob = new gsBlob();
			uint nSyncId = __nLastSyncId++;
#line 12 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			pSendBlob.PackBool(false);
#line 13 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			pSendBlob.PackUint32(nSyncId);
#line 14 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			pSendBlob.PackUint32(pRoom == null ? 0 : pRoom.__nRoomId);
#line 15 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			pSendBlob.PackUint32(nMessageTypeHash);
#line 16 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			pSendBlob.PackBlob(pBlob);
#line 18 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			__pClientSocket.Send(pSendBlob);
		}

#line 24 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public virtual void OnInitialJoin()
		{
		}

#line 31 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public gsServerRoom GetRoomByRoomId(uint nRoomId)
		{
#line 33 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			for (int i = 0; i < __pRoomVector.GetSize(); i++)
			{
				gsServerRoom pRoom = __pRoomVector.Get(i);
#line 36 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
				if (pRoom.__nRoomId == nRoomId)
#line 37 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					return pRoom;
			}
#line 39 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			return null;
		}

#line 44 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public void SyncRespond(uint nSyncId, byte nResult, gsSync.Response eResponse, gsBlob pBlob)
		{
			gsBlob pRespondBlob = new gsBlob();
#line 48 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			pRespondBlob.PackBool(true);
#line 49 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			pRespondBlob.PackUint32(nSyncId);
#line 50 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			pRespondBlob.PackUint8(nResult);
#line 51 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			pRespondBlob.PackUint8((byte)(eResponse));
#line 53 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			if (pBlob != null)
			{
#line 55 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
				pRespondBlob.PackBool(true);
#line 56 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
				pRespondBlob.PackBlob(pBlob);
			}
			else
			{
#line 60 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
				pRespondBlob.PackBool(false);
			}
#line 63 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			__pClientSocket.Send(pRespondBlob);
		}

#line 88 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public uint __nClientId;
#line 89 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public gsServer __pServer;
#line 90 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public gsClientSocket __pClientSocket;
#line 91 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public gsClient.State __eState;
#line 92 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public Vector<gsServerRoom> __pRoomVector;
#line 94 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public uint __nLastSyncId;
#line 96 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public gsServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer)
		{
#line 98 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			__nClientId = nClientId;
#line 99 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			__pServer = pServer;
#line 100 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			__pClientSocket = pClientSocket;
#line 101 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			__eState = gsClient.State.CONNECT;
#line 102 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			__pRoomVector = new Vector<gsServerRoom>();
		}

#line 105 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public void __Update()
		{
#line 107 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			__pClientSocket.Update();
#line 109 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			switch (__eState)
			{
				case gsClient.State.CONNECT:
				{
#line 113 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					__eState = gsClient.State.HANDSHAKE;
#line 114 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					break;
				}

				case gsClient.State.HANDSHAKE:
				{
					gsBlob pReceiveBlob = __pClientSocket.Receive();
#line 119 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					if (pReceiveBlob != null)
					{
						ushort nMagic = 0;
						ushort nVersion = 0;
						byte nAuthMode = 0;
#line 125 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
						if (pReceiveBlob.UnpackUint16(ref nMagic) && pReceiveBlob.UnpackUint16(ref nVersion) && pReceiveBlob.UnpackUint8(ref nAuthMode))
						{
#line 127 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
							if (nMagic == gsClient.MAGIC_WORD && nVersion == __pServer.__nVersion)
							{
#line 130 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
								if (nAuthMode == 0)
								{
									InternalString sName = new InternalString("");
									InternalString sPassword = new InternalString("");
#line 135 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
									if (pReceiveBlob.UnpackInternalString(sName))
									{
#line 137 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
										if (pReceiveBlob.UnpackInternalString(sPassword))
										{
											gsBlob pSendBlob = new gsBlob();
#line 142 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
											pSendBlob.PackUint16(gsClient.MAGIC_WORD);
#line 143 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
											pSendBlob.PackUint16(__pServer.__nVersion);
#line 144 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
											pSendBlob.PackBool(true);
#line 145 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
											pSendBlob.PackUint32(__nClientId);
#line 146 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
											__pClientSocket.Send(pSendBlob);
#line 148 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
											__eState = gsClient.State.CONNECTED;
#line 150 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
											OnInitialJoin();
#line 151 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
											break;
										}
									}
								}
							}
						}
						{
#line 159 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
							Console.Log("Bad handshake, disconnecting");
							gsBlob pResponseBlob = new gsBlob();
#line 161 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
							pResponseBlob.PackUint8((byte)(gsError.Error.BAD_HANDSHAKE));
#line 162 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
							__pClientSocket.Disconnect();
#line 163 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
							return;
						}
					}
					else
					{
					}
#line 170 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					break;
				}

				case gsClient.State.CONNECTED:
				{
					gsBlob pReceiveBlob = __pClientSocket.Receive();
#line 175 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					if (pReceiveBlob != null)
					{
						uint nSyncId = 0;
						uint nLastSyncId = 0;
						uint nRoomId = 0;
						uint nSyncType = 0;
						gsBlob pSyncBlob = new gsBlob();
#line 183 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
						if (pReceiveBlob.UnpackUint32(ref nSyncId) && pReceiveBlob.UnpackUint32(ref nLastSyncId) && pReceiveBlob.UnpackUint32(ref nRoomId) && pReceiveBlob.UnpackUint32(ref nSyncType) && pReceiveBlob.UnpackBlob(pSyncBlob))
						{
#line 189 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
							if (nRoomId > 0)
							{
								gsServerRoom pRoom = GetRoomByRoomId(nRoomId);
#line 193 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
								if (pRoom == null)
								{
#line 195 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
									ErrorDisconnect("Bad room");
#line 196 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
									return;
								}
								gsServerRoom_SyncHandler pHandler = pRoom.__GetSyncHandler(nSyncType);
#line 199 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
								if (pHandler == null)
								{
#line 201 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
									ErrorDisconnect("No handler for room sync");
#line 202 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
									return;
								}
#line 204 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
								pHandler.__pHandler(pRoom, nSyncId, nSyncType, pSyncBlob, this);
							}
							else
							{
							}
						}
						else
						{
#line 214 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
							Assert.Plz(false);
						}
					}
#line 217 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					break;
				}

				case gsClient.State.DISCONNECTED:
				{
#line 221 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					break;
				}

				default:
				{
#line 225 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					Assert.Plz(false);
#line 226 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					break;
				}

			}
		}

#line 231 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public void ErrorDisconnect(string sxErrorMessage)
		{
#line 233 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			Console.Log("Error disconnect");
#line 234 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			Console.Log(sxErrorMessage);
#line 241 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			__pClientSocket.Disconnect();
		}

#line 4 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		~gsServerClient()
		{
		}

	}
}

