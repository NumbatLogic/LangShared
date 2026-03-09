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
#line 1 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
#line 11 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
	gsClientRoom_SyncHandler::gsClientRoom_SyncHandler(unsigned int nHash, SyncHandler* pHandler)
	{
		__nHash = 0;
		__pHandler = 0;
#line 13 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		__nHash = nHash;
#line 14 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		__pHandler = pHandler;
	}

#line 18 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
#line 20 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
	gsClientRoom::gsClientRoom(unsigned int nRoomId, const char* sxRoomType, unsigned int nRoomTypeHash, bool bPrimary, gsClient* pClient)
	{
		__nRoomId = 0;
		__sRoomType = 0;
		__nRoomTypeHash = 0;
		__bPrimary = false;
		__pClient = 0;
		__pSyncHandlerVector = 0;
#line 22 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		__nRoomId = nRoomId;
#line 23 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		if (sxRoomType == 0)
		{
#line 25 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			__sRoomType = new InternalString("");
		}
		else
		{
#line 29 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			__sRoomType = new InternalString(sxRoomType);
			unsigned int nTestChecksum = ExternalString::GetChecksum(sxRoomType);
#line 31 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			Assert::Plz(nTestChecksum == nRoomTypeHash);
		}
#line 33 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		__nRoomTypeHash = nRoomTypeHash;
#line 34 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		__bPrimary = bPrimary;
#line 35 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		__pClient = pClient;
#line 36 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		__pSyncHandlerVector = new OwnedVector<gsClientRoom_SyncHandler*>();
	}

#line 39 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
	void gsClientRoom::RegisterHandler(unsigned int nMessageType, gsClientRoom_SyncHandler::SyncHandler* pHandler)
	{
#line 41 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		if (__GetSyncHandler(nMessageType) != 0)
		{
#line 43 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			Console::Log("Room sync handler hash already registered!");
#line 44 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			Assert::Plz(false);
		}
#line 46 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		__pSyncHandlerVector->PushBack(new gsClientRoom_SyncHandler(nMessageType, pHandler));
	}

#line 49 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
	gsClientRoom_SyncHandler* gsClientRoom::__GetSyncHandler(unsigned int nMessageType)
	{
#line 51 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		for (int i = 0; i < __pSyncHandlerVector->GetSize(); i++)
		{
			gsClientRoom_SyncHandler* pInfo = __pSyncHandlerVector->Get(i);
#line 54 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
			if (pInfo->__nHash == nMessageType)
#line 55 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
				return pInfo;
		}
#line 57 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
		return 0;
	}

#line 18 "../LangShared/Transpiled/GameStrutClient/gsClientRoom.nll"
	gsClientRoom::~gsClientRoom()
	{
		if (__sRoomType) delete __sRoomType;
		if (__pSyncHandlerVector) delete __pSyncHandlerVector;
	}

}

