namespace NumbatLogic
{
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
		}

		public virtual void OnSync(uint nSyncId, uint nMessageType, gsBlob pMessageBlob)
		{
		}

		public uint __nRoomId;
		public InternalString __sRoomType;
		public uint __nRoomTypeHash;
		public bool __bPrimary;
		public gsClient __pClient;
		~gsClientRoom()
		{
		}

	}
}

