namespace NumbatLogic
{
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

		public virtual void OnSync(uint nSyncId, uint nSyncType, gsBlob pInBlob, gsServerClient pServerClient)
		{
		}

		public uint __nRoomId;
		public uint __nRoomType;
		public InternalString __sRoomType;
		public gsServer __pServer;
		public Vector<gsServerClient> __pClientVector;
		public gsServerRoom(uint nRoomId, string sxRoomType, gsServer pServer)
		{
			__nRoomId = nRoomId;
			__nRoomType = ExternalString.GetChecksum(sxRoomType);
			__sRoomType = new InternalString(sxRoomType);
			__pServer = pServer;
			__pClientVector = new Vector<gsServerClient>();
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
					return;
				}
			}
			Assert.Plz(false);
		}

		~gsServerRoom()
		{
		}

	}
}

