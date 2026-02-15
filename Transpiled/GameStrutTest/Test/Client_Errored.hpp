#pragma once

#include "../../GameStrutServer/gsServer.hpp"
#include "../../GameStrutServer/gsServerClient.hpp"
#include "../../GameStrutClient/gsClient.hpp"

namespace NumbatLogic
{
	class gsServerClient;
	class gsClientSocket;
	class gsServer;
	class gsClient;
	class gsClientRoom;
	class gsBlob;
}
namespace NumbatLogic
{
	class Client_Errored_Server : public gsServer
	{
		public: Client_Errored_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath);
		public: virtual gsServerClient* OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
	};
	class Client_Errored_ServerClient : public gsServerClient
	{
		public: Client_Errored_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
		public: virtual void OnInitialJoin();
	};
	class Client_Errored_Client : public gsClient
	{
		public: Client_Errored_Client(const char* sxAddress, unsigned short nPort, unsigned short nVersion);
		public: virtual gsClientRoom* OnRoomJoin(unsigned int nRoomId, unsigned int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob);
	};
	class Client_Errored
	{
		public: static void Run();
	};
}

