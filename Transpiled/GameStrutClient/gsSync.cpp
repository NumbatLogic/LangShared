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
namespace NumbatLogic
{
	gsSync::gsSync()
	{
		__pSyncInner = 0;
	}

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

	void gsSync::OnComplete(unsigned char nResult, bool bAwaitRoomChange, gsBlob* pBlob)
	{
	}

	gsSyncInner::gsSyncInner(gsSync* pSync, unsigned int nSyncId, const char* sxSyncType, gsClientRoom* pRoom, gsClient* pClient)
	{
		__pSync = 0;
		__nSyncId = 0;
		__sSyncType = 0;
		__nSyncType = 0;
		__bComplete = false;
		__bAwaitRoomChange = false;
		__nRoomId = 0;
		__nResult = 0;
		__pSync = pSync;
		__nSyncId = nSyncId;
		__sSyncType = new InternalString(sxSyncType);
		__nSyncType = ExternalString::GetChecksum(sxSyncType);
		__nRoomId = pRoom != 0 ? pRoom->__nRoomId : 0;
		__nResult = gsSync::RESULT_SUCCESS;
	}

	gsSyncInner::~gsSyncInner()
	{
		if (__pSync != 0)
			__pSync->__pSyncInner = 0;
		if (__sSyncType) delete __sSyncType;
	}

	void gsSyncInner::OnComplete(unsigned char nResult, bool bAwaitRoomChange, gsBlob* pBlob)
	{
		__nResult = nResult;
		if (__pSync != 0)
			__pSync->OnComplete(nResult, bAwaitRoomChange, pBlob);
		if (bAwaitRoomChange)
			__bAwaitRoomChange = true;
		else
			__bComplete = true;
	}

}

