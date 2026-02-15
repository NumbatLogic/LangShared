#include "gsClientRoom.hpp"
#include "../../InternalString/CPP/InternalString.hpp"
#include "../../ExternalString/CPP/ExternalString.hpp"
#include "../../Assert/CPP/Assert.hpp"
#include "gsClient.hpp"

namespace NumbatLogic
{
	class gsClientRoom;
	class InternalString;
	class ExternalString;
	class Assert;
	class gsClient;
}
namespace NumbatLogic
{
	gsClientRoom::gsClientRoom(unsigned int nRoomId, const char* sxRoomType, unsigned int nRoomTypeHash, bool bPrimary, gsClient* pClient)
	{
		__nRoomId = 0;
		__sRoomType = 0;
		__nRoomTypeHash = 0;
		__bPrimary = false;
		__pClient = 0;
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
	}

	void gsClientRoom::OnSync(unsigned int nSyncId, unsigned int nMessageType, gsBlob* pMessageBlob)
	{
	}

	gsClientRoom::~gsClientRoom()
	{
		if (__sRoomType) delete __sRoomType;
	}

}

