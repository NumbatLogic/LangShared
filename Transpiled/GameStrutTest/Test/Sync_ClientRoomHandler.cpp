#include "Sync_ClientRoomHandler.hpp"
#include "../../GameStrutServer/gsServer.hpp"
#include "../../GameStrutServer/gsServerRoom.hpp"
#include "../../Vector/OwnedVector.hpp"
#include "../../../Blob/CPP/Blob.hpp"
#include "../../../Assert/CPP/Assert.hpp"
#include "../GameStrutTestUtil.hpp"
#include "../../GameStrutClient/gsClient.hpp"

namespace NumbatLogic
{
	class Sync_ClientRoomHandler_Server;
	class gsServer;
	class Sync_ClientRoomHandler_ServerClient;
	class gsServerClient;
	class gsServerRoom;
	template <class T>
	class OwnedVector;
	class gsBlob;
	class gsClientRoom;
	class Sync_ClientRoomHandler_ClientRoom;
	class Assert;
	class Sync_ClientRoomHandler_Client;
	class gsClient;
	class Sync_ClientRoomHandler;
	class GameStrutTestUtil;
}
namespace NumbatLogic
{
	Sync_ClientRoomHandler_Server::Sync_ClientRoomHandler_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath) : gsServer(sxAddress, nPort, nVersion, sxDatabasePath)
	{
	}

	gsServerClient* Sync_ClientRoomHandler_Server::OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer)
	{
		return new Sync_ClientRoomHandler_ServerClient(nClientId, pClientSocket, pServer);
	}

	Sync_ClientRoomHandler_ServerClient::Sync_ClientRoomHandler_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer) : gsServerClient(nClientId, pClientSocket, pServer)
	{
	}

	void Sync_ClientRoomHandler_ServerClient::OnInitialJoin()
	{
		gsServerRoom* pOwnedServerRoom = new gsServerRoom(__pServer->__nLastRoomId++, "Sync_ClientRoomHandler_Room", __pServer);
		gsServerRoom* pServerRoom = pOwnedServerRoom;
		NumbatLogic::gsServerRoom* __1621810262 = pOwnedServerRoom;
		pOwnedServerRoom = 0;
		__pServer->__pRoomVector->PushBack(__1621810262);
		__pServer->__ClientJoin(this, pServerRoom);
		gsBlob* pTestBlob = new gsBlob();
		pTestBlob->PackUint32(42);
		Send(pServerRoom, 395751469, pTestBlob);
		if (pOwnedServerRoom) delete pOwnedServerRoom;
		if (pTestBlob) delete pTestBlob;
	}

	const char* Sync_ClientRoomHandler_ClientRoom::ROOM_TYPE = "Sync_ClientRoomHandler_Room";
	Sync_ClientRoomHandler_ClientRoom::Sync_ClientRoomHandler_ClientRoom(unsigned int nRoomId, bool bPrimary, gsBlob* pJoinBlob, gsClient* pClient) : gsClientRoom(nRoomId, ROOM_TYPE, ROOM_TYPE_HASH, bPrimary, pClient)
	{
		m_nTestValue = 0;
		RegisterHandler(395751469, OnRoomTest);
	}

	void Sync_ClientRoomHandler_ClientRoom::OnRoomTest(gsClient* pClient, gsClientRoom* pRoom, unsigned int nSyncId, gsBlob* pMessageBlob)
	{
		Sync_ClientRoomHandler_ClientRoom* pRoomTyped = (Sync_ClientRoomHandler_ClientRoom*)(pRoom);
		Assert::Plz(pRoomTyped != 0);
		Assert::Plz(pMessageBlob->UnpackUint32(pRoomTyped->m_nTestValue));
	}

	Sync_ClientRoomHandler_Client::Sync_ClientRoomHandler_Client(const char* sxAddress, unsigned short nPort, unsigned short nVersion) : gsClient(sxAddress, nPort, nVersion)
	{
	}

	gsClientRoom* Sync_ClientRoomHandler_Client::OnRoomJoin(unsigned int nRoomId, unsigned int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob)
	{
		if (nRoomTypeHash == Sync_ClientRoomHandler_ClientRoom::ROOM_TYPE_HASH)
			return new Sync_ClientRoomHandler_ClientRoom(nRoomId, bPrimary, pJoinBlob, this);
		return gsClient::OnRoomJoin(nRoomId, nRoomTypeHash, bPrimary, pJoinBlob);
	}

	void Sync_ClientRoomHandler::Run()
	{
		gsServer* pServer = new Sync_ClientRoomHandler_Server("localhost", 9878, 0, "");
		gsClient* pClient = new Sync_ClientRoomHandler_Client("localhost", 9878, 0);
		Assert::Plz(pServer->__pRoomVector->GetSize() == 0);
		GameStrutTestUtil::Update(pServer, pClient);
		Assert::Plz(pServer->__pClientVector->GetSize() == 1);
		Assert::Plz(pServer->__pRoomVector->GetSize() == 1);
		Assert::Plz(pClient->__eState == gsClient::State::CONNECTED);
		Assert::Plz(pClient->__pRoomVector->GetSize() == 1);
		gsClientRoom* pRoom = pClient->__pRoomVector->Get(0);
		Sync_ClientRoomHandler_ClientRoom* pRoomTyped = (Sync_ClientRoomHandler_ClientRoom*)(pRoom);
		Assert::Plz(pRoomTyped != 0);
		Assert::Plz(pRoomTyped->m_nTestValue == 42);
		if (pServer) delete pServer;
		if (pClient) delete pClient;
	}

}

