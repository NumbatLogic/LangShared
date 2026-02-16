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
	class gsBlob;
}
namespace NumbatLogic
{
	class Sync_FromServer_Server : public gsServer
	{
		public: Sync_FromServer_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath);
		public: virtual gsServerClient* OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
	};
	class Sync_FromServer_ServerClient : public gsServerClient
	{
		public: Sync_FromServer_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
		public: virtual void OnInitialJoin();
	};
	class Sync_FromServer_Client : public gsClient
	{
		public: unsigned int m_nTestValue;
		public: Sync_FromServer_Client(const char* sxAddress, unsigned short nPort, unsigned short nVersion);
		protected: static bool OnTest(gsClient* pClient, unsigned int nSyncId, gsBlob* pMessageBlob);
	};
	class Sync_FromServer
	{
		public: static void Run();
	};
}

