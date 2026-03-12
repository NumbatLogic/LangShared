#include "Sync_ServerRoomHandler_Error.hpp"
#include "../../GameStrutServer/gsServer.hpp"
#include "../../GameStrutServer/gsServerRoom.hpp"
#include "../../Vector/OwnedVector.hpp"
#include "../../GameStrutClient/gsSync.hpp"
#include "../../../Blob/CPP/Blob.hpp"
#include "../GameStrutTestUtil.hpp"
#include "../../../Assert/CPP/Assert.hpp"
#include "../../GameStrutClient/gsClient.hpp"
#include "../../../GameStrutClient/CPP/gsClientSocket.hpp"

namespace NumbatLogic
{
	class Sync_ServerRoomHandler_Error_Server;
	class gsServer;
	class Sync_ServerRoomHandler_Error_ServerClient;
	class gsServerClient;
	class gsServerRoom;
	template <class T>
	class OwnedVector;
	class Sync_ServerRoomHandler_Error_ClientRoom;
	class gsClientRoom;
	class Sync_ServerRoomHandler_Error_Client;
	class gsClient;
	class gsSync;
	class gsBlob;
	class Sync_ServerRoomHandler_Error;
	class GameStrutTestUtil;
	class Assert;
	class gsClientSocket;
}
#line 0 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
#line 5 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	Sync_ServerRoomHandler_Error_Server::Sync_ServerRoomHandler_Error_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath) : gsServer(sxAddress, nPort, nVersion, sxDatabasePath)
	{
	}

#line 9 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	gsServerClient* Sync_ServerRoomHandler_Error_Server::OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer)
	{
#line 11 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		return new Sync_ServerRoomHandler_Error_ServerClient(nClientId, pClientSocket, pServer);
	}

#line 15 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
#line 17 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	Sync_ServerRoomHandler_Error_ServerClient::Sync_ServerRoomHandler_Error_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer) : gsServerClient(nClientId, pClientSocket, pServer)
	{
	}

#line 21 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	void Sync_ServerRoomHandler_Error_ServerClient::OnInitialJoin()
	{
#line 23 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		gsServerRoom* pOwnedServerRoom = new gsServerRoom(++__pServer->__nLastRoomId, "Sync_ServerRoomHandler_Error_Room", __pServer);
#line 24 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		gsServerRoom* pServerRoom = pOwnedServerRoom;
		NumbatLogic::gsServerRoom* __1621810262 = pOwnedServerRoom;
#line 25 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		pOwnedServerRoom = 0;
#line 25 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		__pServer->__pRoomVector->PushBack(__1621810262);
#line 26 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		__pServer->__ClientJoin(this, pServerRoom);
		if (pOwnedServerRoom) delete pOwnedServerRoom;
	}

#line 30 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
#line 32 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	const char* Sync_ServerRoomHandler_Error_ClientRoom::ROOM_TYPE = "Sync_ServerRoomHandler_Error_Room";
#line 35 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	Sync_ServerRoomHandler_Error_ClientRoom::Sync_ServerRoomHandler_Error_ClientRoom(unsigned int nRoomId, bool bPrimary, gsBlob* pJoinBlob, gsClient* pClient) : gsClientRoom(nRoomId, ROOM_TYPE, ROOM_TYPE_HASH, bPrimary, pClient)
	{
	}

#line 40 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
#line 44 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	Sync_ServerRoomHandler_Error_Client::Sync_ServerRoomHandler_Error_Client(const char* sxAddress, unsigned short nPort, unsigned short nVersion) : gsClient(sxAddress, nPort, nVersion)
	{
		__pDummySync = 0;
	}

#line 49 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	gsClientRoom* Sync_ServerRoomHandler_Error_Client::OnRoomJoin(unsigned int nRoomId, unsigned int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob)
	{
#line 51 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		if (nRoomTypeHash == Sync_ServerRoomHandler_Error_ClientRoom::ROOM_TYPE_HASH)
		{
#line 53 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
			gsClientRoom* pRoom = new Sync_ServerRoomHandler_Error_ClientRoom(nRoomId, bPrimary, pJoinBlob, this);
#line 54 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
			__pDummySync = new gsSync();
#line 55 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
			gsBlob* pBlob = new gsBlob();
#line 56 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
			SyncSend(__pDummySync, "Dummy", pBlob, gsSync::Response::EXPECT_RESPONSE, pRoom);
			NumbatLogic::gsClientRoom* __2731727373 = pRoom;
#line 57 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
			pRoom = 0;
			if (pBlob) delete pBlob;
#line 57 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
			return __2731727373;
		}
#line 59 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		return gsClient::OnRoomJoin(nRoomId, nRoomTypeHash, bPrimary, pJoinBlob);
	}

#line 40 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	Sync_ServerRoomHandler_Error_Client::~Sync_ServerRoomHandler_Error_Client()
	{
		if (__pDummySync) delete __pDummySync;
	}

#line 63 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
#line 65 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	void Sync_ServerRoomHandler_Error::Run()
	{
#line 67 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		gsServer* pServer = new Sync_ServerRoomHandler_Error_Server("localhost", 9879, 0, "");
#line 68 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		gsClient* pClient = new Sync_ServerRoomHandler_Error_Client("localhost", 9879, 0);
#line 70 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		GameStrutTestUtil::Update(pServer, pClient);
#line 72 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		Assert::Plz(!pClient->__pClientSocket->GetConnected());
#line 73 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		Assert::Plz(pServer->__pClientVector->GetSize() == 0);
		if (pServer) delete pServer;
		if (pClient) delete pClient;
	}

}

