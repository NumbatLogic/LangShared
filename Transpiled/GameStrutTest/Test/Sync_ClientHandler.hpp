#pragma once

#include "../../GameStrutServer/gsServer.hpp"
#include "../../GameStrutServer/gsServerClient.hpp"
#include "../../GameStrutClient/gsClient.hpp"

namespace NumbatLogic
{
	class gsServerClient;
	class gsClientSocket;
	class gsServer;
	class gsServerRoom;
	class gsClient;
	class gsBlob;
}
#line 0 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
	class Sync_ClientHandler_Server : public gsServer
	{
		public: Sync_ClientHandler_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath);
#line 9 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public: virtual gsServerClient* OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
	};
#line 15 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
	class Sync_ClientHandler_ServerClient : public gsServerClient
	{
		public: Sync_ClientHandler_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
#line 21 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public: virtual void OnInitialJoin();
	};
#line 34 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
	class Sync_ClientHandler_Client : public gsClient
	{
		public: unsigned int m_nTestValue;
#line 38 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public: Sync_ClientHandler_Client(const char* sxAddress, unsigned short nPort, unsigned short nVersion);
#line 43 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		protected: static void OnTest(gsClient* pClient, unsigned int nSyncId, gsBlob* pMessageBlob);
	};
#line 51 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
	class Sync_ClientHandler
	{
		public: static void Run();
	};
}

