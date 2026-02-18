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
namespace NumbatLogic
{
	Sync_ServerRoomHandler_Error_Server::Sync_ServerRoomHandler_Error_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath) : gsServer(sxAddress, nPort, nVersion, sxDatabasePath)
	{
	}

	gsServerClient* Sync_ServerRoomHandler_Error_Server::OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer)
	{
		return new Sync_ServerRoomHandler_Error_ServerClient(nClientId, pClientSocket, pServer);
	}

	Sync_ServerRoomHandler_Error_ServerClient::Sync_ServerRoomHandler_Error_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer) : gsServerClient(nClientId, pClientSocket, pServer)
	{
	}

	void Sync_ServerRoomHandler_Error_ServerClient::OnInitialJoin()
	{
		gsServerRoom* pOwnedServerRoom = new gsServerRoom(++__pServer->__nLastRoomId, "Sync_ServerRoomHandler_Error_Room", __pServer);
		gsServerRoom* pServerRoom = pOwnedServerRoom;
		NumbatLogic::gsServerRoom* __1621810262 = pOwnedServerRoom;
		pOwnedServerRoom = 0;
		__pServer->__pRoomVector->PushBack(__1621810262);
		__pServer->__ClientJoin(this, pServerRoom);
		if (pOwnedServerRoom) delete pOwnedServerRoom;
	}

	const char* Sync_ServerRoomHandler_Error_ClientRoom::ROOM_TYPE = "Sync_ServerRoomHandler_Error_Room";
	Sync_ServerRoomHandler_Error_ClientRoom::Sync_ServerRoomHandler_Error_ClientRoom(unsigned int nRoomId, bool bPrimary, gsBlob* pJoinBlob, gsClient* pClient) : gsClientRoom(nRoomId, ROOM_TYPE, ROOM_TYPE_HASH, bPrimary, pClient)
	{
	}

	Sync_ServerRoomHandler_Error_Client::Sync_ServerRoomHandler_Error_Client(const char* sxAddress, unsigned short nPort, unsigned short nVersion) : gsClient(sxAddress, nPort, nVersion)
	{
		__pDummySync = 0;
	}

	gsClientRoom* Sync_ServerRoomHandler_Error_Client::OnRoomJoin(unsigned int nRoomId, unsigned int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob)
	{
		if (nRoomTypeHash == Sync_ServerRoomHandler_Error_ClientRoom::ROOM_TYPE_HASH)
		{
			gsClientRoom* pRoom = new Sync_ServerRoomHandler_Error_ClientRoom(nRoomId, bPrimary, pJoinBlob, this);
			__pDummySync = new gsSync();
			gsBlob* pBlob = new gsBlob();
			SyncSend(__pDummySync, "Dummy", pBlob, false, pRoom);
			NumbatLogic::gsClientRoom* __2731727373 = pRoom;
			pRoom = 0;
			if (pBlob) delete pBlob;
			return __2731727373;
		}
		return gsClient::OnRoomJoin(nRoomId, nRoomTypeHash, bPrimary, pJoinBlob);
	}

	Sync_ServerRoomHandler_Error_Client::~Sync_ServerRoomHandler_Error_Client()
	{
		if (__pDummySync) delete __pDummySync;
	}

	void Sync_ServerRoomHandler_Error::Run()
	{
		gsServer* pServer = new Sync_ServerRoomHandler_Error_Server("localhost", 9879, 0, "");
		gsClient* pClient = new Sync_ServerRoomHandler_Error_Client("localhost", 9879, 0);
		GameStrutTestUtil::Update(pServer, pClient);
		Assert::Plz(!pClient->__pClientSocket->GetConnected());
		Assert::Plz(pServer->__pClientVector->GetSize() == 0);
		if (pServer) delete pServer;
		if (pClient) delete pClient;
	}

}

