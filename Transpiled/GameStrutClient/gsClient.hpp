#pragma once

#include "../Vector/OwnedVector.hpp"
#include "gsClientRoom.hpp"
#include "gsSync.hpp"

namespace NumbatLogic
{
	class gsClientRoom;
	class gsSyncInner;
	class gsBlob;
	class gsSync;
	template <class T>
	class OwnedVector;
	class gsClientSocket;
	class InternalString;
}
namespace NumbatLogic
{
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
		public: virtual bool OnSync(unsigned int nSyncId, unsigned int nMessageType, gsBlob* pMessageBlob);
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

