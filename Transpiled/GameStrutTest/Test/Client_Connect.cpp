#include "Client_Connect.hpp"
#include "../../GameStrutServer/gsServer.hpp"
#include "../../GameStrutServer/gsServerRoom.hpp"
#include "../../Vector/OwnedVector.hpp"
#include "../../../Assert/CPP/Assert.hpp"
#include "../GameStrutTestUtil.hpp"
#include "../../GameStrutServer/gsServerClient.hpp"
#include "../../../Vector/CPP/Vector.hpp"
#include "../../GameStrutClient/gsClient.hpp"
#include "../../GameStrutClient/gsClientRoom.hpp"

namespace NumbatLogic
{
	class Client_Connect_Server;
	class gsServer;
	class Client_Connect_ServerClient;
	class gsServerClient;
	class gsServerRoom;
	template <class T>
	class OwnedVector;
	class Client_Connect_Client;
	class gsClient;
	class Client_Connect;
	class Assert;
	class GameStrutTestUtil;
	template <class T>
	class Vector;
	class gsClientRoom;
}
#line 1 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
#line 6 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
	Client_Connect_Server::Client_Connect_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath) : gsServer(sxAddress, nPort, nVersion, sxDatabasePath)
	{
	}

#line 10 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
	gsServerClient* Client_Connect_Server::OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer)
	{
#line 12 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		return new Client_Connect_ServerClient(nClientId, pClientSocket, pServer);
	}

#line 16 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
#line 18 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
	Client_Connect_ServerClient::Client_Connect_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer) : gsServerClient(nClientId, pClientSocket, pServer)
	{
	}

#line 22 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
	void Client_Connect_ServerClient::OnInitialJoin()
	{
		gsServerRoom* pOwnedServerRoom = new gsServerRoom(++__pServer->__nLastRoomId, "Client_Connect_Room", __pServer);
		gsServerRoom* pServerRoom = pOwnedServerRoom;
		NumbatLogic::gsServerRoom* __1621810262 = pOwnedServerRoom;
#line 26 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		pOwnedServerRoom = 0;
#line 26 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		__pServer->__pRoomVector->PushBack(__1621810262);
#line 27 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		__pServer->__ClientJoin(this, pServerRoom);
		if (pOwnedServerRoom) delete pOwnedServerRoom;
	}

#line 31 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
#line 33 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
	Client_Connect_Client::Client_Connect_Client(const char* sxAddress, unsigned short nPort, unsigned short nVersion) : gsClient(sxAddress, nPort, nVersion)
	{
	}

#line 37 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
	gsClientRoom* Client_Connect_Client::OnRoomJoin(unsigned int nRoomId, unsigned int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob)
	{
#line 39 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		return gsClient::OnRoomJoin(nRoomId, nRoomTypeHash, bPrimary, pJoinBlob);
	}

#line 44 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
#line 46 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
	void Client_Connect::Run()
	{
		gsServer* pServer = new Client_Connect_Server("localhost", 9876, 0, "");
		gsClient* pClient = new Client_Connect_Client("localhost", 9876, 0);
#line 51 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		Assert::Plz(pServer->__pRoomVector->GetSize() == 0);
#line 53 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		GameStrutTestUtil::Update(pServer, pClient);
#line 56 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		Assert::Plz(pServer->__pClientVector->GetSize() == 1);
#line 57 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		Assert::Plz(pServer->__pRoomVector->GetSize() == 1);
		gsServerClient* pServerClient = pServer->__pClientVector->Get(0);
#line 60 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		Assert::Plz(pServerClient->__pRoomVector->GetSize() == 1);
		gsServerRoom* pServerRoom = pServer->__pRoomVector->Get(0);
#line 63 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		Assert::Plz(pServerRoom->__pClientVector->GetSize() == 1);
#line 66 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		Assert::Plz(pClient->__eState == gsClient::State::CONNECTED);
#line 67 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		Assert::Plz(pServerClient->__nClientId == pClient->__nClientId);
#line 69 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		Assert::Plz(pClient->__pRoomVector->GetSize() == 1);
		gsClientRoom* pClientRoom = pClient->__pRoomVector->Get(0);
#line 71 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		Assert::Plz(pServerRoom->__nRoomId == pClientRoom->__nRoomId);
		if (pServer) delete pServer;
		if (pClient) delete pClient;
	}

}

