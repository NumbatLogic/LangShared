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
	class Client_Connect_Server : public gsServer
	{
		public: Client_Connect_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath);
		public: virtual gsServerClient* OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
	};
	class Client_Connect_ServerClient : public gsServerClient
	{
		public: Client_Connect_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
		public: virtual void OnInitialJoin();
	};
	class Client_Connect_Client : public gsClient
	{
		public: Client_Connect_Client(const char* sxAddress, unsigned short nPort, unsigned short nVersion);
		public: virtual gsClientRoom* OnRoomJoin(unsigned int nRoomId, int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob);
	};
	class Client_Connect
	{
		public: static void Run();
	};
}

