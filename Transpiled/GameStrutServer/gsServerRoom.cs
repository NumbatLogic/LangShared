namespace NumbatLogic
{
	class gsServerRoom_SyncHandler
	{
		public delegate void SyncHandler(gsServerRoom pRoom, uint nSyncId, uint nSyncType, gsBlob pInBlob, gsServerClient pServerClient);
		public uint __nHash;
		public SyncHandler __pHandler;
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

		public uint __nRoomId;
		public uint __nRoomType;
		public InternalString __sRoomType;
		public gsServer __pServer;
		public Vector<gsServerClient> __pClientVector;
		public OwnedVector<gsServerRoom_SyncHandler> __pSyncHandlerVector;
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
			__pClientVector.PushBack(pClient);
			pClient.__pRoomVector.PushBack(this);
			gsBlob pJoinBlob = OnClientJoin(pClient);
			gsBlob pBlob = new gsBlob();
			pBlob.PackUint32(__nRoomId);
			pBlob.PackUint32(__nRoomType);
			pBlob.PackBool(false);
			pBlob.PackBlob(pJoinBlob);
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
					for (int j = 0; j < pClient.__pRoomVector.GetSize(); j++)
					{
						if (pClient.__pRoomVector.Get(j) == this)
						{
							pClient.__pRoomVector.Erase(j);
							gsBlob pBlob = new gsBlob();
							pBlob.PackUint32(__nRoomId);
							pBlob.PackUint32(__nRoomType);
							pClient.Send(null, gsClient.__ROOM_LEAVE_HASH, pBlob);
							return;
						}
					}
					Assert.Plz(false);
				}
			}
			Assert.Plz(false);
		}

		~gsServerRoom()
		{
		}

	}
}

