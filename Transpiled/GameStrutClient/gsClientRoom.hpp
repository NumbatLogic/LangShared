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
namespace NumbatLogic
{
	class gsClientRoom_SyncHandler
	{
		public: typedef bool (SyncHandler)(gsClient* pClient, gsClientRoom* pRoom, unsigned int nSyncId, gsBlob* pMessageBlob);
		public: unsigned int __nHash;
		public: SyncHandler* __pHandler;
		public: gsClientRoom_SyncHandler(unsigned int nHash, SyncHandler* pHandler);
	};
	class gsClientRoom
	{
		public: gsClientRoom(unsigned int nRoomId, const char* sxRoomType, unsigned int nRoomTypeHash, bool bPrimary, gsClient* pClient);
		public: virtual void OnSync(unsigned int nSyncId, unsigned int nMessageType, gsBlob* pMessageBlob);
		public: void RegisterHandler(unsigned int nMessageType, gsClientRoom_SyncHandler::SyncHandler* pHandler);
		public: gsClientRoom_SyncHandler* __GetSyncHandler(unsigned int nMessageType);
		public: unsigned int __nRoomId;
		public: InternalString* __sRoomType;
		public: unsigned int __nRoomTypeHash;
		public: bool __bPrimary;
		public: gsClient* __pClient;
		public: OwnedVector<gsClientRoom_SyncHandler*>* __pSyncHandlerVector;
		public: virtual ~gsClientRoom();
	};
}

