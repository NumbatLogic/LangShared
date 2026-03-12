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
		if (__pSyncInner != 0)
			__pSyncInner->__pSync = 0;
	}

	bool gsSync::GetComplete()
	{
		return __pSyncInner != 0 ? __pSyncInner->__bComplete : false;
	}

	unsigned char gsSync::GetResult()
	{
		Assert::Plz(GetComplete());
		return __pSyncInner != 0 ? __pSyncInner->__nResult : RESULT_SUCCESS;
	}

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
		__nSyncId = nSyncId;
		__sSyncType = new InternalString(sxSyncType);
		__nSyncType = ExternalString::GetChecksum(sxSyncType);
		__nRoomId = pRoom != 0 ? pRoom->__nRoomId : 0;
		__nResult = gsSync::RESULT_SUCCESS;
		__eResponse = gsSync::Response::NO_RESPONSE;
	}

	gsSyncInner::~gsSyncInner()
	{
		if (__pSync != 0)
			__pSync->__pSyncInner = 0;
		if (__sSyncType) delete __sSyncType;
	}

}

