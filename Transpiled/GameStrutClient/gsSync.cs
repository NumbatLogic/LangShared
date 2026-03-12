#line 1 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
	class gsSync
	{
#line 5 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public enum Response
		{
			NO_RESPONSE = 0,
			EXPECT_RESPONSE,
			EXPECT_ROOM_CHANGE,
		}

#line 11 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public const byte RESULT_SUCCESS = 0;
#line 13 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public gsSync()
		{
		}

#line 17 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		~gsSync()
		{
#line 19 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			if (__pSyncInner != null)
#line 20 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
				__pSyncInner.__pSync = null;
		}

#line 23 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public bool GetComplete()
		{
#line 25 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			return __pSyncInner != null ? __pSyncInner.__bComplete : false;
		}

#line 28 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public byte GetResult()
		{
#line 30 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			Assert.Plz(GetComplete());
#line 31 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			return __pSyncInner != null ? __pSyncInner.__nResult : RESULT_SUCCESS;
		}

#line 34 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public virtual void OnComplete(byte nResult, gsBlob pBlob)
		{
		}

#line 37 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public gsSyncInner __pSyncInner;
	}
#line 41 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
	class gsSyncInner
	{
#line 43 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public gsSyncInner(gsSync pSync, uint nSyncId, string sxSyncType, gsClientRoom pRoom, gsClient pClient)
		{
#line 45 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			__pSync = pSync;
#line 46 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			__nSyncId = nSyncId;
#line 47 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			__sSyncType = new InternalString(sxSyncType);
#line 48 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			__nSyncType = ExternalString.GetChecksum(sxSyncType);
#line 49 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			__nRoomId = pRoom != null ? pRoom.__nRoomId : 0;
#line 50 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			__nResult = gsSync.RESULT_SUCCESS;
#line 51 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			__eResponse = gsSync.Response.NO_RESPONSE;
		}

#line 54 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		~gsSyncInner()
		{
#line 56 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			if (__pSync != null)
#line 57 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
				__pSync.__pSyncInner = null;
		}

#line 62 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public gsSync __pSync;
#line 64 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public uint __nSyncId;
#line 65 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public InternalString __sSyncType;
#line 66 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public uint __nSyncType;
#line 68 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public bool __bComplete;
#line 69 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public gsSync.Response __eResponse;
#line 70 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public uint __nRoomId;
#line 71 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public byte __nResult;
	}
}

