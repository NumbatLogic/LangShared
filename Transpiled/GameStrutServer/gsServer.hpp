#pragma once

#include "../Vector/OwnedVector.hpp"
#include "gsServerClient.hpp"
#include "gsServerRoom.hpp"

namespace NumbatLogic
{
	class gsServerRoom;
	class gsServerClient;
	class gsClientSocket;
	class gsServer;
	class gsBlob;
	class InternalString;
	class gsServerSocket;
	template <class T>
	class OwnedVector;
}
namespace NumbatLogic
{
	class gsServer
	{
		public: gsServer(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath);
		public: virtual ~gsServer();
		public: void Update();
		public: bool Pending();
		public: virtual gsServerClient* OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
		public: virtual gsServerRoom* OnCreateRoom(unsigned int nRoomId, unsigned int nRoomType, gsBlob* pCreateBlob);
		public: virtual void Auth(gsBlob* pAuthBlob, gsClientSocket* pClientSocket);
		public: InternalString* __sAddress;
		public: unsigned short __nPort;
		public: unsigned short __nVersion;
		public: gsServerSocket* __pServerSocket;
		public: OwnedVector<gsServerClient*>* __pClientVector;
		public: OwnedVector<gsServerRoom*>* __pRoomVector;
		public: unsigned int __nLastClientId;
		public: unsigned int __nLastRoomId;
		public: void __ClientJoin(gsServerClient* pClient, gsServerRoom* pRoom);
		public: gsServerRoom* __CreateRoom(const char* sxRoomType, gsBlob* pCreateBlob);
	};
}

