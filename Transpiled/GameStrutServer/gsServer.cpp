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
#line 0 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
#line 5 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
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
#line 7 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		__sAddress = new InternalString(sxAddress);
		__nPort = nPort;
		__nVersion = nVersion;
#line 11 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		__pServerSocket = new gsServerSocket();
		__pServerSocket->Start(__nPort);
#line 14 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		__pRoomVector = new OwnedVector<gsServerRoom*>();
		__pClientVector = new OwnedVector<gsServerClient*>();
	}

	gsServer::~gsServer()
	{
		__pServerSocket->Stop();
		if (__sAddress) delete __sAddress;
		if (__pServerSocket) delete __pServerSocket;
		if (__pClientVector) delete __pClientVector;
		if (__pRoomVector) delete __pRoomVector;
	}

#line 23 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
	void gsServer::Update()
	{
		__pServerSocket->Update();
		{
#line 28 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			gsClientSocket* pClientSocket = __pServerSocket->Accept();
			if (pClientSocket != 0)
			{
				gsServerClient* pServerClient = OnCreateServerClient(++__nLastClientId, pClientSocket, this);
				Assert::Plz(pServerClient != 0);
				NumbatLogic::gsServerClient* __1702162430 = pServerClient;
#line 33 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				pServerClient = 0;
#line 33 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				__pClientVector->PushBack(__1702162430);
				if (pServerClient) delete pServerClient;
			}
		}
		for (int i = 0; i < __pClientVector->GetSize(); i++)
		{
			gsServerClient* pServerClient = __pClientVector->Get(i);
#line 41 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			pServerClient->__Update();
		}
		{
#line 46 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			int i = 0;
			while (i < __pClientVector->GetSize())
			{
				gsServerClient* pServerClient = __pClientVector->Get(i);
				if (!pServerClient->__pClientSocket->GetConnected())
				{
#line 70 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
					__pClientVector->Erase(i);
#line 72 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
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
		return new gsServerClient(nClientId, pClientSocket, this);
	}

	gsServerRoom* gsServer::OnCreateRoom(unsigned int nRoomId, unsigned int nRoomType, gsBlob* pCreateBlob)
	{
		return 0;
	}

#line 95 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
	void gsServer::Auth(gsBlob* pAuthBlob, gsClientSocket* pClientSocket)
	{
		Assert::Plz(false);
	}

#line 115 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
	void gsServer::__ClientJoin(gsServerClient* pClient, gsServerRoom* pRoom)
	{
#line 121 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		while (pClient->__pRoomVector->GetSize() > 0)
		{
			gsServerRoom* pCurrentRoom = pClient->__pRoomVector->Get(0);
			pCurrentRoom->__ClientLeave(pClient);
		}
#line 127 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		pRoom->__ClientJoin(pClient);
	}

	gsServerRoom* gsServer::__CreateRoom(const char* sxRoomType, gsBlob* pCreateBlob)
	{
		pCreateBlob->SetOffset(0);
#line 134 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		unsigned int nRoomType = ExternalString::GetChecksum(sxRoomType);
		gsServerRoom* pOwnedRoom = OnCreateRoom(++__nLastRoomId, nRoomType, pCreateBlob);
		Assert::Plz(pOwnedRoom != 0);
		gsServerRoom* pRoom = pOwnedRoom;
		NumbatLogic::gsServerRoom* __4188406598 = pOwnedRoom;
#line 138 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		pOwnedRoom = 0;
#line 138 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		__pRoomVector->PushBack(__4188406598);
		if (pOwnedRoom) delete pOwnedRoom;
#line 139 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		return pRoom;
	}

}

