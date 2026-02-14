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
		public: static const unsigned char RESULT_SUCCESS = 0;
		public: gsSync();
		public: virtual ~gsSync();
		public: bool GetComplete();
		public: unsigned char GetResult();
		public: virtual void OnComplete(unsigned char nResult, bool bAwaitRoomChange, gsBlob* pBlob);
		public: gsSyncInner* __pSyncInner;
	};
	class gsSyncInner
	{
		public: gsSyncInner(gsSync* pSync, unsigned int nSyncId, const char* sxSyncType, gsClientRoom* pRoom, gsClient* pClient);
		public: virtual ~gsSyncInner();
		public: virtual void OnComplete(unsigned char nResult, bool bAwaitRoomChange, gsBlob* pBlob);
		public: gsSync* __pSync;
		public: unsigned int __nSyncId;
		public: InternalString* __sSyncType;
		public: unsigned int __nSyncType;
		public: bool __bComplete;
		public: bool __bAwaitRoomChange;
		public: unsigned int __nRoomId;
		public: unsigned char __nResult;
	};
}

