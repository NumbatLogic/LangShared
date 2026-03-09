#include "Sync_ClientHandler_Error.hpp"
#include "../../GameStrutServer/gsServerRoom.hpp"
#include "../../../Blob/CPP/Blob.hpp"
#include "../../GameStrutClient/gsClient.hpp"
#include "../GameStrutTestUtil.hpp"
#include "../../../Assert/CPP/Assert.hpp"
#include "../../../GameStrutClient/CPP/gsClientSocket.hpp"

namespace NumbatLogic
{
	class Sync_ClientHandler_Error_Server;
	class gsServer;
	class Sync_ClientHandler_Error_ServerClient;
	class gsServerClient;
	class gsServerRoom;
	class gsBlob;
	class Sync_ClientHandler_Error;
	class gsClient;
	class GameStrutTestUtil;
	class Assert;
	class gsClientSocket;
}
#line 1 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
#line 6 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
	Sync_ClientHandler_Error_Server::Sync_ClientHandler_Error_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath) : gsServer(sxAddress, nPort, nVersion, sxDatabasePath)
	{
	}

#line 10 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
	gsServerClient* Sync_ClientHandler_Error_Server::OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer)
	{
#line 12 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		return new Sync_ClientHandler_Error_ServerClient(nClientId, pClientSocket, pServer);
	}

#line 16 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
#line 18 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
	Sync_ClientHandler_Error_ServerClient::Sync_ClientHandler_Error_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer) : gsServerClient(nClientId, pClientSocket, pServer)
	{
	}

#line 22 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
	void Sync_ClientHandler_Error_ServerClient::OnInitialJoin()
	{
		gsServerRoom* pRoom = new gsServerRoom(1234, "Sync_ClientHandler_Error_Room", __pServer);
		gsBlob* pBlob = new gsBlob();
#line 26 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		Send(pRoom, 2223003848, pBlob);
		if (pRoom) delete pRoom;
		if (pBlob) delete pBlob;
	}

#line 30 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
#line 32 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
	void Sync_ClientHandler_Error::Run()
	{
		gsServer* pServer = new Sync_ClientHandler_Error_Server("localhost", 9878, 0, "");
		gsClient* pClient = new gsClient("localhost", 9878, 0);
#line 37 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		GameStrutTestUtil::Update(pServer, pClient);
#line 38 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		Assert::Plz(pClient->__eState == gsClient::State::ERRORED);
#line 39 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		Assert::Plz(!pClient->__pClientSocket->GetConnected());
		if (pServer) delete pServer;
		if (pClient) delete pClient;
	}

}

