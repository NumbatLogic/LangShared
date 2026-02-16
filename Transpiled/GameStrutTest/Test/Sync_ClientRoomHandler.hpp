#pragma once

#include "../../GameStrutServer/gsServer.hpp"
#include "../../GameStrutServer/gsServerClient.hpp"
#include "../../GameStrutClient/gsClientRoom.hpp"
#include "../../GameStrutClient/gsClient.hpp"

namespace NumbatLogic
{
	class gsServerClient;
	class gsClientSocket;
	class gsServer;
	class gsBlob;
	class gsClient;
	class gsClientRoom;
}
namespace NumbatLogic
{
	class Sync_ClientRoomHandler_Server : public gsServer
	{
		public: Sync_ClientRoomHandler_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath);
		public: virtual gsServerClient* OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
	};
	class Sync_ClientRoomHandler_ServerClient : public gsServerClient
	{
		public: Sync_ClientRoomHandler_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
		public: virtual void OnInitialJoin();
	};
	class Sync_ClientRoomHandler_ClientRoom : public gsClientRoom
	{
		public: static const char* ROOM_TYPE;
		public: static const unsigned int ROOM_TYPE_HASH = 3638174234;
		public: unsigned int m_nTestValue;
		public: Sync_ClientRoomHandler_ClientRoom(unsigned int nRoomId, bool bPrimary, gsBlob* pJoinBlob, gsClient* pClient);
		protected: static bool OnRoomTest(gsClient* pClient, gsClientRoom* pRoom, unsigned int nSyncId, gsBlob* pMessageBlob);
	};
	class Sync_ClientRoomHandler_Client : public gsClient
	{
		public: Sync_ClientRoomHandler_Client(const char* sxAddress, unsigned short nPort, unsigned short nVersion);
		public: virtual gsClientRoom* OnRoomJoin(unsigned int nRoomId, unsigned int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob);
	};
	class Sync_ClientRoomHandler
	{
		public: static void Run();
	};
}

