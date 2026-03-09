#pragma once

#include "../../GameStrutServer/gsServer.hpp"
#include "../../GameStrutServer/gsServerClient.hpp"

namespace NumbatLogic
{
	class gsServerClient;
	class gsClientSocket;
	class gsServer;
}
#line 1 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
	class Sync_ClientHandler_Error_Server : public gsServer
	{
#line 6 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		public: Sync_ClientHandler_Error_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath);
#line 10 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		public: virtual gsServerClient* OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
	};
#line 16 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
	class Sync_ClientHandler_Error_ServerClient : public gsServerClient
	{
#line 18 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		public: Sync_ClientHandler_Error_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
#line 22 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		public: virtual void OnInitialJoin();
	};
#line 30 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
	class Sync_ClientHandler_Error
	{
#line 32 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		public: static void Run();
	};
}

