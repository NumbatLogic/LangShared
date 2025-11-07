#pragma once

#include "../../Vector/CPP/Vector.hpp"
#include "gsServerClient.hpp"

namespace NumbatLogic
{
	class gsServerClient;
	class gsBlob;
	class InternalString;
	class gsServer;
	template <class T>
	class Vector;
}
namespace NumbatLogic
{
	class gsServerRoom
	{
		public: gsServerClient* GetClientByClientId(unsigned short nClientId);
		protected: virtual gsBlob* OnClientJoin(gsServerClient* pClient);
		protected: virtual void OnClientLeave(gsServerClient* pClient);
		public: virtual void OnSync(unsigned int nSyncId, unsigned int nSyncType, gsBlob* pInBlob, gsServerClient* pServerClient);
		public: unsigned int __nRoomId;
		public: unsigned int __nRoomType;
		public: InternalString* __sRoomType;
		public: bool __bPrimary;
		public: gsServer* __pServer;
		public: Vector<gsServerClient*>* __pClientVector;
		public: gsServerRoom(unsigned int nRoomId, const char* sxRoomType, gsServer* pServer);
		public: void __ClientJoin(gsServerClient* pClient);
		public: void __ClientLeave(gsServerClient* pClient);
		public: virtual ~gsServerRoom();
	};
}

