#include "gsServer.hpp"
#include "../../InternalString/CPP/InternalString.hpp"
#include "../../GameStrutClient/CPP/gsServerSocket.hpp"
#include "gsServerRoom.hpp"
#include "../Vector/OwnedVector.hpp"
#include "gsServerClient.hpp"
#include "../../Assert/CPP/Assert.hpp"
#include "../../GameStrutClient/CPP/gsClientSocket.hpp"
#include "../../Vector/CPP/Vector.hpp"
#include "../../Blob/CPP/Blob.hpp"
#include "../../ExternalString/CPP/ExternalString.hpp"

namespace NumbatLogic
{
	class gsServer;
	class InternalString;
	class gsServerSocket;
	class gsServerRoom;
	template <class T>
	class OwnedVector;
	class gsServerClient;
	class gsClientSocket;
	class Assert;
	template <class T>
	class Vector;
	class gsBlob;
	class ExternalString;
}
namespace NumbatLogic
{
	gsServer::gsServer(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath)
	{
		__sAddress = 0;
		__nPort = 0;
		__nVersion = 0;
		__pServerSocket = 0;
		__pClientVector = 0;
		__pRoomVector = 0;
		__nLastClientId = 0;
		__nLastRoomId = 0;
		__sAddress = new InternalString(sxAddress);
		__nPort = nPort;
		__nVersion = nVersion;
		__pServerSocket = new gsServerSocket();
		__pServerSocket->Start(__nPort);
		__pRoomVector = new OwnedVector<gsServerRoom*>();
		__pClientVector = new OwnedVector<gsServerClient*>();
		__nLastRoomId = 1;
	}

	gsServer::~gsServer()
	{
		__pServerSocket->Stop();
		if (__sAddress) delete __sAddress;
		if (__pServerSocket) delete __pServerSocket;
		if (__pClientVector) delete __pClientVector;
		if (__pRoomVector) delete __pRoomVector;
	}

	void gsServer::Update()
	{
		__pServerSocket->Update();
		{
			gsClientSocket* pClientSocket = __pServerSocket->Accept();
			if (pClientSocket != 0)
			{
				gsServerClient* pServerClient = OnCreateServerClient(__nLastClientId++, pClientSocket, this);
				Assert::Plz(pServerClient != 0);
				NumbatLogic::gsServerClient* __1702162431 = pServerClient;
				pServerClient = 0;
				__pClientVector->PushBack(__1702162431);
				if (pServerClient) delete pServerClient;
			}
		}
		for (int i = 0; i < __pClientVector->GetSize(); i++)
		{
			gsServerClient* pServerClient = __pClientVector->Get(i);
			pServerClient->__Update();
		}
		{
			int i = 0;
			while (i < __pClientVector->GetSize())
			{
				gsServerClient* pServerClient = __pClientVector->Get(i);
				if (!pServerClient->__pClientSocket->GetConnected())
				{
					__pClientVector->Erase(i);
					continue;
				}
				i++;
			}
		}
	}

	bool gsServer::Pending()
	{
		return __pServerSocket->Pending();
	}

	gsServerClient* gsServer::OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer)
	{
		return new gsServerClient(__nLastClientId++, pClientSocket, this);
	}

	gsServerRoom* gsServer::OnCreateRoom(unsigned int nRoomId, unsigned int nRoomType, gsBlob* pCreateBlob)
	{
		return 0;
	}

	void gsServer::Auth(gsBlob* pAuthBlob, gsClientSocket* pClientSocket)
	{
		Assert::Plz(false);
	}

	void gsServer::__ClientJoin(gsServerClient* pClient, gsServerRoom* pRoom)
	{
		while (pClient->__pRoomVector->GetSize() > 0)
		{
			gsServerRoom* pCurrentRoom = pClient->__pRoomVector->Get(0);
			pCurrentRoom->__ClientLeave(pClient);
		}
		pRoom->__ClientJoin(pClient);
	}

	gsServerRoom* gsServer::__CreateRoom(const char* sxRoomType, gsBlob* pCreateBlob)
	{
		pCreateBlob->SetOffset(0);
		unsigned int nRoomType = ExternalString::GetChecksum(sxRoomType);
		gsServerRoom* pOwnedRoom = OnCreateRoom(++__nLastRoomId, nRoomType, pCreateBlob);
		Assert::Plz(pOwnedRoom != 0);
		gsServerRoom* pRoom = pOwnedRoom;
		NumbatLogic::gsServerRoom* __4188406599 = pOwnedRoom;
		pOwnedRoom = 0;
		__pRoomVector->PushBack(__4188406599);
		if (pOwnedRoom) delete pOwnedRoom;
		return pRoom;
	}

}

