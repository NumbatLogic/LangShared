namespace NumbatLogic
{
	class gsClientRoom_SyncHandler
	{
		public delegate bool SyncHandler(gsClient pClient, gsClientRoom pRoom, uint nSyncId, gsBlob pMessageBlob);
		public uint __nHash;
		public SyncHandler __pHandler;
		public gsClientRoom_SyncHandler(uint nHash, SyncHandler pHandler)
		{
			__nHash = nHash;
			__pHandler = pHandler;
		}

	}
	class gsClientRoom
	{
		public gsClientRoom(uint nRoomId, string sxRoomType, uint nRoomTypeHash, bool bPrimary, gsClient pClient)
		{
			__nRoomId = nRoomId;
			if (sxRoomType == null)
			{
				__sRoomType = new InternalString("");
			}
			else
			{
				__sRoomType = new InternalString(sxRoomType);
				uint nTestChecksum = ExternalString.GetChecksum(sxRoomType);
				Assert.Plz(nTestChecksum == nRoomTypeHash);
			}
			__nRoomTypeHash = nRoomTypeHash;
			__bPrimary = bPrimary;
			__pClient = pClient;
			__pSyncHandlerVector = new OwnedVector<gsClientRoom_SyncHandler>();
		}

		public virtual void OnSync(uint nSyncId, uint nMessageType, gsBlob pMessageBlob)
		{
		}

		public void RegisterHandler(uint nMessageType, gsClientRoom_SyncHandler.SyncHandler pHandler)
		{
			if (__GetSyncHandler(nMessageType) != null)
			{
				Console.Log("Room sync handler hash already registered!");
				Assert.Plz(false);
			}
			__pSyncHandlerVector.PushBack(new gsClientRoom_SyncHandler(nMessageType, pHandler));
		}

		public gsClientRoom_SyncHandler __GetSyncHandler(uint nMessageType)
		{
			for (int i = 0; i < __pSyncHandlerVector.GetSize(); i++)
			{
				gsClientRoom_SyncHandler pInfo = __pSyncHandlerVector.Get(i);
				if (pInfo.__nHash == nMessageType)
					return pInfo;
			}
			return null;
		}

		public uint __nRoomId;
		public InternalString __sRoomType;
		public uint __nRoomTypeHash;
		public bool __bPrimary;
		public gsClient __pClient;
		public OwnedVector<gsClientRoom_SyncHandler> __pSyncHandlerVector;
		~gsClientRoom()
		{
		}

	}
}

