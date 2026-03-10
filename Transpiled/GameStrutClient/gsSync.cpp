#include "gsSync.hpp"
#include "../../Assert/CPP/Assert.hpp"
#include "../../InternalString/CPP/InternalString.hpp"
#include "../../ExternalString/CPP/ExternalString.hpp"
#include "gsClientRoom.hpp"

namespace NumbatLogic
{
	class gsSync;
	class gsSyncInner;
	class Assert;
	class InternalString;
	class ExternalString;
	class gsClientRoom;
}
#line 0 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
#line 13 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
	gsSync::gsSync()
	{
		__pSyncInner = 0;
	}

#line 17 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
	gsSync::~gsSync()
	{
#line 19 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		if (__pSyncInner != 0)
#line 20 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			__pSyncInner->__pSync = 0;
	}

#line 23 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
	bool gsSync::GetComplete()
	{
#line 25 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		return __pSyncInner != 0 ? __pSyncInner->__bComplete : false;
	}

#line 28 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
	unsigned char gsSync::GetResult()
	{
#line 30 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		Assert::Plz(GetComplete());
#line 31 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		return __pSyncInner != 0 ? __pSyncInner->__nResult : RESULT_SUCCESS;
	}

#line 34 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
	void gsSync::OnComplete(unsigned char nResult, gsBlob* pBlob)
	{
	}

#line 41 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
#line 43 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
	gsSyncInner::gsSyncInner(gsSync* pSync, unsigned int nSyncId, const char* sxSyncType, gsClientRoom* pRoom, gsClient* pClient)
	{
		__pSync = 0;
		__nSyncId = 0;
		__sSyncType = 0;
		__nSyncType = 0;
		__bComplete = false;
		__eResponse = gsSync::Response::NO_RESPONSE;
		__nRoomId = 0;
		__nResult = 0;
#line 45 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		__pSync = pSync;
#line 46 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		__nSyncId = nSyncId;
#line 47 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		__sSyncType = new InternalString(sxSyncType);
#line 48 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		__nSyncType = ExternalString::GetChecksum(sxSyncType);
#line 49 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		__nRoomId = pRoom != 0 ? pRoom->__nRoomId : 0;
#line 50 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		__nResult = gsSync::RESULT_SUCCESS;
#line 51 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		__eResponse = gsSync::Response::NO_RESPONSE;
	}

#line 54 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
	gsSyncInner::~gsSyncInner()
	{
#line 56 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		if (__pSync != 0)
#line 57 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
			__pSync->__pSyncInner = 0;
		if (__sSyncType) delete __sSyncType;
	}

}

