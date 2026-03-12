#line 1 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	class gsClient_SyncHandler
	{
		public delegate void SyncHandler(gsClient pClient, uint nSyncId, gsBlob pMessageBlob);
#line 7 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public uint __nHash;
#line 8 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public SyncHandler __pHandler;
#line 10 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public gsClient_SyncHandler(uint nHash, SyncHandler pHandler)
		{
#line 12 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__nHash = nHash;
#line 13 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__pHandler = pHandler;
		}

	}
#line 17 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	class gsClient
	{
#line 19 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public enum State
		{
			CONNECT,
			HANDSHAKE,
			CONNECTED,
			DISCONNECTED,
			ERRORED,
		}

#line 27 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public gsClient(string sxAddress, ushort nPort, ushort nVersion)
		{
#line 29 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__pRoomVector = new OwnedVector<gsClientRoom>();
#line 31 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__pClientSocket = new gsClientSocket();
#line 32 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__pClientSocket.Connect(sxAddress, nPort);
#line 33 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__nVersion = nVersion;
#line 34 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__eState = State.CONNECT;
#line 35 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__pSyncInnerVector = new OwnedVector<gsSyncInner>();
#line 36 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__pSyncHandlerVector = new OwnedVector<gsClient_SyncHandler>();
#line 38 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			RegisterHandler(__ROOM_JOIN_HASH, __OnRoomJoin);
#line 39 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			RegisterHandler(__ROOM_LEAVE_HASH, __OnRoomLeave);
		}

#line 42 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		~gsClient()
		{
#line 44 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__pClientSocket.Disconnect();
		}

#line 47 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public void Update()
		{
#line 49 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__pClientSocket.Update();
#line 51 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			switch (__eState)
			{
				case State.CONNECT:
				{
#line 55 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					if (!__pClientSocket.Pending())
					{
#line 57 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						__eState = State.HANDSHAKE;
#line 59 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						gsBlob pSendBlob = new gsBlob();
#line 60 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						pSendBlob.PackUint16(MAGIC_WORD);
#line 61 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						pSendBlob.PackUint16(__nVersion);
#line 63 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						pSendBlob.PackUint8(0);
#line 65 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						InternalString sName = new InternalString("cliffya");
#line 66 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						pSendBlob.PackInternalString(sName);
#line 68 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						InternalString sPassword = new InternalString("password");
#line 69 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						pSendBlob.PackInternalString(sPassword);
#line 71 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						__pClientSocket.Send(pSendBlob);
					}
#line 73 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					break;
				}

				case State.HANDSHAKE:
				{
#line 77 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					gsBlob pReceiveBlob = __pClientSocket.Receive();
#line 78 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					if (pReceiveBlob != null)
					{
#line 81 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						const int INITIAL_SIZE = 2 + 2 + 1 + 4;
#line 82 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (pReceiveBlob.GetSize() == INITIAL_SIZE)
						{
#line 84 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							ushort nMagic = 0;
#line 85 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							ushort nVersion = 0;
#line 86 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							bool bSuccess = false;
#line 88 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (pReceiveBlob.UnpackUint16(ref nMagic) && pReceiveBlob.UnpackUint16(ref nVersion) && pReceiveBlob.UnpackBool(ref bSuccess))
							{
#line 90 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								if (nMagic == gsClient.MAGIC_WORD && bSuccess)
								{
#line 92 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
									if (!pReceiveBlob.UnpackUint32(ref __nClientId))
#line 93 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
										Assert.Plz(false);
#line 94 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
									__eState = State.CONNECTED;
#line 95 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
									break;
								}
							}
						}
#line 101 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						Console.Log("bad handshake?");
#line 102 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						Assert.Plz(false);
					}
#line 104 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					break;
				}

				case State.CONNECTED:
				{
#line 108 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					gsBlob pReceiveBlob = __pClientSocket.Receive();
#line 109 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					if (pReceiveBlob != null)
					{
#line 111 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						bool bSyncResponse = false;
#line 112 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						uint nSyncId = 0;
#line 114 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (!pReceiveBlob.UnpackBool(ref bSyncResponse) || !pReceiveBlob.UnpackUint32(ref nSyncId))
						{
#line 116 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							Console.Log("bad blob?");
#line 117 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							Assert.Plz(false);
						}
#line 120 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (bSyncResponse)
						{
#line 122 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							gsSyncInner pSyncInner = GetSyncInnerBySyncId(nSyncId);
#line 123 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							Assert.Plz(pSyncInner != null);
#line 125 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							byte nResult = 0;
#line 126 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (!pReceiveBlob.UnpackUint8(ref nResult))
#line 127 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								Assert.Plz(false);
#line 129 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							byte nResponseRaw = 0;
#line 130 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (!pReceiveBlob.UnpackUint8(ref nResponseRaw))
#line 131 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								Assert.Plz(false);
#line 132 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							gsSync.Response eResponse = (gsSync.Response)(nResponseRaw);
#line 134 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (nResult == gsSync.RESULT_SUCCESS && eResponse != pSyncInner.__eResponse)
							{
#line 136 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								ErrorDisconnect("Response expectation mismatch");
#line 137 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								return;
							}
#line 140 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							bool bHasBlob = false;
#line 141 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (!pReceiveBlob.UnpackBool(ref bHasBlob))
#line 142 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								Assert.Plz(false);
#line 144 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							gsBlob pSyncBlob = null;
#line 145 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (bHasBlob)
							{
#line 147 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								pSyncBlob = new gsBlob();
#line 148 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								if (!pReceiveBlob.UnpackBlob(pSyncBlob))
#line 149 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
									Assert.Plz(false);
							}
#line 152 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (eResponse != gsSync.Response.EXPECT_ROOM_CHANGE)
#line 153 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								pSyncInner.__bComplete = true;
#line 155 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							pSyncInner.__nResult = nResult;
#line 156 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (nResult == gsSync.RESULT_SUCCESS && pSyncInner.__pSync != null)
#line 157 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								pSyncInner.__pSync.OnComplete(nResult, pSyncBlob);
						}
						else
						{
#line 161 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							uint nRoomId = 0;
#line 162 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							uint nMessageType = 0;
#line 164 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (!pReceiveBlob.UnpackUint32(ref nRoomId) || !pReceiveBlob.UnpackUint32(ref nMessageType))
#line 165 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								Assert.Plz(false);
#line 167 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							gsBlob pMessageBlob = new gsBlob();
#line 168 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (!pReceiveBlob.UnpackBlob(pMessageBlob))
#line 169 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								Assert.Plz(false);
#line 171 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (nRoomId == 0)
							{
#line 173 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								gsClient_SyncHandler pHandler = __GetSyncHandler(nMessageType);
#line 174 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								if (pHandler == null)
								{
#line 176 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
									ErrorDisconnect("No handler registered for sync message");
#line 177 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
									return;
								}
#line 179 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								pHandler.__pHandler(this, nSyncId, pMessageBlob);
							}
							else
							{
#line 183 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								gsClientRoom pRoom = GetRoomByRoomId(nRoomId);
#line 184 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								if (pRoom == null)
								{
#line 186 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
									ErrorDisconnect("Bad room id");
#line 187 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
									return;
								}
#line 189 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								gsClientRoom_SyncHandler pHandler = pRoom.__GetSyncHandler(nMessageType);
#line 190 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								if (pHandler == null)
								{
#line 192 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
									ErrorDisconnect("No handler registered for room sync message");
#line 193 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
									return;
								}
#line 195 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								pHandler.__pHandler(this, pRoom, nSyncId, pMessageBlob);
							}
						}
					}
#line 200 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					int i = 0;
#line 201 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					while (i < __pSyncInnerVector.GetSize())
					{
#line 203 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						gsSyncInner pSyncInner = __pSyncInnerVector.Get(i);
#line 204 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (pSyncInner.__eResponse == gsSync.Response.EXPECT_ROOM_CHANGE && !pSyncInner.__bComplete)
						{
#line 206 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							int j = 0;
#line 207 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							for (j = 0; j < __pRoomVector.GetSize(); j++)
							{
#line 209 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								gsClientRoom pRoom = __pRoomVector.Get(j);
#line 210 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								if (pRoom.__nRoomId == pSyncInner.__nRoomId)
#line 211 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
									break;
							}
#line 214 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (j == __pRoomVector.GetSize())
							{
#line 216 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								pSyncInner.__eResponse = gsSync.Response.NO_RESPONSE;
#line 217 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								pSyncInner.__bComplete = true;
							}
						}
#line 221 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (pSyncInner.__bComplete && pSyncInner.__pSync == null)
						{
#line 223 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							__pSyncInnerVector.Erase(i);
#line 224 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							continue;
						}
#line 226 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						i++;
					}
#line 230 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					break;
				}

				case State.DISCONNECTED:
				{
#line 234 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					break;
				}

				case State.ERRORED:
				{
#line 238 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					break;
				}

				default:
				{
#line 242 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					Assert.Plz(false);
#line 243 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					break;
				}

			}
		}

#line 248 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public static void __OnRoomJoin(gsClient pClient, uint nSyncId, gsBlob pMessageBlob)
		{
#line 250 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			uint nRoomId = 0;
#line 251 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			uint nRoomType = 0;
#line 252 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			bool bPrimary = false;
#line 253 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (pMessageBlob.UnpackUint32(ref nRoomId) && pMessageBlob.UnpackUint32(ref nRoomType) && pMessageBlob.UnpackBool(ref bPrimary))
			{
#line 255 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				gsBlob pJoinBlob = new gsBlob();
#line 256 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (pMessageBlob.UnpackBlob(pJoinBlob))
				{
#line 258 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					gsClientRoom pRoom = pClient.OnRoomJoin(nRoomId, nRoomType, bPrimary, pJoinBlob);
#line 259 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					if (pRoom != null)
					{
						NumbatLogic.gsClientRoom __3933567650 = pRoom;
#line 261 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						pRoom = null;
#line 261 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						pClient.__pRoomVector.PushBack(__3933567650);
#line 262 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						return;
					}
				}
			}
#line 266 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			pClient.ErrorDisconnect("Room join failed");
		}

#line 269 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public static void __OnRoomLeave(gsClient pClient, uint nSyncId, gsBlob pMessageBlob)
		{
#line 271 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			uint nLeaveRoomId = 0;
#line 272 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			uint nLeaveRoomType = 0;
#line 273 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (pMessageBlob.UnpackUint32(ref nLeaveRoomId) && pMessageBlob.UnpackUint32(ref nLeaveRoomType))
			{
#line 275 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				for (int i = 0; i < pClient.__pRoomVector.GetSize(); i++)
				{
#line 277 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					if (pClient.__pRoomVector.Get(i).__nRoomId == nLeaveRoomId)
					{
#line 279 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						pClient.__pRoomVector.Erase(i);
#line 280 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						return;
					}
				}
			}
#line 284 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			pClient.ErrorDisconnect("Room leave failed");
		}

#line 287 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public void RegisterHandler(uint nMessageType, gsClient_SyncHandler.SyncHandler pHandler)
		{
#line 289 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (__GetSyncHandler(nMessageType) != null)
			{
#line 291 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				Console.Log("Sync handler hash already registered!");
#line 292 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				Assert.Plz(false);
			}
#line 294 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__pSyncHandlerVector.PushBack(new gsClient_SyncHandler(nMessageType, pHandler));
		}

#line 297 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public gsClient_SyncHandler __GetSyncHandler(uint nMessageType)
		{
#line 299 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			for (int i = 0; i < __pSyncHandlerVector.GetSize(); i++)
			{
#line 301 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				gsClient_SyncHandler pInfo = __pSyncHandlerVector.Get(i);
#line 302 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (pInfo.__nHash == nMessageType)
#line 303 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					return pInfo;
			}
#line 305 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			return null;
		}

#line 308 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public void SyncSend(gsSync pSync, string sxSyncType, gsBlob pBlob, gsSync.Response eResponse, gsClientRoom pRoom)
		{
#line 310 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (eResponse == gsSync.Response.EXPECT_ROOM_CHANGE)
#line 311 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				Assert.Plz(!HasRoomChangeSyncInFlight(pRoom));
#line 313 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			gsSyncInner pSyncInner = new gsSyncInner(pSync, ++__nLastSyncId, sxSyncType, pRoom, this);
#line 314 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			pSyncInner.__eResponse = eResponse;
#line 316 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			gsBlob pSendBlob = new gsBlob();
#line 317 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			pSendBlob.PackUint32(pSyncInner.__nSyncId);
#line 318 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			pSendBlob.PackUint32(0);
#line 319 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (pRoom != null)
#line 320 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				pSendBlob.PackUint32(pRoom.__nRoomId);
			else
#line 322 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				pSendBlob.PackUint32(0);
#line 323 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			pSendBlob.PackUint32(pSyncInner.__nSyncType);
#line 324 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			pSendBlob.PackBlob(pBlob);
#line 326 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__pClientSocket.Send(pSendBlob);
#line 328 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			pSyncInner.__pSync.__pSyncInner = pSyncInner;
#line 330 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (pSyncInner.__eResponse == gsSync.Response.NO_RESPONSE)
#line 331 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				pSyncInner.__bComplete = true;
			NumbatLogic.gsSyncInner __3139231656 = pSyncInner;
#line 333 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			pSyncInner = null;
#line 333 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__pSyncInnerVector.PushBack(__3139231656);
		}

#line 336 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public bool GetPending()
		{
#line 338 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (__eState == State.ERRORED)
#line 339 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				return false;
#line 341 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (__pClientSocket.Pending())
#line 342 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				return true;
#line 344 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (!__pClientSocket.GetConnected())
#line 345 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				return false;
#line 347 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			for (int i = 0; i < __pSyncInnerVector.GetSize(); i++)
			{
#line 349 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				gsSyncInner pSyncInner = __pSyncInnerVector.Get(i);
#line 350 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (!pSyncInner.__bComplete)
#line 351 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					return true;
			}
#line 354 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			return false;
		}

#line 357 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public bool HasActiveSync()
		{
#line 359 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			for (int i = 0; i < __pSyncInnerVector.GetSize(); i++)
			{
#line 361 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				gsSyncInner pSyncInner = __pSyncInnerVector.Get(i);
#line 362 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (!pSyncInner.__bComplete)
#line 363 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					return true;
			}
#line 365 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			return false;
		}

#line 368 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public bool HasActiveSyncByRoom(gsClientRoom pRoom)
		{
#line 370 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			for (int i = 0; i < __pSyncInnerVector.GetSize(); i++)
			{
#line 372 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				gsSyncInner pSyncInner = __pSyncInnerVector.Get(i);
#line 373 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (pSyncInner.__nRoomId == pRoom.__nRoomId && !pSyncInner.__bComplete)
#line 374 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					return true;
			}
#line 376 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			return false;
		}

#line 379 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public bool HasRoomChangeSyncInFlight(gsClientRoom pRoom)
		{
#line 381 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			uint nRoomId = pRoom != null ? pRoom.__nRoomId : 0;
#line 382 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			for (int i = 0; i < __pSyncInnerVector.GetSize(); i++)
			{
#line 384 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				gsSyncInner pSyncInner = __pSyncInnerVector.Get(i);
#line 385 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (pSyncInner.__eResponse == gsSync.Response.EXPECT_ROOM_CHANGE && !pSyncInner.__bComplete && pSyncInner.__nRoomId == nRoomId)
#line 386 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					return true;
			}
#line 388 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			return false;
		}

#line 391 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public virtual gsClientRoom OnRoomJoin(uint nRoomId, uint nRoomTypeHash, bool bPrimary, gsBlob pJoinBlob)
		{
#line 393 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			return new gsClientRoom(nRoomId, null, nRoomTypeHash, bPrimary, this);
		}

#line 399 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public const ushort MAGIC_WORD = 619;
#line 401 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public OwnedVector<gsClientRoom> __pRoomVector;
#line 404 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public gsClientSocket __pClientSocket;
#line 405 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public ushort __nVersion;
#line 407 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public uint __nClientId;
#line 409 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public uint __nLastSyncId;
#line 410 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public OwnedVector<gsSyncInner> __pSyncInnerVector;
#line 411 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public OwnedVector<gsClient_SyncHandler> __pSyncHandlerVector;
#line 414 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public State __eState;
#line 415 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public InternalString __sErrorMessage;
#line 417 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public static uint __ROOM_JOIN_HASH = 1895086341;
#line 418 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public static uint __ROOM_LEAVE_HASH = 938124572;
#line 422 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public gsClientRoom GetRoomByRoomId(uint nRoomId)
		{
#line 424 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			for (int i = 0; i < __pRoomVector.GetSize(); i++)
			{
#line 426 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				gsClientRoom pRoom = __pRoomVector.Get(i);
#line 427 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (pRoom.__nRoomId == nRoomId)
#line 428 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					return pRoom;
			}
#line 430 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			return null;
		}

#line 433 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public void ErrorDisconnect(string sxErrorMessage)
		{
#line 435 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			Console.Log("Error disconnect");
#line 436 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			Console.Log(sxErrorMessage);
#line 437 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__sErrorMessage = new InternalString(sxErrorMessage);
#line 438 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__eState = State.ERRORED;
#line 439 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__pClientSocket.Disconnect();
		}

#line 442 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public string GetErrorMessage()
		{
#line 444 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			Assert.Plz(__eState == State.ERRORED);
#line 445 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			return __sErrorMessage.GetExternalString();
		}

#line 448 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public gsSyncInner GetSyncInnerBySyncId(uint nSyncId)
		{
#line 450 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			for (int i = 0; i < __pSyncInnerVector.GetSize(); i++)
			{
#line 452 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				gsSyncInner pSyncInner = __pSyncInnerVector.Get(i);
#line 453 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (nSyncId == pSyncInner.__nSyncId)
#line 454 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					return pSyncInner;
			}
#line 456 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			return null;
		}

	}
}

