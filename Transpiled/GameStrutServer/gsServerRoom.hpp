#pragma once

#include "gsServerRoom.hpp"
#include "../../Vector/CPP/Vector.hpp"
#include "gsServerClient.hpp"
#include "../Vector/OwnedVector.hpp"

namespace NumbatLogic
{
	class gsServerRoom;
	class gsBlob;
	class gsServerClient;
	class gsServerRoom_SyncHandler;
	class InternalString;
	class gsServer;
	template <class T>
	class Vector;
	template <class T>
	class OwnedVector;
}
#line 1 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
	class gsServerRoom_SyncHandler
	{
		public: typedef void (SyncHandler)(gsServerRoom* pRoom, unsigned int nSyncId, unsigned int nSyncType, gsBlob* pInBlob, gsServerClient* pServerClient);
#line 8 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: unsigned int __nHash;
#line 9 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: SyncHandler* __pHandler;
#line 11 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: gsServerRoom_SyncHandler(unsigned int nHash, SyncHandler* pHandler);
	};
#line 18 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
	class gsServerRoom
	{
#line 20 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: gsServerClient* GetClientByClientId(unsigned int nClientId);
#line 31 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		protected: virtual gsBlob* OnClientJoin(gsServerClient* pClient);
#line 36 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		protected: virtual void OnClientLeave(gsServerClient* pClient);
#line 41 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: void RegisterHandler(unsigned int nSyncType, gsServerRoom_SyncHandler::SyncHandler* pHandler);
#line 51 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: gsServerRoom_SyncHandler* __GetSyncHandler(unsigned int nSyncType);
#line 63 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: unsigned int __nRoomId;
#line 64 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: unsigned int __nRoomType;
#line 65 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: InternalString* __sRoomType;
#line 67 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: gsServer* __pServer;
#line 68 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: Vector<gsServerClient*>* __pClientVector;
#line 69 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: OwnedVector<gsServerRoom_SyncHandler*>* __pSyncHandlerVector;
#line 71 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: gsServerRoom(unsigned int nRoomId, const char* sxRoomType, gsServer* pServer);
#line 81 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: void __ClientJoin(gsServerClient* pClient);
#line 98 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: void __ClientLeave(gsServerClient* pClient);
#line 18 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: virtual ~gsServerRoom();
	};
}

