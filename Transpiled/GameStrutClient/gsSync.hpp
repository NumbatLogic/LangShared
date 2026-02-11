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
		public: virtual ~gsSyncInner();
		public: virtual void OnComplete(gsBlob* pBlob, bool bAwaitRoomChange);
		public: gsSync* __pSync;
		public: unsigned int __nSyncId;
		public: InternalString* __sSyncType;
		public: unsigned int __nSyncType;
		public: bool __bComplete;
		public: bool __bAwaitRoomChange;
		public: unsigned int __nRoomId;
	};
}

