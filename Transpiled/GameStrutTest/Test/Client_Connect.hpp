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
#line 0 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
	class Client_Connect_Server : public gsServer
	{
		public: Client_Connect_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath);
#line 9 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		public: virtual gsServerClient* OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
	};
#line 15 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
	class Client_Connect_ServerClient : public gsServerClient
	{
		public: Client_Connect_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
#line 21 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		public: virtual void OnInitialJoin();
	};
#line 30 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
	class Client_Connect_Client : public gsClient
	{
		public: Client_Connect_Client(const char* sxAddress, unsigned short nPort, unsigned short nVersion);
#line 36 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		public: virtual gsClientRoom* OnRoomJoin(unsigned int nRoomId, unsigned int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob);
	};
#line 43 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
	class Client_Connect
	{
		public: static void Run();
	};
}

