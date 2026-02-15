#include "Sync_Server.hpp"
#include "../../GameStrutServer/gsServer.hpp"
#include "../../GameStrutServer/gsServerRoom.hpp"
#include "../../Vector/OwnedVector.hpp"
#include "../../../Blob/CPP/Blob.hpp"
#include "../../../Assert/CPP/Assert.hpp"
#include "../GameStrutTestUtil.hpp"
#include "../../GameStrutClient/gsClient.hpp"

namespace NumbatLogic
{
	class Sync_Server_Server;
	class gsServer;
	class Sync_Server_ServerClient;
	class gsServerClient;
	class gsServerRoom;
	template <class T>
	class OwnedVector;
	class gsBlob;
	class gsClient;
	class Assert;
	class Sync_Server;
	class GameStrutTestUtil;
	class Sync_Server_Client;
}
namespace NumbatLogic
{
	Sync_Server_Server::Sync_Server_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath) : gsServer(sxAddress, nPort, nVersion, sxDatabasePath)
	{
	}

	gsServerClient* Sync_Server_Server::OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer)
	{
		return new Sync_Server_ServerClient(nClientId, pClientSocket, pServer);
	}

	Sync_Server_ServerClient::Sync_Server_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer) : gsServerClient(nClientId, pClientSocket, pServer)
	{
	}

	void Sync_Server_ServerClient::OnInitialJoin()
	{
		gsServerRoom* pOwnedServerRoom = new gsServerRoom(__pServer->__nLastRoomId++, "Sync_Server_Room", __pServer);
		gsServerRoom* pServerRoom = pOwnedServerRoom;
		NumbatLogic::gsServerRoom* __1621810262 = pOwnedServerRoom;
		pOwnedServerRoom = 0;
		__pServer->__pRoomVector->PushBack(__1621810262);
		__pServer->__ClientJoin(this, pServerRoom);
		gsBlob* pTestBlob = new gsBlob();
		pTestBlob->PackUint32(42);
		Send(pServerRoom, 1986771282, pTestBlob);
		if (pOwnedServerRoom) delete pOwnedServerRoom;
		if (pTestBlob) delete pTestBlob;
	}

	Sync_Server_Client::Sync_Server_Client(const char* sxAddress, unsigned short nPort, unsigned short nVersion) : gsClient(sxAddress, nPort, nVersion)
	{
		m_nTestValue = 0;
	}

	bool Sync_Server_Client::OnSync(unsigned int nSyncId, unsigned int nMessageType, gsBlob* pMessageBlob)
	{
		if (gsClient::OnSync(nSyncId, nMessageType, pMessageBlob))
			return true;
		if (nMessageType == 1986771282)
		{
			Assert::Plz(pMessageBlob->UnpackUint32(m_nTestValue));
			return true;
		}
		return false;
	}

	void Sync_Server::Run()
	{
		gsServer* pServer = new Sync_Server_Server("localhost", 9877, 0, "");
		gsClient* pClient = new Sync_Server_Client("localhost", 9877, 0);
		Assert::Plz(pServer->__pRoomVector->GetSize() == 0);
		GameStrutTestUtil::Update(pServer, pClient);
		Assert::Plz(pServer->__pClientVector->GetSize() == 1);
		Assert::Plz(pServer->__pRoomVector->GetSize() == 1);
		Assert::Plz(pClient->__eState == gsClient::State::CONNECTED);
		Assert::Plz(pClient->__pRoomVector->GetSize() == 1);
		Sync_Server_Client* pSyncClient = (Sync_Server_Client*)(pClient);
		Assert::Plz(pSyncClient != 0);
		Assert::Plz(pSyncClient->m_nTestValue == 42);
		if (pServer) delete pServer;
		if (pClient) delete pClient;
	}

}

