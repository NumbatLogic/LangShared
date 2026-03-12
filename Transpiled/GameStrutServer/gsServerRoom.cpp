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
		__pHandler = pHandler;
	}

#line 17 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
#line 19 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
	gsServerClient* gsServerRoom::GetClientByClientId(unsigned int nClientId)
	{
		for (int i = 0; i < __pClientVector->GetSize(); i++)
		{
			gsServerClient* pClient = __pClientVector->Get(i);
			if (pClient->__nClientId == nClientId)
				return pClient;
		}
		return 0;
	}

	gsBlob* gsServerRoom::OnClientJoin(gsServerClient* pClient)
	{
		return new gsBlob();
	}

	void gsServerRoom::OnClientLeave(gsServerClient* pClient)
	{
	}

#line 40 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
	void gsServerRoom::RegisterHandler(unsigned int nSyncType, gsServerRoom_SyncHandler::SyncHandler* pHandler)
	{
		if (__GetSyncHandler(nSyncType) != 0)
		{
			Console::Log("Server room sync handler hash already registered!");
			Assert::Plz(false);
		}
		__pSyncHandlerVector->PushBack(new gsServerRoom_SyncHandler(nSyncType, pHandler));
	}

	gsServerRoom_SyncHandler* gsServerRoom::__GetSyncHandler(unsigned int nSyncType)
	{
		for (int i = 0; i < __pSyncHandlerVector->GetSize(); i++)
		{
			gsServerRoom_SyncHandler* pInfo = __pSyncHandlerVector->Get(i);
			if (pInfo->__nHash == nSyncType)
				return pInfo;
		}
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
		__nRoomType = ExternalString::GetChecksum(sxRoomType);
		__sRoomType = new InternalString(sxRoomType);
		__pServer = pServer;
		__pClientVector = new Vector<gsServerClient*>();
		__pSyncHandlerVector = new OwnedVector<gsServerRoom_SyncHandler*>();
	}

	void gsServerRoom::__ClientJoin(gsServerClient* pClient)
	{
		Assert::Plz(GetClientByClientId(pClient->__nClientId) == 0);
#line 84 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		__pClientVector->PushBack(pClient);
		pClient->__pRoomVector->PushBack(this);
		gsBlob* pJoinBlob = OnClientJoin(pClient);
#line 88 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		gsBlob* pBlob = new gsBlob();
		pBlob->PackUint32(__nRoomId);
		pBlob->PackUint32(__nRoomType);
		pBlob->PackBool(false);
		pBlob->PackBlob(pJoinBlob);
#line 94 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
		pClient->Send(0, gsClient::__ROOM_JOIN_HASH, pBlob);
		if (pJoinBlob) delete pJoinBlob;
		if (pBlob) delete pBlob;
	}

#line 97 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
	void gsServerRoom::__ClientLeave(gsServerClient* pClient)
	{
		for (int i = 0; i < __pClientVector->GetSize(); i++)
		{
			if (__pClientVector->Get(i) == pClient)
			{
				OnClientLeave(pClient);
				__pClientVector->Erase(i);
#line 106 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
				for (int j = 0; j < pClient->__pRoomVector->GetSize(); j++)
				{
					if (pClient->__pRoomVector->Get(j) == this)
					{
						pClient->__pRoomVector->Erase(j);
#line 112 "../LangShared/Transpiled/GameStrutServer/gsServerRoom.nll"
						gsBlob* pBlob = new gsBlob();
						pBlob->PackUint32(__nRoomId);
						pBlob->PackUint32(__nRoomType);
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

