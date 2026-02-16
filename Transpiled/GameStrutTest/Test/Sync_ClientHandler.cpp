#include "Sync_ClientHandler.hpp"
#include "../../GameStrutServer/gsServer.hpp"
#include "../../GameStrutServer/gsServerRoom.hpp"
#include "../../Vector/OwnedVector.hpp"
#include "../../../Blob/CPP/Blob.hpp"
#include "../../../Assert/CPP/Assert.hpp"
#include "../GameStrutTestUtil.hpp"
#include "../../GameStrutClient/gsClient.hpp"

namespace NumbatLogic
{
	class Sync_ClientHandler_Server;
	class gsServer;
	class Sync_ClientHandler_ServerClient;
	class gsServerClient;
	class gsServerRoom;
	template <class T>
	class OwnedVector;
	class gsBlob;
	class gsClient;
	class Sync_ClientHandler_Client;
	class Assert;
	class Sync_ClientHandler;
	class GameStrutTestUtil;
}
namespace NumbatLogic
{
	Sync_ClientHandler_Server::Sync_ClientHandler_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath) : gsServer(sxAddress, nPort, nVersion, sxDatabasePath)
	{
	}

	gsServerClient* Sync_ClientHandler_Server::OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer)
	{
		return new Sync_ClientHandler_ServerClient(nClientId, pClientSocket, pServer);
	}

	Sync_ClientHandler_ServerClient::Sync_ClientHandler_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer) : gsServerClient(nClientId, pClientSocket, pServer)
	{
	}

	void Sync_ClientHandler_ServerClient::OnInitialJoin()
	{
		gsServerRoom* pOwnedServerRoom = new gsServerRoom(__pServer->__nLastRoomId++, "Sync_ClientHandler_Room", __pServer);
		gsServerRoom* pServerRoom = pOwnedServerRoom;
		NumbatLogic::gsServerRoom* __1621810262 = pOwnedServerRoom;
		pOwnedServerRoom = 0;
		__pServer->__pRoomVector->PushBack(__1621810262);
		__pServer->__ClientJoin(this, pServerRoom);
		gsBlob* pTestBlob = new gsBlob();
		pTestBlob->PackUint32(42);
		Send(0, 1986771282, pTestBlob);
		if (pOwnedServerRoom) delete pOwnedServerRoom;
		if (pTestBlob) delete pTestBlob;
	}

	Sync_ClientHandler_Client::Sync_ClientHandler_Client(const char* sxAddress, unsigned short nPort, unsigned short nVersion) : gsClient(sxAddress, nPort, nVersion)
	{
		m_nTestValue = 0;
		RegisterHandler(1986771282, OnTest);
	}

	void Sync_ClientHandler_Client::OnTest(gsClient* pClient, unsigned int nSyncId, gsBlob* pMessageBlob)
	{
		Sync_ClientHandler_Client* pSyncClient = (Sync_ClientHandler_Client*)(pClient);
		Assert::Plz(pSyncClient != 0);
		Assert::Plz(pMessageBlob->UnpackUint32(pSyncClient->m_nTestValue));
	}

	void Sync_ClientHandler::Run()
	{
		gsServer* pServer = new Sync_ClientHandler_Server("localhost", 9877, 0, "");
		gsClient* pClient = new Sync_ClientHandler_Client("localhost", 9877, 0);
		Assert::Plz(pServer->__pRoomVector->GetSize() == 0);
		GameStrutTestUtil::Update(pServer, pClient);
		Assert::Plz(pServer->__pClientVector->GetSize() == 1);
		Assert::Plz(pServer->__pRoomVector->GetSize() == 1);
		Assert::Plz(pClient->__eState == gsClient::State::CONNECTED);
		Assert::Plz(pClient->__pRoomVector->GetSize() == 1);
		Sync_ClientHandler_Client* pSyncClient = (Sync_ClientHandler_Client*)(pClient);
		Assert::Plz(pSyncClient != 0);
		Assert::Plz(pSyncClient->m_nTestValue == 42);
		if (pServer) delete pServer;
		if (pClient) delete pClient;
	}

}

