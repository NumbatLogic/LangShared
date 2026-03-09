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
#line 1 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
#line 6 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	Sync_ServerRoomHandler_Error_Server::Sync_ServerRoomHandler_Error_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath) : gsServer(sxAddress, nPort, nVersion, sxDatabasePath)
	{
	}

#line 10 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	gsServerClient* Sync_ServerRoomHandler_Error_Server::OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer)
	{
#line 12 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		return new Sync_ServerRoomHandler_Error_ServerClient(nClientId, pClientSocket, pServer);
	}

#line 16 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
#line 18 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	Sync_ServerRoomHandler_Error_ServerClient::Sync_ServerRoomHandler_Error_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer) : gsServerClient(nClientId, pClientSocket, pServer)
	{
	}

#line 22 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	void Sync_ServerRoomHandler_Error_ServerClient::OnInitialJoin()
	{
		gsServerRoom* pOwnedServerRoom = new gsServerRoom(++__pServer->__nLastRoomId, "Sync_ServerRoomHandler_Error_Room", __pServer);
		gsServerRoom* pServerRoom = pOwnedServerRoom;
		NumbatLogic::gsServerRoom* __1621810262 = pOwnedServerRoom;
#line 26 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		pOwnedServerRoom = 0;
#line 26 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		__pServer->__pRoomVector->PushBack(__1621810262);
#line 27 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		__pServer->__ClientJoin(this, pServerRoom);
		if (pOwnedServerRoom) delete pOwnedServerRoom;
	}

#line 31 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
#line 33 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	const char* Sync_ServerRoomHandler_Error_ClientRoom::ROOM_TYPE = "Sync_ServerRoomHandler_Error_Room";
#line 36 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	Sync_ServerRoomHandler_Error_ClientRoom::Sync_ServerRoomHandler_Error_ClientRoom(unsigned int nRoomId, bool bPrimary, gsBlob* pJoinBlob, gsClient* pClient) : gsClientRoom(nRoomId, ROOM_TYPE, ROOM_TYPE_HASH, bPrimary, pClient)
	{
	}

#line 41 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
#line 45 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	Sync_ServerRoomHandler_Error_Client::Sync_ServerRoomHandler_Error_Client(const char* sxAddress, unsigned short nPort, unsigned short nVersion) : gsClient(sxAddress, nPort, nVersion)
	{
		__pDummySync = 0;
	}

#line 50 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	gsClientRoom* Sync_ServerRoomHandler_Error_Client::OnRoomJoin(unsigned int nRoomId, unsigned int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob)
	{
#line 52 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		if (nRoomTypeHash == Sync_ServerRoomHandler_Error_ClientRoom::ROOM_TYPE_HASH)
		{
			gsClientRoom* pRoom = new Sync_ServerRoomHandler_Error_ClientRoom(nRoomId, bPrimary, pJoinBlob, this);
#line 55 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
			__pDummySync = new gsSync();
			gsBlob* pBlob = new gsBlob();
#line 57 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
			SyncSend(__pDummySync, "Dummy", pBlob, gsSync::Response::EXPECT_RESPONSE, pRoom);
			NumbatLogic::gsClientRoom* __2731727373 = pRoom;
#line 58 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
			pRoom = 0;
			if (pBlob) delete pBlob;
#line 58 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
			return __2731727373;
		}
#line 60 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		return gsClient::OnRoomJoin(nRoomId, nRoomTypeHash, bPrimary, pJoinBlob);
	}

#line 41 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	Sync_ServerRoomHandler_Error_Client::~Sync_ServerRoomHandler_Error_Client()
	{
		if (__pDummySync) delete __pDummySync;
	}

#line 64 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
#line 66 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	void Sync_ServerRoomHandler_Error::Run()
	{
		gsServer* pServer = new Sync_ServerRoomHandler_Error_Server("localhost", 9879, 0, "");
		gsClient* pClient = new Sync_ServerRoomHandler_Error_Client("localhost", 9879, 0);
#line 71 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		GameStrutTestUtil::Update(pServer, pClient);
#line 73 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		Assert::Plz(!pClient->__pClientSocket->GetConnected());
#line 74 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		Assert::Plz(pServer->__pClientVector->GetSize() == 0);
		if (pServer) delete pServer;
		if (pClient) delete pClient;
	}

}

