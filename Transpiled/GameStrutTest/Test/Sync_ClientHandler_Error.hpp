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
		public: Sync_ClientHandler_Error_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath);
#line 9 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		public: virtual gsServerClient* OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
	};
#line 15 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
	class Sync_ClientHandler_Error_ServerClient : public gsServerClient
	{
		public: Sync_ClientHandler_Error_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
#line 21 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		public: virtual void OnInitialJoin();
	};
#line 29 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
	class Sync_ClientHandler_Error
	{
		public: static void Run();
	};
}

