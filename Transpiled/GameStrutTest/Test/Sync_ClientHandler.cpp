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
#line 0 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
#line 5 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
	Sync_ClientHandler_Server::Sync_ClientHandler_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath) : gsServer(sxAddress, nPort, nVersion, sxDatabasePath)
	{
	}

#line 9 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
	gsServerClient* Sync_ClientHandler_Server::OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer)
	{
#line 11 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		return new Sync_ClientHandler_ServerClient(nClientId, pClientSocket, pServer);
	}

#line 15 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
#line 17 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
	Sync_ClientHandler_ServerClient::Sync_ClientHandler_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer) : gsServerClient(nClientId, pClientSocket, pServer)
	{
	}

#line 21 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
	void Sync_ClientHandler_ServerClient::OnInitialJoin()
	{
		gsServerRoom* pOwnedServerRoom = new gsServerRoom(++__pServer->__nLastRoomId, "Sync_ClientHandler_Room", __pServer);
		gsServerRoom* pServerRoom = pOwnedServerRoom;
		NumbatLogic::gsServerRoom* __1621810262 = pOwnedServerRoom;
#line 25 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		pOwnedServerRoom = 0;
#line 25 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		__pServer->__pRoomVector->PushBack(__1621810262);
#line 26 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		__pServer->__ClientJoin(this, pServerRoom);
		gsBlob* pTestBlob = new gsBlob();
#line 29 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		pTestBlob->PackUint32(42);
#line 30 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		Send(0, 1986771282, pTestBlob);
		if (pOwnedServerRoom) delete pOwnedServerRoom;
		if (pTestBlob) delete pTestBlob;
	}

#line 34 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
#line 38 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
	Sync_ClientHandler_Client::Sync_ClientHandler_Client(const char* sxAddress, unsigned short nPort, unsigned short nVersion) : gsClient(sxAddress, nPort, nVersion)
	{
		m_nTestValue = 0;
#line 40 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		RegisterHandler(1986771282, OnTest);
	}

#line 43 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
	void Sync_ClientHandler_Client::OnTest(gsClient* pClient, unsigned int nSyncId, gsBlob* pMessageBlob)
	{
		Sync_ClientHandler_Client* pSyncClient = (Sync_ClientHandler_Client*)(pClient);
#line 46 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		Assert::Plz(pSyncClient != 0);
#line 47 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		Assert::Plz(pMessageBlob->UnpackUint32(pSyncClient->m_nTestValue));
	}

#line 51 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
#line 53 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
	void Sync_ClientHandler::Run()
	{
		gsServer* pServer = new Sync_ClientHandler_Server("localhost", 9877, 0, "");
		gsClient* pClient = new Sync_ClientHandler_Client("localhost", 9877, 0);
#line 58 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		Assert::Plz(pServer->__pRoomVector->GetSize() == 0);
#line 60 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		GameStrutTestUtil::Update(pServer, pClient);
#line 62 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		Assert::Plz(pServer->__pClientVector->GetSize() == 1);
#line 63 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		Assert::Plz(pServer->__pRoomVector->GetSize() == 1);
#line 64 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		Assert::Plz(pClient->__eState == gsClient::State::CONNECTED);
#line 65 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		Assert::Plz(pClient->__pRoomVector->GetSize() == 1);
		Sync_ClientHandler_Client* pSyncClient = (Sync_ClientHandler_Client*)(pClient);
#line 68 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		Assert::Plz(pSyncClient != 0);
#line 69 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		Assert::Plz(pSyncClient->m_nTestValue == 42);
		if (pServer) delete pServer;
		if (pClient) delete pClient;
	}

}

