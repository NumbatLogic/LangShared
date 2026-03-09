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
#line 1 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
#line 6 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	Sync_ClientRoomHandler_Server::Sync_ClientRoomHandler_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath) : gsServer(sxAddress, nPort, nVersion, sxDatabasePath)
	{
	}

#line 10 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	gsServerClient* Sync_ClientRoomHandler_Server::OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer)
	{
#line 12 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		return new Sync_ClientRoomHandler_ServerClient(nClientId, pClientSocket, pServer);
	}

#line 16 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
#line 18 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	Sync_ClientRoomHandler_ServerClient::Sync_ClientRoomHandler_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer) : gsServerClient(nClientId, pClientSocket, pServer)
	{
	}

#line 22 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	void Sync_ClientRoomHandler_ServerClient::OnInitialJoin()
	{
		gsServerRoom* pOwnedServerRoom = new gsServerRoom(++__pServer->__nLastRoomId, "Sync_ClientRoomHandler_Room", __pServer);
		gsServerRoom* pServerRoom = pOwnedServerRoom;
		NumbatLogic::gsServerRoom* __1621810262 = pOwnedServerRoom;
#line 26 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		pOwnedServerRoom = 0;
#line 26 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		__pServer->__pRoomVector->PushBack(__1621810262);
#line 27 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		__pServer->__ClientJoin(this, pServerRoom);
		gsBlob* pTestBlob = new gsBlob();
#line 30 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		pTestBlob->PackUint32(42);
#line 31 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		Send(pServerRoom, 395751469, pTestBlob);
		if (pOwnedServerRoom) delete pOwnedServerRoom;
		if (pTestBlob) delete pTestBlob;
	}

#line 35 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
#line 37 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	const char* Sync_ClientRoomHandler_ClientRoom::ROOM_TYPE = "Sync_ClientRoomHandler_Room";
#line 42 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	Sync_ClientRoomHandler_ClientRoom::Sync_ClientRoomHandler_ClientRoom(unsigned int nRoomId, bool bPrimary, gsBlob* pJoinBlob, gsClient* pClient) : gsClientRoom(nRoomId, ROOM_TYPE, ROOM_TYPE_HASH, bPrimary, pClient)
	{
		m_nTestValue = 0;
#line 44 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		RegisterHandler(395751469, OnRoomTest);
	}

#line 47 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	void Sync_ClientRoomHandler_ClientRoom::OnRoomTest(gsClient* pClient, gsClientRoom* pRoom, unsigned int nSyncId, gsBlob* pMessageBlob)
	{
		Sync_ClientRoomHandler_ClientRoom* pRoomTyped = (Sync_ClientRoomHandler_ClientRoom*)(pRoom);
#line 50 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		Assert::Plz(pRoomTyped != 0);
#line 51 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		Assert::Plz(pMessageBlob->UnpackUint32(pRoomTyped->m_nTestValue));
	}

#line 55 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
#line 57 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	Sync_ClientRoomHandler_Client::Sync_ClientRoomHandler_Client(const char* sxAddress, unsigned short nPort, unsigned short nVersion) : gsClient(sxAddress, nPort, nVersion)
	{
	}

#line 61 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	gsClientRoom* Sync_ClientRoomHandler_Client::OnRoomJoin(unsigned int nRoomId, unsigned int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob)
	{
#line 63 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		if (nRoomTypeHash == Sync_ClientRoomHandler_ClientRoom::ROOM_TYPE_HASH)
#line 64 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			return new Sync_ClientRoomHandler_ClientRoom(nRoomId, bPrimary, pJoinBlob, this);
#line 65 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		return gsClient::OnRoomJoin(nRoomId, nRoomTypeHash, bPrimary, pJoinBlob);
	}

#line 69 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
#line 71 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	void Sync_ClientRoomHandler::Run()
	{
		gsServer* pServer = new Sync_ClientRoomHandler_Server("localhost", 9878, 0, "");
		gsClient* pClient = new Sync_ClientRoomHandler_Client("localhost", 9878, 0);
#line 76 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		Assert::Plz(pServer->__pRoomVector->GetSize() == 0);
#line 78 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		GameStrutTestUtil::Update(pServer, pClient);
#line 80 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		Assert::Plz(pServer->__pClientVector->GetSize() == 1);
#line 81 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		Assert::Plz(pServer->__pRoomVector->GetSize() == 1);
#line 82 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		Assert::Plz(pClient->__eState == gsClient::State::CONNECTED);
#line 83 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		Assert::Plz(pClient->__pRoomVector->GetSize() == 1);
		gsClientRoom* pRoom = pClient->__pRoomVector->Get(0);
		Sync_ClientRoomHandler_ClientRoom* pRoomTyped = (Sync_ClientRoomHandler_ClientRoom*)(pRoom);
#line 87 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		Assert::Plz(pRoomTyped != 0);
#line 88 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		Assert::Plz(pRoomTyped->m_nTestValue == 42);
		if (pServer) delete pServer;
		if (pClient) delete pClient;
	}

}

