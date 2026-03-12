#line 1 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
	class gsServerRoom_SyncHandler
	{
		public delegate void SyncHandler(gsServerRoom pRoom, uint nSyncId, uint nSyncType, gsBlob pInBlob, gsServerClient pServerClient);
#line 7 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public uint __nHash;
#line 8 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public SyncHandler __pHandler;
#line 10 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public gsServerRoom_SyncHandler(uint nHash, SyncHandler pHandler)
		{
#line 12 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			__nHash = nHash;
#line 13 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			__pHandler = pHandler;
		}

	}
#line 17 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
	class gsServerRoom
	{
#line 19 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public gsServerClient GetClientByClientId(uint nClientId)
		{
#line 21 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			for (int i = 0; i < __pClientVector.GetSize(); i++)
			{
#line 23 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
				gsServerClient pClient = __pClientVector.Get(i);
#line 24 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
				if (pClient.__nClientId == nClientId)
#line 25 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
					return pClient;
			}
#line 27 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			return null;
		}

#line 30 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		protected virtual gsBlob OnClientJoin(gsServerClient pClient)
		{
#line 32 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			return new gsBlob();
		}

#line 35 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		protected virtual void OnClientLeave(gsServerClient pClient)
		{
		}

#line 40 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public void RegisterHandler(uint nSyncType, gsServerRoom_SyncHandler.SyncHandler pHandler)
		{
#line 42 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			if (__GetSyncHandler(nSyncType) != null)
			{
#line 44 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
				Console.Log("Server room sync handler hash already registered!");
#line 45 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
				Assert.Plz(false);
			}
#line 47 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			__pSyncHandlerVector.PushBack(new gsServerRoom_SyncHandler(nSyncType, pHandler));
		}

#line 50 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public gsServerRoom_SyncHandler __GetSyncHandler(uint nSyncType)
		{
#line 52 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			for (int i = 0; i < __pSyncHandlerVector.GetSize(); i++)
			{
#line 54 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
				gsServerRoom_SyncHandler pInfo = __pSyncHandlerVector.Get(i);
#line 55 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
				if (pInfo.__nHash == nSyncType)
#line 56 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
					return pInfo;
			}
#line 58 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			return null;
		}

#line 62 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public uint __nRoomId;
#line 63 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public uint __nRoomType;
#line 64 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public InternalString __sRoomType;
#line 66 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public gsServer __pServer;
#line 67 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public Vector<gsServerClient> __pClientVector;
#line 68 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public OwnedVector<gsServerRoom_SyncHandler> __pSyncHandlerVector;
#line 70 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public gsServerRoom(uint nRoomId, string sxRoomType, gsServer pServer)
		{
#line 72 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			__nRoomId = nRoomId;
#line 73 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			__nRoomType = ExternalString.GetChecksum(sxRoomType);
#line 74 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			__sRoomType = new InternalString(sxRoomType);
#line 75 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			__pServer = pServer;
#line 76 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			__pClientVector = new Vector<gsServerClient>();
#line 77 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			__pSyncHandlerVector = new OwnedVector<gsServerRoom_SyncHandler>();
		}

#line 80 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public void __ClientJoin(gsServerClient pClient)
		{
#line 82 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			Assert.Plz(GetClientByClientId(pClient.__nClientId) == null);
#line 84 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			__pClientVector.PushBack(pClient);
#line 85 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			pClient.__pRoomVector.PushBack(this);
#line 86 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			gsBlob pJoinBlob = OnClientJoin(pClient);
#line 88 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			gsBlob pBlob = new gsBlob();
#line 89 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			pBlob.PackUint32(__nRoomId);
#line 90 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			pBlob.PackUint32(__nRoomType);
#line 91 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			pBlob.PackBool(false);
#line 92 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			pBlob.PackBlob(pJoinBlob);
#line 94 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			pClient.Send(null, gsClient.__ROOM_JOIN_HASH, pBlob);
		}

#line 97 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public void __ClientLeave(gsServerClient pClient)
		{
#line 99 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			for (int i = 0; i < __pClientVector.GetSize(); i++)
			{
#line 101 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
				if (__pClientVector.Get(i) == pClient)
				{
#line 103 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
					OnClientLeave(pClient);
#line 104 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
					__pClientVector.Erase(i);
#line 106 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
					for (int j = 0; j < pClient.__pRoomVector.GetSize(); j++)
					{
#line 108 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
						if (pClient.__pRoomVector.Get(j) == this)
						{
#line 110 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
							pClient.__pRoomVector.Erase(j);
#line 112 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
							gsBlob pBlob = new gsBlob();
#line 113 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
							pBlob.PackUint32(__nRoomId);
#line 114 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
							pBlob.PackUint32(__nRoomType);
#line 115 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
							pClient.Send(null, gsClient.__ROOM_LEAVE_HASH, pBlob);
#line 116 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
							return;
						}
					}
#line 121 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
					Assert.Plz(false);
				}
			}
#line 126 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			Assert.Plz(false);
		}

#line 17 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		~gsServerRoom()
		{
		}

	}
}

