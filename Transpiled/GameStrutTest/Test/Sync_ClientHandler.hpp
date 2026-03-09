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
#line 1 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
	class Sync_ClientHandler_Server : public gsServer
	{
#line 6 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public: Sync_ClientHandler_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath);
#line 10 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public: virtual gsServerClient* OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
	};
#line 16 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
	class Sync_ClientHandler_ServerClient : public gsServerClient
	{
#line 18 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public: Sync_ClientHandler_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
#line 22 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public: virtual void OnInitialJoin();
	};
#line 35 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
	class Sync_ClientHandler_Client : public gsClient
	{
#line 37 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public: unsigned int m_nTestValue;
#line 39 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public: Sync_ClientHandler_Client(const char* sxAddress, unsigned short nPort, unsigned short nVersion);
#line 44 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		protected: static void OnTest(gsClient* pClient, unsigned int nSyncId, gsBlob* pMessageBlob);
	};
#line 52 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
	class Sync_ClientHandler
	{
#line 54 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public: static void Run();
	};
}

