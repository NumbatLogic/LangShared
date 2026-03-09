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
#line 1 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
#line 6 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
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
#line 8 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		__sAddress = new InternalString(sxAddress);
#line 9 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		__nPort = nPort;
#line 10 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		__nVersion = nVersion;
#line 12 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		__pServerSocket = new gsServerSocket();
#line 13 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		__pServerSocket->Start(__nPort);
#line 15 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		__pRoomVector = new OwnedVector<gsServerRoom*>();
#line 16 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		__pClientVector = new OwnedVector<gsServerClient*>();
	}

#line 19 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
	gsServer::~gsServer()
	{
#line 21 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		__pServerSocket->Stop();
		if (__sAddress) delete __sAddress;
		if (__pServerSocket) delete __pServerSocket;
		if (__pClientVector) delete __pClientVector;
		if (__pRoomVector) delete __pRoomVector;
	}

#line 24 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
	void gsServer::Update()
	{
#line 26 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		__pServerSocket->Update();
		{
			gsClientSocket* pClientSocket = __pServerSocket->Accept();
#line 30 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			if (pClientSocket != 0)
			{
				gsServerClient* pServerClient = OnCreateServerClient(++__nLastClientId, pClientSocket, this);
#line 33 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				Assert::Plz(pServerClient != 0);
				NumbatLogic::gsServerClient* __1702162430 = pServerClient;
#line 34 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				pServerClient = 0;
#line 34 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				__pClientVector->PushBack(__1702162430);
				if (pServerClient) delete pServerClient;
			}
		}
#line 38 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		for (int i = 0; i < __pClientVector->GetSize(); i++)
		{
			gsServerClient* pServerClient = __pClientVector->Get(i);
#line 42 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			pServerClient->__Update();
		}
		{
			int i = 0;
#line 48 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			while (i < __pClientVector->GetSize())
			{
				gsServerClient* pServerClient = __pClientVector->Get(i);
#line 51 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				if (!pServerClient->__pClientSocket->GetConnected())
				{
#line 71 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
					__pClientVector->Erase(i);
#line 73 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
					continue;
				}
#line 75 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				i++;
			}
		}
	}

#line 80 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
	bool gsServer::Pending()
	{
#line 82 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		return __pServerSocket->Pending();
	}

#line 85 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
	gsServerClient* gsServer::OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer)
	{
#line 87 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		return new gsServerClient(nClientId, pClientSocket, this);
	}

#line 90 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
	gsServerRoom* gsServer::OnCreateRoom(unsigned int nRoomId, unsigned int nRoomType, gsBlob* pCreateBlob)
	{
#line 92 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		return 0;
	}

#line 96 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
	void gsServer::Auth(gsBlob* pAuthBlob, gsClientSocket* pClientSocket)
	{
#line 98 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		Assert::Plz(false);
	}

#line 116 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
	void gsServer::__ClientJoin(gsServerClient* pClient, gsServerRoom* pRoom)
	{
#line 122 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		while (pClient->__pRoomVector->GetSize() > 0)
		{
			gsServerRoom* pCurrentRoom = pClient->__pRoomVector->Get(0);
#line 125 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			pCurrentRoom->__ClientLeave(pClient);
		}
#line 128 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		pRoom->__ClientJoin(pClient);
	}

#line 131 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
	gsServerRoom* gsServer::__CreateRoom(const char* sxRoomType, gsBlob* pCreateBlob)
	{
#line 133 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		pCreateBlob->SetOffset(0);
		unsigned int nRoomType = ExternalString::GetChecksum(sxRoomType);
		gsServerRoom* pOwnedRoom = OnCreateRoom(++__nLastRoomId, nRoomType, pCreateBlob);
#line 137 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		Assert::Plz(pOwnedRoom != 0);
		gsServerRoom* pRoom = pOwnedRoom;
		NumbatLogic::gsServerRoom* __4188406598 = pOwnedRoom;
#line 139 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		pOwnedRoom = 0;
#line 139 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		__pRoomVector->PushBack(__4188406598);
		if (pOwnedRoom) delete pOwnedRoom;
#line 140 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		return pRoom;
	}

}

