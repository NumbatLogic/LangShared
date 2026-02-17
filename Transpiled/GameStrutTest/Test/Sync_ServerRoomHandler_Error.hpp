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
	class gsSync;
	class gsClientRoom;
}
namespace NumbatLogic
{
	class Sync_ServerRoomHandler_Error_Server : public gsServer
	{
		public: Sync_ServerRoomHandler_Error_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath);
		public: virtual gsServerClient* OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
	};
	class Sync_ServerRoomHandler_Error_ServerClient : public gsServerClient
	{
		public: Sync_ServerRoomHandler_Error_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
		public: virtual void OnInitialJoin();
	};
	class Sync_ServerRoomHandler_Error_ClientRoom : public gsClientRoom
	{
		public: static const char* ROOM_TYPE;
		public: static const unsigned int ROOM_TYPE_HASH = 3685084777;
		public: Sync_ServerRoomHandler_Error_ClientRoom(unsigned int nRoomId, bool bPrimary, gsBlob* pJoinBlob, gsClient* pClient);
	};
	class Sync_ServerRoomHandler_Error_Client : public gsClient
	{
		public: gsSync* __pDummySync;
		public: Sync_ServerRoomHandler_Error_Client(const char* sxAddress, unsigned short nPort, unsigned short nVersion);
		public: virtual gsClientRoom* OnRoomJoin(unsigned int nRoomId, unsigned int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob);
		public: virtual ~Sync_ServerRoomHandler_Error_Client();
	};
	class Sync_ServerRoomHandler_Error
	{
		public: static void Run();
	};
}

