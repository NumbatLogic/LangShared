#pragma once

namespace NumbatLogic
{
	class gsBlob;
	class gsSyncInner;
	class gsSync;
	class gsClientRoom;
	class gsClient;
	class InternalString;
}
namespace NumbatLogic
{
	class gsSync
	{
		public: gsSync();
		public: virtual ~gsSync();
		public: bool GetComplete();
		public: bool GetError();
		public: virtual void OnComplete(gsBlob* pBlob);
		public: gsSyncInner* __pSyncInner;
	};
	class gsSyncInner
	{
		public: gsSyncInner(gsSync* pSync, unsigned int nSyncId, const char* sxSyncType, gsClientRoom* pRoom, gsClient* pClient);
		public: virtual void OnComplete(gsBlob* pBlob);
		public: gsSync* __pSync;
		public: unsigned int __nSyncId;
		public: InternalString* __sSyncType;
		public: int __nSyncType;
		public: bool __bComplete;
		public: bool __bError;
		public: virtual ~gsSyncInner();
	};
}

