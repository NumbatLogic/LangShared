#line 1 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsSync.nll"
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

#line 11 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsSync.nll"
		public const byte RESULT_SUCCESS = 0;
#line 13 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsSync.nll"
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

#line 37 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsSync.nll"
		public gsSyncInner __pSyncInner;
	}
#line 41 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsSync.nll"
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

#line 62 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsSync.nll"
		public gsSync __pSync;
#line 64 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsSync.nll"
		public uint __nSyncId;
		public InternalString __sSyncType;
		public uint __nSyncType;
#line 68 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsSync.nll"
		public bool __bComplete;
		public gsSync.Response __eResponse;
		public uint __nRoomId;
		public byte __nResult;
	}
}

