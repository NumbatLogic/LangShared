#pragma once

#include "gsSync.hpp"

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
		public: enum Response
		{
			NO_RESPONSE = 0,
			EXPECT_RESPONSE,
			EXPECT_ROOM_CHANGE,
		};

		public: static const unsigned char RESULT_SUCCESS = 0;
		public: gsSync();
		public: virtual ~gsSync();
		public: bool GetComplete();
		public: unsigned char GetResult();
		public: virtual void OnComplete(unsigned char nResult, gsBlob* pBlob);
		public: gsSyncInner* __pSyncInner;
	};
	class gsSyncInner
	{
		public: gsSyncInner(gsSync* pSync, unsigned int nSyncId, const char* sxSyncType, gsClientRoom* pRoom, gsClient* pClient);
		public: virtual ~gsSyncInner();
		public: gsSync* __pSync;
		public: unsigned int __nSyncId;
		public: InternalString* __sSyncType;
		public: unsigned int __nSyncType;
		public: bool __bComplete;
		public: gsSync::Response __eResponse;
		public: unsigned int __nRoomId;
		public: unsigned char __nResult;
	};
}

