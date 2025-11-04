#include "gsSync.hpp"
#include "../../InternalString/CPP/InternalString.hpp"
#include "../../ExternalString/CPP/ExternalString.hpp"

namespace NumbatLogic
{
	class gsSync;
	class gsSyncInner;
	class InternalString;
	class ExternalString;
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

	bool gsSync::GetError()
	{
		return __pSyncInner != 0 ? __pSyncInner->__bError : false;
	}

	void gsSync::OnComplete(gsBlob* pBlob)
	{
	}

	gsSyncInner::gsSyncInner(gsSync* pSync, unsigned int nSyncId, const char* sxSyncType, gsClientRoom* pRoom, gsClient* pClient)
	{
		__pSync = 0;
		__nSyncId = 0;
		__sSyncType = 0;
		__nSyncType = 0;
		__bComplete = false;
		__bError = false;
		__pSync = pSync;
		__nSyncId = nSyncId;
		__sSyncType = new InternalString(sxSyncType);
		__nSyncType = ExternalString::GetChecksum(sxSyncType);
	}

	gsSyncInner::~gsSyncInner()
	{
		if (__pSync != 0)
			__pSync->__pSyncInner = 0;
		if (__sSyncType) delete __sSyncType;
	}

	void gsSyncInner::OnComplete(gsBlob* pBlob)
	{
		if (__pSync != 0)
			__pSync->OnComplete(pBlob);
		__bComplete = true;
	}

}

