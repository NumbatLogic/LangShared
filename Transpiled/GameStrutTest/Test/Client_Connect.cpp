#include "Client_Connect.hpp"
#include "../../GameStrutServer/gsServer.hpp"
#include "../../GameStrutServer/gsServerRoom.hpp"
#include "../../Vector/OwnedVector.hpp"
#include "../../../Source/Assert/CPP/Assert.hpp"
#include "../GameStrutTestUtil.hpp"
#include "../../GameStrutServer/gsServerClient.hpp"
#include "../../../Source/Vector/CPP/Vector.hpp"
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
#line 0 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Client_Connect.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Client_Connect.nll"
#line 5 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Client_Connect.nll"
	Client_Connect_Server::Client_Connect_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath) : gsServer(sxAddress, nPort, nVersion, sxDatabasePath)
	{
	}

	gsServerClient* Client_Connect_Server::OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer)
	{
		return new Client_Connect_ServerClient(nClientId, pClientSocket, pServer);
	}

#line 15 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Client_Connect.nll"
#line 17 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Client_Connect.nll"
	Client_Connect_ServerClient::Client_Connect_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer) : gsServerClient(nClientId, pClientSocket, pServer)
	{
	}

	void Client_Connect_ServerClient::OnInitialJoin()
	{
		gsServerRoom* pOwnedServerRoom = new gsServerRoom(++__pServer->__nLastRoomId, "Client_Connect_Room", __pServer);
		gsServerRoom* pServerRoom = pOwnedServerRoom;
		NumbatLogic::gsServerRoom* __1621810262 = pOwnedServerRoom;
#line 25 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Client_Connect.nll"
		pOwnedServerRoom = 0;
#line 25 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Client_Connect.nll"
		__pServer->__pRoomVector->PushBack(__1621810262);
		__pServer->__ClientJoin(this, pServerRoom);
		if (pOwnedServerRoom) delete pOwnedServerRoom;
	}

#line 32 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Client_Connect.nll"
	Client_Connect_Client::Client_Connect_Client(const char* sxAddress, unsigned short nPort, unsigned short nVersion) : gsClient(sxAddress, nPort, nVersion)
	{
	}

	gsClientRoom* Client_Connect_Client::OnRoomJoin(unsigned int nRoomId, unsigned int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob)
	{
		return gsClient::OnRoomJoin(nRoomId, nRoomTypeHash, bPrimary, pJoinBlob);
	}

#line 43 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Client_Connect.nll"
#line 45 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Client_Connect.nll"
	void Client_Connect::Run()
	{
		gsServer* pServer = new Client_Connect_Server("localhost", 9876, 0, "");
		gsClient* pClient = new Client_Connect_Client("localhost", 9876, 0);
#line 50 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Client_Connect.nll"
		Assert::Plz(pServer->__pRoomVector->GetSize() == 0);
#line 52 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Client_Connect.nll"
		GameStrutTestUtil::Update(pServer, pClient);
#line 55 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Client_Connect.nll"
		Assert::Plz(pServer->__pClientVector->GetSize() == 1);
		Assert::Plz(pServer->__pRoomVector->GetSize() == 1);
#line 58 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Client_Connect.nll"
		gsServerClient* pServerClient = pServer->__pClientVector->Get(0);
		Assert::Plz(pServerClient->__pRoomVector->GetSize() == 1);
#line 61 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Client_Connect.nll"
		gsServerRoom* pServerRoom = pServer->__pRoomVector->Get(0);
		Assert::Plz(pServerRoom->__pClientVector->GetSize() == 1);
#line 65 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Client_Connect.nll"
		Assert::Plz(pClient->__eState == gsClient::State::CONNECTED);
		Assert::Plz(pServerClient->__nClientId == pClient->__nClientId);
#line 68 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Client_Connect.nll"
		Assert::Plz(pClient->__pRoomVector->GetSize() == 1);
		gsClientRoom* pClientRoom = pClient->__pRoomVector->Get(0);
		Assert::Plz(pServerRoom->__nRoomId == pClientRoom->__nRoomId);
		if (pServer) delete pServer;
		if (pClient) delete pClient;
	}

}

