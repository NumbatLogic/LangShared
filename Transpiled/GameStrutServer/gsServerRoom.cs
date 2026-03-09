#line 1 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
	class gsServerRoom_SyncHandler
	{
		public delegate void SyncHandler(gsServerRoom pRoom, uint nSyncId, uint nSyncType, gsBlob pInBlob, gsServerClient pServerClient);
#line 8 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public uint __nHash;
#line 9 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public SyncHandler __pHandler;
#line 11 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public gsServerRoom_SyncHandler(uint nHash, SyncHandler pHandler)
		{
#line 13 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			__nHash = nHash;
#line 14 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			__pHandler = pHandler;
		}

	}
#line 18 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
	class gsServerRoom
	{
#line 20 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public gsServerClient GetClientByClientId(uint nClientId)
		{
#line 22 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			for (int i = 0; i < __pClientVector.GetSize(); i++)
			{
				gsServerClient pClient = __pClientVector.Get(i);
#line 25 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
				if (pClient.__nClientId == nClientId)
#line 26 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
					return pClient;
			}
#line 28 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			return null;
		}

#line 31 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		protected virtual gsBlob OnClientJoin(gsServerClient pClient)
		{
#line 33 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			return new gsBlob();
		}

#line 36 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		protected virtual void OnClientLeave(gsServerClient pClient)
		{
		}

#line 41 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public void RegisterHandler(uint nSyncType, gsServerRoom_SyncHandler.SyncHandler pHandler)
		{
#line 43 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			if (__GetSyncHandler(nSyncType) != null)
			{
#line 45 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
				Console.Log("Server room sync handler hash already registered!");
#line 46 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
				Assert.Plz(false);
			}
#line 48 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			__pSyncHandlerVector.PushBack(new gsServerRoom_SyncHandler(nSyncType, pHandler));
		}

#line 51 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public gsServerRoom_SyncHandler __GetSyncHandler(uint nSyncType)
		{
#line 53 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			for (int i = 0; i < __pSyncHandlerVector.GetSize(); i++)
			{
				gsServerRoom_SyncHandler pInfo = __pSyncHandlerVector.Get(i);
#line 56 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
				if (pInfo.__nHash == nSyncType)
#line 57 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
					return pInfo;
			}
#line 59 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			return null;
		}

#line 63 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public uint __nRoomId;
#line 64 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public uint __nRoomType;
#line 65 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public InternalString __sRoomType;
#line 67 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public gsServer __pServer;
#line 68 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public Vector<gsServerClient> __pClientVector;
#line 69 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public OwnedVector<gsServerRoom_SyncHandler> __pSyncHandlerVector;
#line 71 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public gsServerRoom(uint nRoomId, string sxRoomType, gsServer pServer)
		{
#line 73 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			__nRoomId = nRoomId;
#line 74 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			__nRoomType = ExternalString.GetChecksum(sxRoomType);
#line 75 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			__sRoomType = new InternalString(sxRoomType);
#line 76 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			__pServer = pServer;
#line 77 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			__pClientVector = new Vector<gsServerClient>();
#line 78 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			__pSyncHandlerVector = new OwnedVector<gsServerRoom_SyncHandler>();
		}

#line 81 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public void __ClientJoin(gsServerClient pClient)
		{
#line 83 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			Assert.Plz(GetClientByClientId(pClient.__nClientId) == null);
#line 85 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			__pClientVector.PushBack(pClient);
#line 86 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			pClient.__pRoomVector.PushBack(this);
			gsBlob pJoinBlob = OnClientJoin(pClient);
			gsBlob pBlob = new gsBlob();
#line 90 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			pBlob.PackUint32(__nRoomId);
#line 91 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			pBlob.PackUint32(__nRoomType);
#line 92 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			pBlob.PackBool(false);
#line 93 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			pBlob.PackBlob(pJoinBlob);
#line 95 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			pClient.Send(null, gsClient.__ROOM_JOIN_HASH, pBlob);
		}

#line 98 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public void __ClientLeave(gsServerClient pClient)
		{
#line 100 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			for (int i = 0; i < __pClientVector.GetSize(); i++)
			{
#line 102 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
				if (__pClientVector.Get(i) == pClient)
				{
#line 104 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
					OnClientLeave(pClient);
#line 105 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
					__pClientVector.Erase(i);
#line 107 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
					for (int j = 0; j < pClient.__pRoomVector.GetSize(); j++)
					{
#line 109 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
						if (pClient.__pRoomVector.Get(j) == this)
						{
#line 111 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
							pClient.__pRoomVector.Erase(j);
							gsBlob pBlob = new gsBlob();
#line 114 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
							pBlob.PackUint32(__nRoomId);
#line 115 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
							pBlob.PackUint32(__nRoomType);
#line 116 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
							pClient.Send(null, gsClient.__ROOM_LEAVE_HASH, pBlob);
#line 117 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
							return;
						}
					}
#line 122 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
					Assert.Plz(false);
				}
			}
#line 127 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			Assert.Plz(false);
		}

#line 18 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		~gsServerRoom()
		{
		}

	}
}

