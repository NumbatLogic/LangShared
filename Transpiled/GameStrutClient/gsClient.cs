#line 1 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	class gsClient_SyncHandler
	{
		public delegate void SyncHandler(gsClient pClient, uint nSyncId, gsBlob pMessageBlob);
#line 8 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public uint __nHash;
#line 9 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public SyncHandler __pHandler;
#line 11 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public gsClient_SyncHandler(uint nHash, SyncHandler pHandler)
		{
#line 13 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__nHash = nHash;
#line 14 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__pHandler = pHandler;
		}

	}
#line 18 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	class gsClient
	{
#line 20 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public enum State
		{
			CONNECT,
			HANDSHAKE,
			CONNECTED,
			DISCONNECTED,
			ERRORED,
		}

#line 28 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public gsClient(string sxAddress, ushort nPort, ushort nVersion)
		{
#line 30 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__pRoomVector = new OwnedVector<gsClientRoom>();
#line 32 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__pClientSocket = new gsClientSocket();
#line 33 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__pClientSocket.Connect(sxAddress, nPort);
#line 34 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__nVersion = nVersion;
#line 35 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__eState = State.CONNECT;
#line 36 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__pSyncInnerVector = new OwnedVector<gsSyncInner>();
#line 37 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__pSyncHandlerVector = new OwnedVector<gsClient_SyncHandler>();
#line 39 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			RegisterHandler(__ROOM_JOIN_HASH, __OnRoomJoin);
#line 40 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			RegisterHandler(__ROOM_LEAVE_HASH, __OnRoomLeave);
		}

#line 43 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		~gsClient()
		{
#line 45 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__pClientSocket.Disconnect();
		}

#line 48 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public void Update()
		{
#line 50 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__pClientSocket.Update();
#line 52 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			switch (__eState)
			{
				case State.CONNECT:
				{
#line 56 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					if (!__pClientSocket.Pending())
					{
#line 58 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						__eState = State.HANDSHAKE;
						gsBlob pSendBlob = new gsBlob();
#line 61 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						pSendBlob.PackUint16(MAGIC_WORD);
#line 62 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						pSendBlob.PackUint16(__nVersion);
#line 64 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						pSendBlob.PackUint8(0);
						InternalString sName = new InternalString("cliffya");
#line 67 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						pSendBlob.PackInternalString(sName);
						InternalString sPassword = new InternalString("password");
#line 70 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						pSendBlob.PackInternalString(sPassword);
#line 72 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						__pClientSocket.Send(pSendBlob);
					}
#line 74 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					break;
				}

				case State.HANDSHAKE:
				{
					gsBlob pReceiveBlob = __pClientSocket.Receive();
#line 79 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					if (pReceiveBlob != null)
					{
						const int INITIAL_SIZE = 2 + 2 + 1 + 4;
#line 83 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (pReceiveBlob.GetSize() == INITIAL_SIZE)
						{
							ushort nMagic = 0;
							ushort nVersion = 0;
							bool bSuccess = false;
#line 89 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (pReceiveBlob.UnpackUint16(ref nMagic) && pReceiveBlob.UnpackUint16(ref nVersion) && pReceiveBlob.UnpackBool(ref bSuccess))
							{
#line 91 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								if (nMagic == gsClient.MAGIC_WORD && bSuccess)
								{
#line 93 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
									if (!pReceiveBlob.UnpackUint32(ref __nClientId))
#line 94 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
										Assert.Plz(false);
#line 95 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
									__eState = State.CONNECTED;
#line 96 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
									break;
								}
							}
						}
#line 102 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						Console.Log("bad handshake?");
#line 103 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						Assert.Plz(false);
					}
#line 105 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					break;
				}

				case State.CONNECTED:
				{
					gsBlob pReceiveBlob = __pClientSocket.Receive();
#line 110 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					if (pReceiveBlob != null)
					{
						bool bSyncResponse = false;
						uint nSyncId = 0;
#line 115 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (!pReceiveBlob.UnpackBool(ref bSyncResponse) || !pReceiveBlob.UnpackUint32(ref nSyncId))
						{
#line 117 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							Console.Log("bad blob?");
#line 118 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							Assert.Plz(false);
						}
#line 121 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (bSyncResponse)
						{
							gsSyncInner pSyncInner = GetSyncInnerBySyncId(nSyncId);
#line 124 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							Assert.Plz(pSyncInner != null);
							byte nResult = 0;
#line 127 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (!pReceiveBlob.UnpackUint8(ref nResult))
#line 128 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								Assert.Plz(false);
							byte nResponseRaw = 0;
#line 131 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (!pReceiveBlob.UnpackUint8(ref nResponseRaw))
#line 132 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								Assert.Plz(false);
							gsSync.Response eResponse = (gsSync.Response)(nResponseRaw);
#line 135 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (nResult == gsSync.RESULT_SUCCESS && eResponse != pSyncInner.__eResponse)
							{
#line 137 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								ErrorDisconnect("Response expectation mismatch");
#line 138 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								return;
							}
							bool bHasBlob = false;
#line 142 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (!pReceiveBlob.UnpackBool(ref bHasBlob))
#line 143 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								Assert.Plz(false);
							gsBlob pSyncBlob = null;
#line 146 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (bHasBlob)
							{
#line 148 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								pSyncBlob = new gsBlob();
#line 149 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								if (!pReceiveBlob.UnpackBlob(pSyncBlob))
#line 150 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
									Assert.Plz(false);
							}
#line 153 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (eResponse != gsSync.Response.EXPECT_ROOM_CHANGE)
#line 154 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								pSyncInner.__bComplete = true;
#line 156 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							pSyncInner.__nResult = nResult;
#line 157 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (nResult == gsSync.RESULT_SUCCESS && pSyncInner.__pSync != null)
#line 158 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								pSyncInner.__pSync.OnComplete(nResult, pSyncBlob);
						}
						else
						{
							uint nRoomId = 0;
							uint nMessageType = 0;
#line 165 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (!pReceiveBlob.UnpackUint32(ref nRoomId) || !pReceiveBlob.UnpackUint32(ref nMessageType))
#line 166 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								Assert.Plz(false);
							gsBlob pMessageBlob = new gsBlob();
#line 169 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (!pReceiveBlob.UnpackBlob(pMessageBlob))
#line 170 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								Assert.Plz(false);
#line 172 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (nRoomId == 0)
							{
								gsClient_SyncHandler pHandler = __GetSyncHandler(nMessageType);
#line 175 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								if (pHandler == null)
								{
#line 177 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
									ErrorDisconnect("No handler registered for sync message");
#line 178 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
									return;
								}
#line 180 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								pHandler.__pHandler(this, nSyncId, pMessageBlob);
							}
							else
							{
								gsClientRoom pRoom = GetRoomByRoomId(nRoomId);
#line 185 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								if (pRoom == null)
								{
#line 187 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
									ErrorDisconnect("Bad room id");
#line 188 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
									return;
								}
								gsClientRoom_SyncHandler pHandler = pRoom.__GetSyncHandler(nMessageType);
#line 191 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								if (pHandler == null)
								{
#line 193 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
									ErrorDisconnect("No handler registered for room sync message");
#line 194 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
									return;
								}
#line 196 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								pHandler.__pHandler(this, pRoom, nSyncId, pMessageBlob);
							}
						}
					}
					int i = 0;
#line 202 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					while (i < __pSyncInnerVector.GetSize())
					{
						gsSyncInner pSyncInner = __pSyncInnerVector.Get(i);
#line 205 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (pSyncInner.__eResponse == gsSync.Response.EXPECT_ROOM_CHANGE && !pSyncInner.__bComplete)
						{
							int j = 0;
#line 208 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							for (j = 0; j < __pRoomVector.GetSize(); j++)
							{
								gsClientRoom pRoom = __pRoomVector.Get(j);
#line 211 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								if (pRoom.__nRoomId == pSyncInner.__nRoomId)
#line 212 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
									break;
							}
#line 215 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (j == __pRoomVector.GetSize())
							{
#line 217 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								pSyncInner.__eResponse = gsSync.Response.NO_RESPONSE;
#line 218 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								pSyncInner.__bComplete = true;
							}
						}
#line 222 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (pSyncInner.__bComplete && pSyncInner.__pSync == null)
						{
#line 224 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							__pSyncInnerVector.Erase(i);
#line 225 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							continue;
						}
#line 227 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						i++;
					}
#line 231 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					break;
				}

				case State.DISCONNECTED:
				{
#line 235 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					break;
				}

				case State.ERRORED:
				{
#line 239 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					break;
				}

				default:
				{
#line 243 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					Assert.Plz(false);
#line 244 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					break;
				}

			}
		}

#line 249 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public static void __OnRoomJoin(gsClient pClient, uint nSyncId, gsBlob pMessageBlob)
		{
			uint nRoomId = 0;
			uint nRoomType = 0;
			bool bPrimary = false;
#line 254 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (pMessageBlob.UnpackUint32(ref nRoomId) && pMessageBlob.UnpackUint32(ref nRoomType) && pMessageBlob.UnpackBool(ref bPrimary))
			{
				gsBlob pJoinBlob = new gsBlob();
#line 257 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (pMessageBlob.UnpackBlob(pJoinBlob))
				{
					gsClientRoom pRoom = pClient.OnRoomJoin(nRoomId, nRoomType, bPrimary, pJoinBlob);
#line 260 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					if (pRoom != null)
					{
						NumbatLogic.gsClientRoom __3933567650 = pRoom;
#line 262 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						pRoom = null;
#line 262 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						pClient.__pRoomVector.PushBack(__3933567650);
#line 263 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						return;
					}
				}
			}
#line 267 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			pClient.ErrorDisconnect("Room join failed");
		}

#line 270 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public static void __OnRoomLeave(gsClient pClient, uint nSyncId, gsBlob pMessageBlob)
		{
			uint nLeaveRoomId = 0;
			uint nLeaveRoomType = 0;
#line 274 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (pMessageBlob.UnpackUint32(ref nLeaveRoomId) && pMessageBlob.UnpackUint32(ref nLeaveRoomType))
			{
#line 276 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				for (int i = 0; i < pClient.__pRoomVector.GetSize(); i++)
				{
#line 278 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					if (pClient.__pRoomVector.Get(i).__nRoomId == nLeaveRoomId)
					{
#line 280 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						pClient.__pRoomVector.Erase(i);
#line 281 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						return;
					}
				}
			}
#line 285 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			pClient.ErrorDisconnect("Room leave failed");
		}

#line 288 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public void RegisterHandler(uint nMessageType, gsClient_SyncHandler.SyncHandler pHandler)
		{
#line 290 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (__GetSyncHandler(nMessageType) != null)
			{
#line 292 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				Console.Log("Sync handler hash already registered!");
#line 293 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				Assert.Plz(false);
			}
#line 295 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__pSyncHandlerVector.PushBack(new gsClient_SyncHandler(nMessageType, pHandler));
		}

#line 298 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public gsClient_SyncHandler __GetSyncHandler(uint nMessageType)
		{
#line 300 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			for (int i = 0; i < __pSyncHandlerVector.GetSize(); i++)
			{
				gsClient_SyncHandler pInfo = __pSyncHandlerVector.Get(i);
#line 303 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (pInfo.__nHash == nMessageType)
#line 304 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					return pInfo;
			}
#line 306 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			return null;
		}

#line 309 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public void SyncSend(gsSync pSync, string sxSyncType, gsBlob pBlob, gsSync.Response eResponse, gsClientRoom pRoom)
		{
#line 311 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (eResponse == gsSync.Response.EXPECT_ROOM_CHANGE)
#line 312 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				Assert.Plz(!HasRoomChangeSyncInFlight(pRoom));
			gsSyncInner pSyncInner = new gsSyncInner(pSync, ++__nLastSyncId, sxSyncType, pRoom, this);
#line 315 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			pSyncInner.__eResponse = eResponse;
			gsBlob pSendBlob = new gsBlob();
#line 318 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			pSendBlob.PackUint32(pSyncInner.__nSyncId);
#line 319 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			pSendBlob.PackUint32(0);
#line 320 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (pRoom != null)
#line 321 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				pSendBlob.PackUint32(pRoom.__nRoomId);
			else
#line 323 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				pSendBlob.PackUint32(0);
#line 324 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			pSendBlob.PackUint32(pSyncInner.__nSyncType);
#line 325 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			pSendBlob.PackBlob(pBlob);
#line 327 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__pClientSocket.Send(pSendBlob);
#line 329 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			pSyncInner.__pSync.__pSyncInner = pSyncInner;
#line 331 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (pSyncInner.__eResponse == gsSync.Response.NO_RESPONSE)
#line 332 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				pSyncInner.__bComplete = true;
			NumbatLogic.gsSyncInner __3139231656 = pSyncInner;
#line 334 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			pSyncInner = null;
#line 334 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__pSyncInnerVector.PushBack(__3139231656);
		}

#line 337 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public bool GetPending()
		{
#line 339 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (__eState == State.ERRORED)
#line 340 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				return false;
#line 342 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (__pClientSocket.Pending())
#line 343 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				return true;
#line 345 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (!__pClientSocket.GetConnected())
#line 346 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				return false;
#line 348 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			for (int i = 0; i < __pSyncInnerVector.GetSize(); i++)
			{
				gsSyncInner pSyncInner = __pSyncInnerVector.Get(i);
#line 351 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (!pSyncInner.__bComplete)
#line 352 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					return true;
			}
#line 355 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			return false;
		}

#line 358 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public bool HasActiveSync()
		{
#line 360 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			for (int i = 0; i < __pSyncInnerVector.GetSize(); i++)
			{
				gsSyncInner pSyncInner = __pSyncInnerVector.Get(i);
#line 363 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (!pSyncInner.__bComplete)
#line 364 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					return true;
			}
#line 366 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			return false;
		}

#line 369 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public bool HasActiveSyncByRoom(gsClientRoom pRoom)
		{
#line 371 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			for (int i = 0; i < __pSyncInnerVector.GetSize(); i++)
			{
				gsSyncInner pSyncInner = __pSyncInnerVector.Get(i);
#line 374 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (pSyncInner.__nRoomId == pRoom.__nRoomId && !pSyncInner.__bComplete)
#line 375 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					return true;
			}
#line 377 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			return false;
		}

#line 380 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public bool HasRoomChangeSyncInFlight(gsClientRoom pRoom)
		{
			uint nRoomId = pRoom != null ? pRoom.__nRoomId : 0;
#line 383 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			for (int i = 0; i < __pSyncInnerVector.GetSize(); i++)
			{
				gsSyncInner pSyncInner = __pSyncInnerVector.Get(i);
#line 386 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (pSyncInner.__eResponse == gsSync.Response.EXPECT_ROOM_CHANGE && !pSyncInner.__bComplete && pSyncInner.__nRoomId == nRoomId)
#line 387 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					return true;
			}
#line 389 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			return false;
		}

#line 392 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public virtual gsClientRoom OnRoomJoin(uint nRoomId, uint nRoomTypeHash, bool bPrimary, gsBlob pJoinBlob)
		{
#line 394 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			return new gsClientRoom(nRoomId, null, nRoomTypeHash, bPrimary, this);
		}

#line 400 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public const ushort MAGIC_WORD = 619;
#line 402 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public OwnedVector<gsClientRoom> __pRoomVector;
#line 405 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public gsClientSocket __pClientSocket;
#line 406 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public ushort __nVersion;
#line 408 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public uint __nClientId;
#line 410 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public uint __nLastSyncId;
#line 411 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public OwnedVector<gsSyncInner> __pSyncInnerVector;
#line 412 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public OwnedVector<gsClient_SyncHandler> __pSyncHandlerVector;
#line 415 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public State __eState;
#line 416 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public InternalString __sErrorMessage;
#line 418 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public static uint __ROOM_JOIN_HASH = 1895086341;
#line 419 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public static uint __ROOM_LEAVE_HASH = 938124572;
#line 423 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public gsClientRoom GetRoomByRoomId(uint nRoomId)
		{
#line 425 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			for (int i = 0; i < __pRoomVector.GetSize(); i++)
			{
				gsClientRoom pRoom = __pRoomVector.Get(i);
#line 428 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (pRoom.__nRoomId == nRoomId)
#line 429 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					return pRoom;
			}
#line 431 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			return null;
		}

#line 434 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public void ErrorDisconnect(string sxErrorMessage)
		{
#line 436 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			Console.Log("Error disconnect");
#line 437 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			Console.Log(sxErrorMessage);
#line 438 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__sErrorMessage = new InternalString(sxErrorMessage);
#line 439 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__eState = State.ERRORED;
#line 440 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			__pClientSocket.Disconnect();
		}

#line 443 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public string GetErrorMessage()
		{
#line 445 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			Assert.Plz(__eState == State.ERRORED);
#line 446 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			return __sErrorMessage.GetExternalString();
		}

#line 449 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public gsSyncInner GetSyncInnerBySyncId(uint nSyncId)
		{
#line 451 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			for (int i = 0; i < __pSyncInnerVector.GetSize(); i++)
			{
				gsSyncInner pSyncInner = __pSyncInnerVector.Get(i);
#line 454 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (nSyncId == pSyncInner.__nSyncId)
#line 455 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					return pSyncInner;
			}
#line 457 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			return null;
		}

	}
}

