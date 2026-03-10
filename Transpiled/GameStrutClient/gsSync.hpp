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
#line 0 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
	class gsSync
	{
#line 5 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: enum Response
		{
			NO_RESPONSE = 0,
			EXPECT_RESPONSE,
			EXPECT_ROOM_CHANGE,
		};

#line 11 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: static const unsigned char RESULT_SUCCESS = 0;
#line 13 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: gsSync();
#line 17 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: virtual ~gsSync();
#line 23 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: bool GetComplete();
#line 28 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: unsigned char GetResult();
#line 34 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: virtual void OnComplete(unsigned char nResult, gsBlob* pBlob);
#line 37 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: gsSyncInner* __pSyncInner;
	};
#line 41 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
	class gsSyncInner
	{
#line 43 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: gsSyncInner(gsSync* pSync, unsigned int nSyncId, const char* sxSyncType, gsClientRoom* pRoom, gsClient* pClient);
#line 54 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: virtual ~gsSyncInner();
#line 62 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: gsSync* __pSync;
#line 64 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: unsigned int __nSyncId;
#line 65 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: InternalString* __sSyncType;
#line 66 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: unsigned int __nSyncType;
#line 68 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: bool __bComplete;
#line 69 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: gsSync::Response __eResponse;
#line 70 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: unsigned int __nRoomId;
#line 71 "../LangShared/Transpiled/GameStrutClient/gsSync.nll"
		public: unsigned char __nResult;
	};
}

