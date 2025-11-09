#pragma once

#include "../Vector/OwnedVector.hpp"
#include "gsClientRoom.hpp"
#include "gsSync.hpp"

namespace NumbatLogic
{
	class gsClientRoom;
	class gsSyncInner;
	class gsSync;
	class gsBlob;
	template <class T>
	class OwnedVector;
	class gsClientSocket;
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
		};

		public: gsClient(const char* sxAddress, unsigned short nPort, unsigned short nVersion);
		public: virtual ~gsClient();
		public: void Update();
		public: typedef void (CompleteCallback)();
		public: void SyncSend(gsSync* pSync, const char* sxSyncType, gsBlob* pBlob, bool mayChangeRoom, gsClientRoom* pRoom);
		public: bool GetPending();
		public: virtual gsClientRoom* OnRoomJoin(unsigned int nRoomId, unsigned int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob);
		public: static const unsigned short MAGIC_WORD = 619;
		public: OwnedVector<gsClientRoom*>* __pRoomVector;
		public: gsClientSocket* __pClientSocket;
		public: unsigned short __nVersion;
		public: unsigned int __nClientId;
		public: unsigned int __nLastSyncId;
		public: OwnedVector<gsSyncInner*>* __pSyncInnerVector;
		public: State __eState;
		public: unsigned int __ROOM_JOIN_HASH;
		public: gsSyncInner* GetSyncInnerBySyncId(unsigned int nSyncId);
	};
}

