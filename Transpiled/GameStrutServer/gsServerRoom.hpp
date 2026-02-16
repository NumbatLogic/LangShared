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
namespace NumbatLogic
{
	class gsServerRoom_SyncHandler
	{
		public: typedef void (SyncHandler)(gsServerRoom* pRoom, unsigned int nSyncId, unsigned int nSyncType, gsBlob* pInBlob, gsServerClient* pServerClient);
		public: unsigned int __nHash;
		public: SyncHandler* __pHandler;
		public: gsServerRoom_SyncHandler(unsigned int nHash, SyncHandler* pHandler);
	};
	class gsServerRoom
	{
		public: gsServerClient* GetClientByClientId(unsigned int nClientId);
		protected: virtual gsBlob* OnClientJoin(gsServerClient* pClient);
		protected: virtual void OnClientLeave(gsServerClient* pClient);
		public: void RegisterHandler(unsigned int nSyncType, gsServerRoom_SyncHandler::SyncHandler* pHandler);
		public: gsServerRoom_SyncHandler* __GetSyncHandler(unsigned int nSyncType);
		public: unsigned int __nRoomId;
		public: unsigned int __nRoomType;
		public: InternalString* __sRoomType;
		public: gsServer* __pServer;
		public: Vector<gsServerClient*>* __pClientVector;
		public: OwnedVector<gsServerRoom_SyncHandler*>* __pSyncHandlerVector;
		public: gsServerRoom(unsigned int nRoomId, const char* sxRoomType, gsServer* pServer);
		public: void __ClientJoin(gsServerClient* pClient);
		public: void __ClientLeave(gsServerClient* pClient);
		public: virtual ~gsServerRoom();
	};
}

