namespace NumbatLogic
{
	class gsClientRoom
	{
		public gsClientRoom(uint nRoomId, string sxRoomType, uint nRoomType, bool bPrimary, gsClient pClient)
		{
			__nRoomId = nRoomId;
			if (sxRoomType == null)
			{
				__sRoomType = new InternalString("");
			}
			else
			{
				__sRoomType = new InternalString(sxRoomType);
				int nTestChecksum = ExternalString.GetChecksum(sxRoomType);
				Assert.Plz(nTestChecksum == nRoomType);
			}
			__nRoomTypeHash = nRoomType;
			__bPrimary = bPrimary;
			__pClient = pClient;
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

