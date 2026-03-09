#line 1 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
	class gsClientRoom_SyncHandler
	{
		public delegate void SyncHandler(gsClient pClient, gsClientRoom pRoom, uint nSyncId, gsBlob pMessageBlob);
#line 8 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public uint __nHash;
#line 9 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public SyncHandler __pHandler;
#line 11 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public gsClientRoom_SyncHandler(uint nHash, SyncHandler pHandler)
		{
#line 13 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			__nHash = nHash;
#line 14 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			__pHandler = pHandler;
		}

	}
#line 18 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
	class gsClientRoom
	{
#line 20 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public gsClientRoom(uint nRoomId, string sxRoomType, uint nRoomTypeHash, bool bPrimary, gsClient pClient)
		{
#line 22 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			__nRoomId = nRoomId;
#line 23 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			if (sxRoomType == null)
			{
#line 25 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
				__sRoomType = new InternalString("");
			}
			else
			{
#line 29 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
				__sRoomType = new InternalString(sxRoomType);
				uint nTestChecksum = ExternalString.GetChecksum(sxRoomType);
#line 31 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
				Assert.Plz(nTestChecksum == nRoomTypeHash);
			}
#line 33 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			__nRoomTypeHash = nRoomTypeHash;
#line 34 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			__bPrimary = bPrimary;
#line 35 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			__pClient = pClient;
#line 36 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			__pSyncHandlerVector = new OwnedVector<gsClientRoom_SyncHandler>();
		}

#line 39 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public void RegisterHandler(uint nMessageType, gsClientRoom_SyncHandler.SyncHandler pHandler)
		{
#line 41 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			if (__GetSyncHandler(nMessageType) != null)
			{
#line 43 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
				Console.Log("Room sync handler hash already registered!");
#line 44 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
				Assert.Plz(false);
			}
#line 46 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			__pSyncHandlerVector.PushBack(new gsClientRoom_SyncHandler(nMessageType, pHandler));
		}

#line 49 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public gsClientRoom_SyncHandler __GetSyncHandler(uint nMessageType)
		{
#line 51 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			for (int i = 0; i < __pSyncHandlerVector.GetSize(); i++)
			{
				gsClientRoom_SyncHandler pInfo = __pSyncHandlerVector.Get(i);
#line 54 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
				if (pInfo.__nHash == nMessageType)
#line 55 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
					return pInfo;
			}
#line 57 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			return null;
		}

#line 62 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public uint __nRoomId;
#line 63 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public InternalString __sRoomType;
#line 64 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public uint __nRoomTypeHash;
#line 65 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public bool __bPrimary;
#line 66 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public gsClient __pClient;
#line 67 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public OwnedVector<gsClientRoom_SyncHandler> __pSyncHandlerVector;
#line 18 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		~gsClientRoom()
		{
		}

	}
}

