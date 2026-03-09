#pragma once

#include "gsClientRoom.hpp"
#include "../Vector/OwnedVector.hpp"

namespace NumbatLogic
{
	class gsClient;
	class gsClientRoom;
	class gsBlob;
	class gsClientRoom_SyncHandler;
	class InternalString;
	template <class T>
	class OwnedVector;
}
#line 1 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
	class gsClientRoom_SyncHandler
	{
		public: typedef void (SyncHandler)(gsClient* pClient, gsClientRoom* pRoom, unsigned int nSyncId, gsBlob* pMessageBlob);
#line 8 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public: unsigned int __nHash;
#line 9 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public: SyncHandler* __pHandler;
#line 11 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public: gsClientRoom_SyncHandler(unsigned int nHash, SyncHandler* pHandler);
	};
#line 18 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
	class gsClientRoom
	{
#line 20 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public: gsClientRoom(unsigned int nRoomId, const char* sxRoomType, unsigned int nRoomTypeHash, bool bPrimary, gsClient* pClient);
#line 39 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public: void RegisterHandler(unsigned int nMessageType, gsClientRoom_SyncHandler::SyncHandler* pHandler);
#line 49 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public: gsClientRoom_SyncHandler* __GetSyncHandler(unsigned int nMessageType);
#line 62 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public: unsigned int __nRoomId;
#line 63 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public: InternalString* __sRoomType;
#line 64 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public: unsigned int __nRoomTypeHash;
#line 65 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public: bool __bPrimary;
#line 66 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public: gsClient* __pClient;
#line 67 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public: OwnedVector<gsClientRoom_SyncHandler*>* __pSyncHandlerVector;
#line 18 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		public: virtual ~gsClientRoom();
	};
}

