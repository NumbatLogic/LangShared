#pragma once

#include "../../GameStrutServer/gsServer.hpp"
#include "../../GameStrutServer/gsServerClient.hpp"

namespace NumbatLogic
{
	class gsServerClient;
	class gsClientSocket;
	class gsServer;
}
#line 0 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
	class Sync_ClientHandler_Error_Server : public gsServer
	{
#line 5 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		public: Sync_ClientHandler_Error_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath);
#line 9 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		public: virtual gsServerClient* OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
	};
#line 15 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
	class Sync_ClientHandler_Error_ServerClient : public gsServerClient
	{
#line 17 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		public: Sync_ClientHandler_Error_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
#line 21 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		public: virtual void OnInitialJoin();
	};
#line 29 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
	class Sync_ClientHandler_Error
	{
#line 31 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		public: static void Run();
	};
}

