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
	class gsClientRoom;
	class gsBlob;
}
#line 1 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
	class Client_Connect_Server : public gsServer
	{
#line 6 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		public: Client_Connect_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath);
#line 10 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		public: virtual gsServerClient* OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
	};
#line 16 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
	class Client_Connect_ServerClient : public gsServerClient
	{
#line 18 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		public: Client_Connect_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
#line 22 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		public: virtual void OnInitialJoin();
	};
#line 31 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
	class Client_Connect_Client : public gsClient
	{
#line 33 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		public: Client_Connect_Client(const char* sxAddress, unsigned short nPort, unsigned short nVersion);
#line 37 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		public: virtual gsClientRoom* OnRoomJoin(unsigned int nRoomId, unsigned int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob);
	};
#line 44 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
	class Client_Connect
	{
#line 46 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		public: static void Run();
	};
}

