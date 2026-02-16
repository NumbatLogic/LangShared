#pragma once

#include "gsClient.hpp"
#include "../Vector/OwnedVector.hpp"
#include "gsClientRoom.hpp"
#include "gsSync.hpp"

namespace NumbatLogic
{
	class gsClient;
	class gsBlob;
	class gsClientRoom;
	class gsSyncInner;
	class gsClient_SyncHandler;
	class gsSync;
	template <class T>
	class OwnedVector;
	class gsClientSocket;
	class InternalString;
}
namespace NumbatLogic
{
	class gsClient_SyncHandler
	{
		public: typedef void (SyncHandler)(gsClient* pClient, unsigned int nSyncId, gsBlob* pMessageBlob);
		public: unsigned int __nHash;
		public: SyncHandler* __pHandler;
		public: gsClient_SyncHandler(unsigned int nHash, SyncHandler* pHandler);
	};
	class gsClient
	{
		public: enum State
		{
			CONNECT,
			HANDSHAKE,
			CONNECTED,
			DISCONNECTED,
			ERRORED,
		};

		public: gsClient(const char* sxAddress, unsigned short nPort, unsigned short nVersion);
		public: virtual ~gsClient();
		public: void Update();
		public: static void __OnRoomJoin(gsClient* pClient, unsigned int nSyncId, gsBlob* pMessageBlob);
		public: static void __OnRoomLeave(gsClient* pClient, unsigned int nSyncId, gsBlob* pMessageBlob);
		public: void RegisterHandler(unsigned int nMessageType, gsClient_SyncHandler::SyncHandler* pHandler);
		public: gsClient_SyncHandler* __GetSyncHandler(unsigned int nMessageType);
		public: typedef void (CompleteCallback)();
		public: void SyncSend(gsSync* pSync, const char* sxSyncType, gsBlob* pBlob, bool mayChangeRoom, gsClientRoom* pRoom);
		public: bool GetPending();
		public: bool HasActiveSync();
		public: bool HasActiveSyncByRoom(gsClientRoom* pRoom);
		public: virtual gsClientRoom* OnRoomJoin(unsigned int nRoomId, unsigned int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob);
		public: static const unsigned short MAGIC_WORD = 619;
		public: OwnedVector<gsClientRoom*>* __pRoomVector;
		public: gsClientSocket* __pClientSocket;
		public: unsigned short __nVersion;
		public: unsigned int __nClientId;
		public: unsigned int __nLastSyncId;
		public: OwnedVector<gsSyncInner*>* __pSyncInnerVector;
		public: OwnedVector<gsClient_SyncHandler*>* __pSyncHandlerVector;
		public: State __eState;
		public: InternalString* __sErrorMessage;
		public: static unsigned int __ROOM_JOIN_HASH;
		public: static unsigned int __ROOM_LEAVE_HASH;
		public: gsClientRoom* GetRoomByRoomId(unsigned int nRoomId);
		public: void ErrorDisconnect(const char* sxErrorMessage);
		public: const char* GetErrorMessage();
		public: gsSyncInner* GetSyncInnerBySyncId(unsigned int nSyncId);
	};
}

