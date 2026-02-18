namespace NumbatLogic
{
	class gsSync
	{
		public enum Response
		{
			NO_RESPONSE = 0,
			EXPECT_RESPONSE,
			EXPECT_ROOM_CHANGE,
		}

		public const byte RESULT_SUCCESS = 0;
		public gsSync()
		{
		}

		~gsSync()
		{
			if (__pSyncInner != null)
				__pSyncInner.__pSync = null;
		}

		public bool GetComplete()
		{
			return __pSyncInner != null ? __pSyncInner.__bComplete : false;
		}

		public byte GetResult()
		{
			Assert.Plz(GetComplete());
			return __pSyncInner != null ? __pSyncInner.__nResult : RESULT_SUCCESS;
		}

		public virtual void OnComplete(byte nResult, gsBlob pBlob)
		{
		}

		public gsSyncInner __pSyncInner;
	}
	class gsSyncInner
	{
		public gsSyncInner(gsSync pSync, uint nSyncId, string sxSyncType, gsClientRoom pRoom, gsClient pClient)
		{
			__pSync = pSync;
			__nSyncId = nSyncId;
			__sSyncType = new InternalString(sxSyncType);
			__nSyncType = ExternalString.GetChecksum(sxSyncType);
			__nRoomId = pRoom != null ? pRoom.__nRoomId : 0;
			__nResult = gsSync.RESULT_SUCCESS;
			__eResponse = gsSync.Response.NO_RESPONSE;
		}

		~gsSyncInner()
		{
			if (__pSync != null)
				__pSync.__pSyncInner = null;
		}

		public gsSync __pSync;
		public uint __nSyncId;
		public InternalString __sSyncType;
		public uint __nSyncType;
		public bool __bComplete;
		public gsSync.Response __eResponse;
		public uint __nRoomId;
		public byte __nResult;
	}
}

