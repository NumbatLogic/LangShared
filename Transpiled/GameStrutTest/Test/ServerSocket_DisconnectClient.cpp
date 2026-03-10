#include "ServerSocket_DisconnectClient.hpp"
#include "../../../GameStrutClient/CPP/gsServerSocket.hpp"
#include "../../../GameStrutClient/CPP/gsClientSocket.hpp"
#include "../GameStrutTestUtil.hpp"
#include "../../../Assert/CPP/Assert.hpp"

namespace NumbatLogic
{
	class ServerSocket_DisconnectClient;
	class gsServerSocket;
	class gsClientSocket;
	class GameStrutTestUtil;
	class Assert;
}
#line 0 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
#line 5 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
	void ServerSocket_DisconnectClient::Run()
	{
		gsServerSocket* pServerSocket = new gsServerSocket();
#line 8 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
		pServerSocket->Start(9877);
		gsClientSocket* pClientSocket = new gsClientSocket();
#line 11 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
		pClientSocket->Connect("localhost", 9877);
#line 13 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
		GameStrutTestUtil::Update(pServerSocket, pClientSocket);
		gsClientSocket* pServerClientSocket = pServerSocket->Accept();
#line 16 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
		Assert::Plz(pServerClientSocket != 0);
#line 18 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
		Assert::Plz(pServerClientSocket->GetConnected());
#line 19 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
		Assert::Plz(pClientSocket->GetConnected());
#line 21 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
		pServerClientSocket->Disconnect();
#line 23 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
		GameStrutTestUtil::Update(pServerSocket, pClientSocket);
#line 25 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
		Assert::Plz(!pClientSocket->GetConnected());
#line 26 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
		Assert::Plz(!pServerClientSocket->GetConnected());
#line 28 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
		pServerSocket->Stop();
		if (pServerSocket) delete pServerSocket;
		if (pClientSocket) delete pClientSocket;
	}

}

