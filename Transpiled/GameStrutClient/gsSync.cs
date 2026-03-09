#line 1 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
	class gsSync
	{
#line 6 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public enum Response
		{
			NO_RESPONSE = 0,
			EXPECT_RESPONSE,
			EXPECT_ROOM_CHANGE,
		}

#line 12 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public const byte RESULT_SUCCESS = 0;
#line 14 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public gsSync()
		{
		}

#line 18 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		~gsSync()
		{
#line 20 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			if (__pSyncInner != null)
#line 21 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
				__pSyncInner.__pSync = null;
		}

#line 24 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public bool GetComplete()
		{
#line 26 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			return __pSyncInner != null ? __pSyncInner.__bComplete : false;
		}

#line 29 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public byte GetResult()
		{
#line 31 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			Assert.Plz(GetComplete());
#line 32 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			return __pSyncInner != null ? __pSyncInner.__nResult : RESULT_SUCCESS;
		}

#line 35 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public virtual void OnComplete(byte nResult, gsBlob pBlob)
		{
		}

#line 38 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public gsSyncInner __pSyncInner;
	}
#line 42 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
	class gsSyncInner
	{
#line 44 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public gsSyncInner(gsSync pSync, uint nSyncId, string sxSyncType, gsClientRoom pRoom, gsClient pClient)
		{
#line 46 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			__pSync = pSync;
#line 47 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			__nSyncId = nSyncId;
#line 48 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			__sSyncType = new InternalString(sxSyncType);
#line 49 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			__nSyncType = ExternalString.GetChecksum(sxSyncType);
#line 50 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			__nRoomId = pRoom != null ? pRoom.__nRoomId : 0;
#line 51 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			__nResult = gsSync.RESULT_SUCCESS;
#line 52 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			__eResponse = gsSync.Response.NO_RESPONSE;
		}

#line 55 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		~gsSyncInner()
		{
#line 57 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			if (__pSync != null)
#line 58 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
				__pSync.__pSyncInner = null;
		}

#line 63 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public gsSync __pSync;
#line 65 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public uint __nSyncId;
#line 66 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public InternalString __sSyncType;
#line 67 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public uint __nSyncType;
#line 69 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public bool __bComplete;
#line 70 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public gsSync.Response __eResponse;
#line 71 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public uint __nRoomId;
#line 72 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public byte __nResult;
	}
}

