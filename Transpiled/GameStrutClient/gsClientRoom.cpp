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
namespace NumbatLogic
{
	gsClientRoom_SyncHandler::gsClientRoom_SyncHandler(unsigned int nHash, SyncHandler* pHandler)
	{
		__nHash = 0;
		__pHandler = 0;
		__nHash = nHash;
		__pHandler = pHandler;
	}

	gsClientRoom::gsClientRoom(unsigned int nRoomId, const char* sxRoomType, unsigned int nRoomTypeHash, bool bPrimary, gsClient* pClient)
	{
		__nRoomId = 0;
		__sRoomType = 0;
		__nRoomTypeHash = 0;
		__bPrimary = false;
		__pClient = 0;
		__pSyncHandlerVector = 0;
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

	void gsClientRoom::OnSync(unsigned int nSyncId, unsigned int nMessageType, gsBlob* pMessageBlob)
	{
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

	gsClientRoom::~gsClientRoom()
	{
		if (__sRoomType) delete __sRoomType;
		if (__pSyncHandlerVector) delete __pSyncHandlerVector;
	}

}

