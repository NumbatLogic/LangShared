#include "gsClientRoom.hpp"
#include "../../Source/InternalString/CPP/InternalString.hpp"
#include "../../Source/ExternalString/CPP/ExternalString.hpp"
#include "../../Source/Assert/CPP/Assert.hpp"
#include "../Vector/OwnedVector.hpp"
#include "../../Source/Console/CPP/Console.hpp"
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
#line 0 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClientRoom.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClientRoom.nll"
#line 10 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClientRoom.nll"
	gsClientRoom_SyncHandler::gsClientRoom_SyncHandler(unsigned int nHash, SyncHandler* pHandler)
	{
		__nHash = 0;
		__pHandler = 0;
#line 12 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClientRoom.nll"
		__nHash = nHash;
		__pHandler = pHandler;
	}

#line 17 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClientRoom.nll"
#line 19 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClientRoom.nll"
	gsClientRoom::gsClientRoom(unsigned int nRoomId, const char* sxRoomType, unsigned int nRoomTypeHash, bool bPrimary, gsClient* pClient)
	{
		__nRoomId = 0;
		__sRoomType = 0;
		__nRoomTypeHash = 0;
		__bPrimary = false;
		__pClient = 0;
		__pSyncHandlerVector = 0;
#line 21 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClientRoom.nll"
		__nRoomId = nRoomId;
		if (sxRoomType == 0)
		{
			__sRoomType = new InternalString("");
		}
		else
		{
			__sRoomType = new InternalString(sxRoomType);
			unsigned int nTestChecksum = ExternalString::GetChecksum(sxRoomType);
			Assert::Plz(nTestChecksum == nRoomTypeHash);
		}
		__nRoomTypeHash = nRoomTypeHash;
		__bPrimary = bPrimary;
		__pClient = pClient;
		__pSyncHandlerVector = new OwnedVector<gsClientRoom_SyncHandler*>();
	}

	void gsClientRoom::RegisterHandler(unsigned int nMessageType, gsClientRoom_SyncHandler::SyncHandler* pHandler)
	{
		if (__GetSyncHandler(nMessageType) != 0)
		{
			Console::Log("Room sync handler hash already registered!");
			Assert::Plz(false);
		}
		__pSyncHandlerVector->PushBack(new gsClientRoom_SyncHandler(nMessageType, pHandler));
	}

	gsClientRoom_SyncHandler* gsClientRoom::__GetSyncHandler(unsigned int nMessageType)
	{
		for (int i = 0; i < __pSyncHandlerVector->GetSize(); i++)
		{
			gsClientRoom_SyncHandler* pInfo = __pSyncHandlerVector->Get(i);
			if (pInfo->__nHash == nMessageType)
				return pInfo;
		}
		return 0;
	}

#line 17 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClientRoom.nll"
	gsClientRoom::~gsClientRoom()
	{
		if (__sRoomType) delete __sRoomType;
		if (__pSyncHandlerVector) delete __pSyncHandlerVector;
	}

}

