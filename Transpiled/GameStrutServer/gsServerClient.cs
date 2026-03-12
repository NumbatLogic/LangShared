#line 1 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
	class gsServerClient
	{
#line 5 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public void Send(gsServerRoom pRoom, uint nMessageTypeHash, gsBlob pBlob)
		{
#line 7 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			gsBlob pSendBlob = new gsBlob();
#line 9 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			uint nSyncId = __nLastSyncId++;
#line 11 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			pSendBlob.PackBool(false);
#line 12 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			pSendBlob.PackUint32(nSyncId);
#line 13 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			pSendBlob.PackUint32(pRoom == null ? 0 : pRoom.__nRoomId);
#line 14 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			pSendBlob.PackUint32(nMessageTypeHash);
#line 15 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			pSendBlob.PackBlob(pBlob);
#line 17 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			__pClientSocket.Send(pSendBlob);
		}

#line 23 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public virtual void OnInitialJoin()
		{
		}

#line 30 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public gsServerRoom GetRoomByRoomId(uint nRoomId)
		{
#line 32 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			for (int i = 0; i < __pRoomVector.GetSize(); i++)
			{
#line 34 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
				gsServerRoom pRoom = __pRoomVector.Get(i);
#line 35 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
				if (pRoom.__nRoomId == nRoomId)
#line 36 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					return pRoom;
			}
#line 38 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			return null;
		}

#line 43 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public void SyncRespond(uint nSyncId, byte nResult, gsSync.Response eResponse, gsBlob pBlob)
		{
#line 45 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			gsBlob pRespondBlob = new gsBlob();
#line 47 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			pRespondBlob.PackBool(true);
#line 48 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			pRespondBlob.PackUint32(nSyncId);
#line 49 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			pRespondBlob.PackUint8(nResult);
#line 50 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			pRespondBlob.PackUint8((byte)(eResponse));
#line 52 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			if (pBlob != null)
			{
#line 54 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
				pRespondBlob.PackBool(true);
#line 55 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
				pRespondBlob.PackBlob(pBlob);
			}
			else
			{
#line 59 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
				pRespondBlob.PackBool(false);
			}
#line 62 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			__pClientSocket.Send(pRespondBlob);
		}

#line 87 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public uint __nClientId;
#line 88 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public gsServer __pServer;
#line 89 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public gsClientSocket __pClientSocket;
#line 90 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public gsClient.State __eState;
#line 91 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public Vector<gsServerRoom> __pRoomVector;
#line 93 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public uint __nLastSyncId;
#line 95 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public gsServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer)
		{
#line 97 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			__nClientId = nClientId;
#line 98 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			__pServer = pServer;
#line 99 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			__pClientSocket = pClientSocket;
#line 100 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			__eState = gsClient.State.CONNECT;
#line 101 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			__pRoomVector = new Vector<gsServerRoom>();
		}

#line 104 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public void __Update()
		{
#line 106 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			__pClientSocket.Update();
#line 108 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			switch (__eState)
			{
				case gsClient.State.CONNECT:
				{
#line 112 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					__eState = gsClient.State.HANDSHAKE;
#line 113 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					break;
				}

				case gsClient.State.HANDSHAKE:
				{
#line 117 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					gsBlob pReceiveBlob = __pClientSocket.Receive();
#line 118 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					if (pReceiveBlob != null)
					{
#line 120 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
						ushort nMagic = 0;
#line 121 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
						ushort nVersion = 0;
#line 122 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
						byte nAuthMode = 0;
#line 124 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
						if (pReceiveBlob.UnpackUint16(ref nMagic) && pReceiveBlob.UnpackUint16(ref nVersion) && pReceiveBlob.UnpackUint8(ref nAuthMode))
						{
#line 126 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
							if (nMagic == gsClient.MAGIC_WORD && nVersion == __pServer.__nVersion)
							{
#line 129 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
								if (nAuthMode == 0)
								{
#line 131 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
									InternalString sName = new InternalString("");
#line 132 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
									InternalString sPassword = new InternalString("");
#line 134 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
									if (pReceiveBlob.UnpackInternalString(sName))
									{
#line 136 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
										if (pReceiveBlob.UnpackInternalString(sPassword))
										{
#line 140 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
											gsBlob pSendBlob = new gsBlob();
#line 141 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
											pSendBlob.PackUint16(gsClient.MAGIC_WORD);
#line 142 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
											pSendBlob.PackUint16(__pServer.__nVersion);
#line 143 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
											pSendBlob.PackBool(true);
#line 144 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
											pSendBlob.PackUint32(__nClientId);
#line 145 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
											__pClientSocket.Send(pSendBlob);
#line 147 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
											__eState = gsClient.State.CONNECTED;
#line 149 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
											OnInitialJoin();
#line 150 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
											break;
										}
									}
								}
							}
						}
						{
#line 158 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
							Console.Log("Bad handshake, disconnecting");
#line 159 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
							gsBlob pResponseBlob = new gsBlob();
#line 160 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
							pResponseBlob.PackUint8((byte)(gsError.Error.BAD_HANDSHAKE));
#line 161 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
							__pClientSocket.Disconnect();
#line 162 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
							return;
						}
					}
					else
					{
					}
#line 169 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					break;
				}

				case gsClient.State.CONNECTED:
				{
#line 173 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					gsBlob pReceiveBlob = __pClientSocket.Receive();
#line 174 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					if (pReceiveBlob != null)
					{
#line 176 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
						uint nSyncId = 0;
#line 177 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
						uint nLastSyncId = 0;
#line 178 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
						uint nRoomId = 0;
#line 179 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
						uint nSyncType = 0;
#line 180 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
						gsBlob pSyncBlob = new gsBlob();
#line 182 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
						if (pReceiveBlob.UnpackUint32(ref nSyncId) && pReceiveBlob.UnpackUint32(ref nLastSyncId) && pReceiveBlob.UnpackUint32(ref nRoomId) && pReceiveBlob.UnpackUint32(ref nSyncType) && pReceiveBlob.UnpackBlob(pSyncBlob))
						{
#line 188 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
							if (nRoomId > 0)
							{
#line 190 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
								gsServerRoom pRoom = GetRoomByRoomId(nRoomId);
#line 192 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
								if (pRoom == null)
								{
#line 194 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
									ErrorDisconnect("Bad room");
#line 195 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
									return;
								}
#line 197 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
								gsServerRoom_SyncHandler pHandler = pRoom.__GetSyncHandler(nSyncType);
#line 198 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
								if (pHandler == null)
								{
#line 200 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
									ErrorDisconnect("No handler for room sync");
#line 201 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
									return;
								}
#line 203 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
								pHandler.__pHandler(pRoom, nSyncId, nSyncType, pSyncBlob, this);
							}
							else
							{
							}
						}
						else
						{
#line 213 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
							Assert.Plz(false);
						}
					}
#line 216 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					break;
				}

				case gsClient.State.DISCONNECTED:
				{
#line 220 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					break;
				}

				default:
				{
#line 224 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					Assert.Plz(false);
#line 225 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					break;
				}

			}
		}

#line 230 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public void ErrorDisconnect(string sxErrorMessage)
		{
#line 232 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			Console.Log("Error disconnect");
#line 233 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			Console.Log(sxErrorMessage);
#line 240 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			__pClientSocket.Disconnect();
		}

#line 3 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		~gsServerClient()
		{
		}

	}
}

