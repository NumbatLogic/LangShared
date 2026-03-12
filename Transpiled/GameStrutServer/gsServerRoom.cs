#line 1 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
namespace NumbatLogic
{
	class gsServerRoom_SyncHandler
	{
		public delegate void SyncHandler(gsServerRoom pRoom, uint nSyncId, uint nSyncType, gsBlob pInBlob, gsServerClient pServerClient);
#line 7 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public uint __nHash;
		public SyncHandler __pHandler;
#line 10 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public gsServerRoom_SyncHandler(uint nHash, SyncHandler pHandler)
		{
			__nHash = nHash;
			__pHandler = pHandler;
		}

	}
	class gsServerRoom
	{
		public gsServerClient GetClientByClientId(uint nClientId)
		{
			for (int i = 0; i < __pClientVector.GetSize(); i++)
			{
				gsServerClient pClient = __pClientVector.Get(i);
				if (pClient.__nClientId == nClientId)
					return pClient;
			}
			return null;
		}

		protected virtual gsBlob OnClientJoin(gsServerClient pClient)
		{
			return new gsBlob();
		}

		protected virtual void OnClientLeave(gsServerClient pClient)
		{
		}

#line 40 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public void RegisterHandler(uint nSyncType, gsServerRoom_SyncHandler.SyncHandler pHandler)
		{
			if (__GetSyncHandler(nSyncType) != null)
			{
				Console.Log("Server room sync handler hash already registered!");
				Assert.Plz(false);
			}
			__pSyncHandlerVector.PushBack(new gsServerRoom_SyncHandler(nSyncType, pHandler));
		}

		public gsServerRoom_SyncHandler __GetSyncHandler(uint nSyncType)
		{
			for (int i = 0; i < __pSyncHandlerVector.GetSize(); i++)
			{
				gsServerRoom_SyncHandler pInfo = __pSyncHandlerVector.Get(i);
				if (pInfo.__nHash == nSyncType)
					return pInfo;
			}
			return null;
		}

#line 62 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public uint __nRoomId;
		public uint __nRoomType;
		public InternalString __sRoomType;
#line 66 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public gsServer __pServer;
		public Vector<gsServerClient> __pClientVector;
		public OwnedVector<gsServerRoom_SyncHandler> __pSyncHandlerVector;
#line 70 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public gsServerRoom(uint nRoomId, string sxRoomType, gsServer pServer)
		{
			__nRoomId = nRoomId;
			__nRoomType = ExternalString.GetChecksum(sxRoomType);
			__sRoomType = new InternalString(sxRoomType);
			__pServer = pServer;
			__pClientVector = new Vector<gsServerClient>();
			__pSyncHandlerVector = new OwnedVector<gsServerRoom_SyncHandler>();
		}

		public void __ClientJoin(gsServerClient pClient)
		{
			Assert.Plz(GetClientByClientId(pClient.__nClientId) == null);
#line 84 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			__pClientVector.PushBack(pClient);
			pClient.__pRoomVector.PushBack(this);
			gsBlob pJoinBlob = OnClientJoin(pClient);
#line 88 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			gsBlob pBlob = new gsBlob();
			pBlob.PackUint32(__nRoomId);
			pBlob.PackUint32(__nRoomType);
			pBlob.PackBool(false);
			pBlob.PackBlob(pJoinBlob);
#line 94 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			pClient.Send(null, gsClient.__ROOM_JOIN_HASH, pBlob);
		}

		public void __ClientLeave(gsServerClient pClient)
		{
			for (int i = 0; i < __pClientVector.GetSize(); i++)
			{
				if (__pClientVector.Get(i) == pClient)
				{
					OnClientLeave(pClient);
					__pClientVector.Erase(i);
#line 106 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
					for (int j = 0; j < pClient.__pRoomVector.GetSize(); j++)
					{
						if (pClient.__pRoomVector.Get(j) == this)
						{
							pClient.__pRoomVector.Erase(j);
#line 112 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
							gsBlob pBlob = new gsBlob();
							pBlob.PackUint32(__nRoomId);
							pBlob.PackUint32(__nRoomType);
							pClient.Send(null, gsClient.__ROOM_LEAVE_HASH, pBlob);
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

