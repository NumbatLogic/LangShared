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
#line 0 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClientRoom.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClientRoom.nll"
	class gsClientRoom_SyncHandler
	{
		public: typedef void (SyncHandler)(gsClient* pClient, gsClientRoom* pRoom, unsigned int nSyncId, gsBlob* pMessageBlob);
#line 7 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClientRoom.nll"
		public: unsigned int __nHash;
		public: SyncHandler* __pHandler;
#line 10 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClientRoom.nll"
		public: gsClientRoom_SyncHandler(unsigned int nHash, SyncHandler* pHandler);
	};
#line 17 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClientRoom.nll"
	class gsClientRoom
	{
		public: gsClientRoom(unsigned int nRoomId, const char* sxRoomType, unsigned int nRoomTypeHash, bool bPrimary, gsClient* pClient);
#line 38 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClientRoom.nll"
		public: void RegisterHandler(unsigned int nMessageType, gsClientRoom_SyncHandler::SyncHandler* pHandler);
#line 48 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClientRoom.nll"
		public: gsClientRoom_SyncHandler* __GetSyncHandler(unsigned int nMessageType);
#line 61 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClientRoom.nll"
		public: unsigned int __nRoomId;
		public: InternalString* __sRoomType;
		public: unsigned int __nRoomTypeHash;
		public: bool __bPrimary;
		public: gsClient* __pClient;
		public: OwnedVector<gsClientRoom_SyncHandler*>* __pSyncHandlerVector;
#line 17 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClientRoom.nll"
		public: virtual ~gsClientRoom();
	};
}

