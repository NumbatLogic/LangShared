#include "gsServerRoom.hpp"
#include "../../Vector/CPP/Vector.hpp"
#include "gsServerClient.hpp"
#include "../../Blob/CPP/Blob.hpp"
#include "../../Console/CPP/Console.hpp"
#include "../../Assert/CPP/Assert.hpp"
#include "../Vector/OwnedVector.hpp"
#include "../../ExternalString/CPP/ExternalString.hpp"
#include "../../InternalString/CPP/InternalString.hpp"
#include "../GameStrutClient/gsClient.hpp"
#include "gsServer.hpp"

namespace NumbatLogic
{
	class gsServerRoom;
	template <class T>
	class Vector;
	class gsServerClient;
	class Console;
	class Assert;
	template <class T>
	class OwnedVector;
	class gsServerRoom_SyncHandler;
	class ExternalString;
	class InternalString;
	class gsBlob;
	class gsClient;
	class gsServer;
}
#line 0 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
#line 10 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
	gsServerRoom_SyncHandler::gsServerRoom_SyncHandler(unsigned int nHash, SyncHandler* pHandler)
	{
		__nHash = 0;
		__pHandler = 0;
#line 12 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		__nHash = nHash;
#line 13 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		__pHandler = pHandler;
	}

#line 17 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
#line 19 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
	gsServerClient* gsServerRoom::GetClientByClientId(unsigned int nClientId)
	{
#line 21 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		for (int i = 0; i < __pClientVector->GetSize(); i++)
		{
			gsServerClient* pClient = __pClientVector->Get(i);
#line 24 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			if (pClient->__nClientId == nClientId)
#line 25 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
				return pClient;
		}
#line 27 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		return 0;
	}

#line 30 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
	gsBlob* gsServerRoom::OnClientJoin(gsServerClient* pClient)
	{
#line 32 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		return new gsBlob();
	}

#line 35 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
	void gsServerRoom::OnClientLeave(gsServerClient* pClient)
	{
	}

#line 40 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
	void gsServerRoom::RegisterHandler(unsigned int nSyncType, gsServerRoom_SyncHandler::SyncHandler* pHandler)
	{
#line 42 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		if (__GetSyncHandler(nSyncType) != 0)
		{
#line 44 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			Console::Log("Server room sync handler hash already registered!");
#line 45 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			Assert::Plz(false);
		}
#line 47 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		__pSyncHandlerVector->PushBack(new gsServerRoom_SyncHandler(nSyncType, pHandler));
	}

#line 50 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
	gsServerRoom_SyncHandler* gsServerRoom::__GetSyncHandler(unsigned int nSyncType)
	{
#line 52 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		for (int i = 0; i < __pSyncHandlerVector->GetSize(); i++)
		{
			gsServerRoom_SyncHandler* pInfo = __pSyncHandlerVector->Get(i);
#line 55 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			if (pInfo->__nHash == nSyncType)
#line 56 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
				return pInfo;
		}
#line 58 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		return 0;
	}

#line 70 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
	gsServerRoom::gsServerRoom(unsigned int nRoomId, const char* sxRoomType, gsServer* pServer)
	{
		__nRoomId = 0;
		__nRoomType = 0;
		__sRoomType = 0;
		__pServer = 0;
		__pClientVector = 0;
		__pSyncHandlerVector = 0;
#line 72 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		__nRoomId = nRoomId;
#line 73 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		__nRoomType = ExternalString::GetChecksum(sxRoomType);
#line 74 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		__sRoomType = new InternalString(sxRoomType);
#line 75 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		__pServer = pServer;
#line 76 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		__pClientVector = new Vector<gsServerClient*>();
#line 77 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		__pSyncHandlerVector = new OwnedVector<gsServerRoom_SyncHandler*>();
	}

#line 80 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
	void gsServerRoom::__ClientJoin(gsServerClient* pClient)
	{
#line 82 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		Assert::Plz(GetClientByClientId(pClient->__nClientId) == 0);
#line 84 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		__pClientVector->PushBack(pClient);
#line 85 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		pClient->__pRoomVector->PushBack(this);
		gsBlob* pJoinBlob = OnClientJoin(pClient);
		gsBlob* pBlob = new gsBlob();
#line 89 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		pBlob->PackUint32(__nRoomId);
#line 90 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		pBlob->PackUint32(__nRoomType);
#line 91 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		pBlob->PackBool(false);
#line 92 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		pBlob->PackBlob(pJoinBlob);
#line 94 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		pClient->Send(0, gsClient::__ROOM_JOIN_HASH, pBlob);
		if (pJoinBlob) delete pJoinBlob;
		if (pBlob) delete pBlob;
	}

#line 97 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
	void gsServerRoom::__ClientLeave(gsServerClient* pClient)
	{
#line 99 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		for (int i = 0; i < __pClientVector->GetSize(); i++)
		{
#line 101 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
			if (__pClientVector->Get(i) == pClient)
			{
#line 103 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
				OnClientLeave(pClient);
#line 104 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
				__pClientVector->Erase(i);
#line 106 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
				for (int j = 0; j < pClient->__pRoomVector->GetSize(); j++)
				{
#line 108 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
					if (pClient->__pRoomVector->Get(j) == this)
					{
#line 110 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
						pClient->__pRoomVector->Erase(j);
						gsBlob* pBlob = new gsBlob();
#line 113 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
						pBlob->PackUint32(__nRoomId);
#line 114 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
						pBlob->PackUint32(__nRoomType);
#line 115 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
						pClient->Send(0, gsClient::__ROOM_LEAVE_HASH, pBlob);
						if (pBlob) delete pBlob;
#line 116 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
						return;
					}
				}
#line 121 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
				Assert::Plz(false);
			}
		}
#line 126 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		Assert::Plz(false);
	}

#line 17 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
	gsServerRoom::~gsServerRoom()
	{
		if (__sRoomType) delete __sRoomType;
		if (__pClientVector) delete __pClientVector;
		if (__pSyncHandlerVector) delete __pSyncHandlerVector;
	}

}

