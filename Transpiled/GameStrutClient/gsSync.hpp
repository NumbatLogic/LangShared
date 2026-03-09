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
#line 1 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
	class gsSync
	{
#line 6 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: enum Response
		{
			NO_RESPONSE = 0,
			EXPECT_RESPONSE,
			EXPECT_ROOM_CHANGE,
		};

#line 12 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: static const unsigned char RESULT_SUCCESS = 0;
#line 14 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: gsSync();
#line 18 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: virtual ~gsSync();
#line 24 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: bool GetComplete();
#line 29 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: unsigned char GetResult();
#line 35 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: virtual void OnComplete(unsigned char nResult, gsBlob* pBlob);
#line 38 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: gsSyncInner* __pSyncInner;
	};
#line 42 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
	class gsSyncInner
	{
#line 44 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: gsSyncInner(gsSync* pSync, unsigned int nSyncId, const char* sxSyncType, gsClientRoom* pRoom, gsClient* pClient);
#line 55 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: virtual ~gsSyncInner();
#line 63 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: gsSync* __pSync;
#line 65 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: unsigned int __nSyncId;
#line 66 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: InternalString* __sSyncType;
#line 67 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: unsigned int __nSyncType;
#line 69 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: bool __bComplete;
#line 70 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: gsSync::Response __eResponse;
#line 71 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: unsigned int __nRoomId;
#line 72 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: unsigned char __nResult;
	};
}

