#include "Client_Errored.hpp"
#include "../../GameStrutServer/gsServerRoom.hpp"
#include "../../../Blob/CPP/Blob.hpp"
#include "../../GameStrutClient/gsClient.hpp"
#include "../GameStrutTestUtil.hpp"
#include "../../../Assert/CPP/Assert.hpp"

namespace NumbatLogic
{
	class Client_Errored_Server;
	class gsServer;
	class Client_Errored_ServerClient;
	class gsServerClient;
	class gsServerRoom;
	class gsBlob;
	class Client_Errored;
	class gsClient;
	class GameStrutTestUtil;
	class Assert;
}
namespace NumbatLogic
{
	Client_Errored_Server::Client_Errored_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath) : gsServer(sxAddress, nPort, nVersion, sxDatabasePath)
	{
	}

	gsServerClient* Client_Errored_Server::OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer)
	{
		return new Client_Errored_ServerClient(nClientId, pClientSocket, pServer);
	}

	Client_Errored_ServerClient::Client_Errored_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer) : gsServerClient(nClientId, pClientSocket, pServer)
	{
	}

	void Client_Errored_ServerClient::OnInitialJoin()
	{
		gsServerRoom* pRoom = new gsServerRoom(1234, "Client_Errored_Room", __pServer);
		gsBlob* pBlob = new gsBlob();
		Send(pRoom, 2223003848, pBlob);
		if (pRoom) delete pRoom;
		if (pBlob) delete pBlob;
	}

	void Client_Errored::Run()
	{
		gsServer* pServer = new Client_Errored_Server("localhost", 9878, 0, "");
		gsClient* pClient = new gsClient("localhost", 9878, 0);
		GameStrutTestUtil::Update(pServer, pClient);
		Assert::Plz(pClient->__eState == gsClient::State::ERRORED);
		if (pServer) delete pServer;
		if (pClient) delete pClient;
	}

}

