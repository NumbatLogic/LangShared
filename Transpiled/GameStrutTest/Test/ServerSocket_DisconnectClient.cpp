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
namespace NumbatLogic
{
	void ServerSocket_DisconnectClient::Run()
	{
		gsServerSocket* pServerSocket = new gsServerSocket();
		pServerSocket->Start(9877);
		gsClientSocket* pClientSocket = new gsClientSocket();
		pClientSocket->Connect("localhost", 9877);
		GameStrutTestUtil::Update(pServerSocket, pClientSocket);
		gsClientSocket* pServerClientSocket = pServerSocket->Accept();
		Assert::Plz(pServerClientSocket != 0);
		Assert::Plz(pServerClientSocket->GetConnected());
		Assert::Plz(pClientSocket->GetConnected());
		pServerClientSocket->Disconnect();
		GameStrutTestUtil::Update(pServerSocket, pClientSocket);
		Assert::Plz(!pClientSocket->GetConnected());
		Assert::Plz(!pServerClientSocket->GetConnected());
		pServerSocket->Stop();
		if (pServerSocket) delete pServerSocket;
		if (pClientSocket) delete pClientSocket;
	}

}

