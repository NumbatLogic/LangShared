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
#line 0 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
	class gsServerRoom_SyncHandler
	{
		public: typedef void (SyncHandler)(gsServerRoom* pRoom, unsigned int nSyncId, unsigned int nSyncType, gsBlob* pInBlob, gsServerClient* pServerClient);
#line 7 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: unsigned int __nHash;
#line 8 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: SyncHandler* __pHandler;
#line 10 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: gsServerRoom_SyncHandler(unsigned int nHash, SyncHandler* pHandler);
	};
#line 17 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
	class gsServerRoom
	{
#line 19 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: gsServerClient* GetClientByClientId(unsigned int nClientId);
#line 30 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		protected: virtual gsBlob* OnClientJoin(gsServerClient* pClient);
#line 35 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		protected: virtual void OnClientLeave(gsServerClient* pClient);
#line 40 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: void RegisterHandler(unsigned int nSyncType, gsServerRoom_SyncHandler::SyncHandler* pHandler);
#line 50 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: gsServerRoom_SyncHandler* __GetSyncHandler(unsigned int nSyncType);
#line 62 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: unsigned int __nRoomId;
#line 63 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: unsigned int __nRoomType;
#line 64 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: InternalString* __sRoomType;
#line 66 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: gsServer* __pServer;
#line 67 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: Vector<gsServerClient*>* __pClientVector;
#line 68 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: OwnedVector<gsServerRoom_SyncHandler*>* __pSyncHandlerVector;
#line 70 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: gsServerRoom(unsigned int nRoomId, const char* sxRoomType, gsServer* pServer);
#line 80 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: void __ClientJoin(gsServerClient* pClient);
#line 97 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: void __ClientLeave(gsServerClient* pClient);
#line 17 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		public: virtual ~gsServerRoom();
	};
}

