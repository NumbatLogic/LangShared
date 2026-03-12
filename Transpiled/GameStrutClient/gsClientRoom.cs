#line 1 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
	class gsClientRoom_SyncHandler
	{
		public delegate void SyncHandler(gsClient pClient, gsClientRoom pRoom, uint nSyncId, gsBlob pMessageBlob);
#line 7 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public uint __nHash;
#line 8 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public SyncHandler __pHandler;
#line 10 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public gsClientRoom_SyncHandler(uint nHash, SyncHandler pHandler)
		{
#line 12 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			__nHash = nHash;
#line 13 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			__pHandler = pHandler;
		}

	}
#line 17 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
	class gsClientRoom
	{
#line 19 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public gsClientRoom(uint nRoomId, string sxRoomType, uint nRoomTypeHash, bool bPrimary, gsClient pClient)
		{
#line 21 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			__nRoomId = nRoomId;
#line 22 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			if (sxRoomType == null)
			{
#line 24 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
				__sRoomType = new InternalString("");
			}
			else
			{
#line 28 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
				__sRoomType = new InternalString(sxRoomType);
#line 29 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
				uint nTestChecksum = ExternalString.GetChecksum(sxRoomType);
#line 30 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
				Assert.Plz(nTestChecksum == nRoomTypeHash);
			}
#line 32 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			__nRoomTypeHash = nRoomTypeHash;
#line 33 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			__bPrimary = bPrimary;
#line 34 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			__pClient = pClient;
#line 35 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			__pSyncHandlerVector = new OwnedVector<gsClientRoom_SyncHandler>();
		}

#line 38 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public void RegisterHandler(uint nMessageType, gsClientRoom_SyncHandler.SyncHandler pHandler)
		{
#line 40 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			if (__GetSyncHandler(nMessageType) != null)
			{
#line 42 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
				Console.Log("Room sync handler hash already registered!");
#line 43 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
				Assert.Plz(false);
			}
#line 45 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			__pSyncHandlerVector.PushBack(new gsClientRoom_SyncHandler(nMessageType, pHandler));
		}

#line 48 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public gsClientRoom_SyncHandler __GetSyncHandler(uint nMessageType)
		{
#line 50 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			for (int i = 0; i < __pSyncHandlerVector.GetSize(); i++)
			{
#line 52 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
				gsClientRoom_SyncHandler pInfo = __pSyncHandlerVector.Get(i);
#line 53 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
				if (pInfo.__nHash == nMessageType)
#line 54 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
					return pInfo;
			}
#line 56 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			return null;
		}

#line 61 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public uint __nRoomId;
#line 62 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public InternalString __sRoomType;
#line 63 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public uint __nRoomTypeHash;
#line 64 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public bool __bPrimary;
#line 65 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public gsClient __pClient;
#line 66 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public OwnedVector<gsClientRoom_SyncHandler> __pSyncHandlerVector;
#line 17 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		~gsClientRoom()
		{
		}

	}
}

