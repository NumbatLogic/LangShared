#include "ServerSocket_DisconnectClient.hpp"
#include "../../../Source/GameStrutClient/CPP/gsServerSocket.hpp"
#include "../../../Source/GameStrutClient/CPP/gsClientSocket.hpp"
#include "../GameStrutTestUtil.hpp"
#include "../../../Source/Assert/CPP/Assert.hpp"

namespace NumbatLogic
{
	class ServerSocket_DisconnectClient;
	class gsServerSocket;
	class gsClientSocket;
	class GameStrutTestUtil;
	class Assert;
}
#line 0 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
#line 5 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
	void ServerSocket_DisconnectClient::Run()
	{
		gsServerSocket* pServerSocket = new gsServerSocket();
		pServerSocket->Start(9877);
#line 10 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
		gsClientSocket* pClientSocket = new gsClientSocket();
		pClientSocket->Connect("localhost", 9877);
#line 13 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
		GameStrutTestUtil::Update(pServerSocket, pClientSocket);
#line 15 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
		gsClientSocket* pServerClientSocket = pServerSocket->Accept();
		Assert::Plz(pServerClientSocket != 0);
#line 18 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
		Assert::Plz(pServerClientSocket->GetConnected());
		Assert::Plz(pClientSocket->GetConnected());
#line 21 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
		pServerClientSocket->Disconnect();
#line 23 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
		GameStrutTestUtil::Update(pServerSocket, pClientSocket);
#line 25 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
		Assert::Plz(!pClientSocket->GetConnected());
		Assert::Plz(!pServerClientSocket->GetConnected());
#line 28 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
		pServerSocket->Stop();
		if (pServerSocket) delete pServerSocket;
		if (pClientSocket) delete pClientSocket;
	}

}

