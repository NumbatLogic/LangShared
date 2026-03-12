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
#line 8 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		__nPort = nPort;
#line 9 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		__nVersion = nVersion;
#line 11 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		__pServerSocket = new gsServerSocket();
#line 12 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		__pServerSocket->Start(__nPort);
#line 14 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		__pRoomVector = new OwnedVector<gsServerRoom*>();
#line 15 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		__pClientVector = new OwnedVector<gsServerClient*>();
	}

#line 18 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
	gsServer::~gsServer()
	{
#line 20 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		__pServerSocket->Stop();
		if (__sAddress) delete __sAddress;
		if (__pServerSocket) delete __pServerSocket;
		if (__pClientVector) delete __pClientVector;
		if (__pRoomVector) delete __pRoomVector;
	}

#line 23 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
	void gsServer::Update()
	{
#line 25 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		__pServerSocket->Update();
		{
#line 28 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			gsClientSocket* pClientSocket = __pServerSocket->Accept();
#line 29 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			if (pClientSocket != 0)
			{
#line 31 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				gsServerClient* pServerClient = OnCreateServerClient(++__nLastClientId, pClientSocket, this);
#line 32 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				Assert::Plz(pServerClient != 0);
				NumbatLogic::gsServerClient* __1702162430 = pServerClient;
#line 33 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				pServerClient = 0;
#line 33 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				__pClientVector->PushBack(__1702162430);
				if (pServerClient) delete pServerClient;
			}
		}
#line 37 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		for (int i = 0; i < __pClientVector->GetSize(); i++)
		{
#line 39 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			gsServerClient* pServerClient = __pClientVector->Get(i);
#line 41 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			pServerClient->__Update();
		}
		{
#line 46 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			int i = 0;
#line 47 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			while (i < __pClientVector->GetSize())
			{
#line 49 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				gsServerClient* pServerClient = __pClientVector->Get(i);
#line 50 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				if (!pServerClient->__pClientSocket->GetConnected())
				{
#line 70 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
					__pClientVector->Erase(i);
#line 72 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
					continue;
				}
#line 74 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				i++;
			}
		}
	}

#line 79 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
	bool gsServer::Pending()
	{
#line 81 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		return __pServerSocket->Pending();
	}

#line 84 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
	gsServerClient* gsServer::OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer)
	{
#line 86 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		return new gsServerClient(nClientId, pClientSocket, this);
	}

#line 89 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
	gsServerRoom* gsServer::OnCreateRoom(unsigned int nRoomId, unsigned int nRoomType, gsBlob* pCreateBlob)
	{
#line 91 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		return 0;
	}

#line 95 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
	void gsServer::Auth(gsBlob* pAuthBlob, gsClientSocket* pClientSocket)
	{
#line 97 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		Assert::Plz(false);
	}

#line 115 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
	void gsServer::__ClientJoin(gsServerClient* pClient, gsServerRoom* pRoom)
	{
#line 121 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		while (pClient->__pRoomVector->GetSize() > 0)
		{
#line 123 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			gsServerRoom* pCurrentRoom = pClient->__pRoomVector->Get(0);
#line 124 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			pCurrentRoom->__ClientLeave(pClient);
		}
#line 127 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		pRoom->__ClientJoin(pClient);
	}

#line 130 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
	gsServerRoom* gsServer::__CreateRoom(const char* sxRoomType, gsBlob* pCreateBlob)
	{
#line 132 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		pCreateBlob->SetOffset(0);
#line 134 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		unsigned int nRoomType = ExternalString::GetChecksum(sxRoomType);
#line 135 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		gsServerRoom* pOwnedRoom = OnCreateRoom(++__nLastRoomId, nRoomType, pCreateBlob);
#line 136 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		Assert::Plz(pOwnedRoom != 0);
#line 137 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
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

