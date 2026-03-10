#include "gsClientRoom.hpp"
#include "../../InternalString/CPP/InternalString.hpp"
#include "../../ExternalString/CPP/ExternalString.hpp"
#include "../../Assert/CPP/Assert.hpp"
#include "../Vector/OwnedVector.hpp"
#include "../../Console/CPP/Console.hpp"
#include "gsClient.hpp"

namespace NumbatLogic
{
	class gsClientRoom;
	class InternalString;
	class ExternalString;
	class Assert;
	class gsClientRoom_SyncHandler;
	template <class T>
	class OwnedVector;
	class Console;
	class gsClient;
}
#line 0 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
#line 10 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
	gsClientRoom_SyncHandler::gsClientRoom_SyncHandler(unsigned int nHash, SyncHandler* pHandler)
	{
		__nHash = 0;
		__pHandler = 0;
#line 12 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		__nHash = nHash;
#line 13 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		__pHandler = pHandler;
	}

#line 17 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
#line 19 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
	gsClientRoom::gsClientRoom(unsigned int nRoomId, const char* sxRoomType, unsigned int nRoomTypeHash, bool bPrimary, gsClient* pClient)
	{
		__nRoomId = 0;
		__sRoomType = 0;
		__nRoomTypeHash = 0;
		__bPrimary = false;
		__pClient = 0;
		__pSyncHandlerVector = 0;
#line 21 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		__nRoomId = nRoomId;
#line 22 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		if (sxRoomType == 0)
		{
#line 24 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			__sRoomType = new InternalString("");
		}
		else
		{
#line 28 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			__sRoomType = new InternalString(sxRoomType);
			unsigned int nTestChecksum = ExternalString::GetChecksum(sxRoomType);
#line 30 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			Assert::Plz(nTestChecksum == nRoomTypeHash);
		}
#line 32 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		__nRoomTypeHash = nRoomTypeHash;
#line 33 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		__bPrimary = bPrimary;
#line 34 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		__pClient = pClient;
#line 35 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		__pSyncHandlerVector = new OwnedVector<gsClientRoom_SyncHandler*>();
	}

#line 38 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
	void gsClientRoom::RegisterHandler(unsigned int nMessageType, gsClientRoom_SyncHandler::SyncHandler* pHandler)
	{
#line 40 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		if (__GetSyncHandler(nMessageType) != 0)
		{
#line 42 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			Console::Log("Room sync handler hash already registered!");
#line 43 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			Assert::Plz(false);
		}
#line 45 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		__pSyncHandlerVector->PushBack(new gsClientRoom_SyncHandler(nMessageType, pHandler));
	}

#line 48 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
	gsClientRoom_SyncHandler* gsClientRoom::__GetSyncHandler(unsigned int nMessageType)
	{
#line 50 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		for (int i = 0; i < __pSyncHandlerVector->GetSize(); i++)
		{
			gsClientRoom_SyncHandler* pInfo = __pSyncHandlerVector->Get(i);
#line 53 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			if (pInfo->__nHash == nMessageType)
#line 54 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
				return pInfo;
		}
#line 56 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		return 0;
	}

#line 17 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
	gsClientRoom::~gsClientRoom()
	{
		if (__sRoomType) delete __sRoomType;
		if (__pSyncHandlerVector) delete __pSyncHandlerVector;
	}

}

