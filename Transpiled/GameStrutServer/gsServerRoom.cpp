#include "gsServerRoom.hpp"
#include "../../Vector/CPP/Vector.hpp"
#include "gsServerClient.hpp"
#include "../../Blob/CPP/Blob.hpp"
#include "../../ExternalString/CPP/ExternalString.hpp"
#include "../../InternalString/CPP/InternalString.hpp"
#include "../../Assert/CPP/Assert.hpp"
#include "../GameStrutClient/gsClient.hpp"
#include "gsServer.hpp"

namespace NumbatLogic
{
	class gsServerRoom;
	template <class T>
	class Vector;
	class gsServerClient;
	class ExternalString;
	class InternalString;
	class Assert;
	class gsBlob;
	class gsClient;
	class gsServer;
}
namespace NumbatLogic
{
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

	void gsServerRoom::OnSync(unsigned int nSyncId, unsigned int nSyncType, gsBlob* pInBlob, gsServerClient* pServerClient)
	{
	}

	gsServerRoom::gsServerRoom(unsigned int nRoomId, const char* sxRoomType, gsServer* pServer)
	{
		__nRoomId = 0;
		__nRoomType = 0;
		__sRoomType = 0;
		__pServer = 0;
		__pClientVector = 0;
		__nRoomId = nRoomId;
		__nRoomType = ExternalString::GetChecksum(sxRoomType);
		__sRoomType = new InternalString(sxRoomType);
		__pServer = pServer;
		__pClientVector = new Vector<gsServerClient*>();
	}

	void gsServerRoom::__ClientJoin(gsServerClient* pClient)
	{
		Assert::Plz(GetClientByClientId(pClient->__nClientId) == 0);
		__pClientVector->PushBack(pClient);
		pClient->__pRoomVector->PushBack(this);
		gsBlob* pJoinBlob = OnClientJoin(pClient);
		gsBlob* pBlob = new gsBlob();
		pBlob->PackUint32(__nRoomId);
		pBlob->PackUint32(__nRoomType);
		pBlob->PackBool(false);
		pBlob->PackBlob(pJoinBlob);
		pClient->Send(0, gsClient::__ROOM_JOIN_HASH, pBlob);
		if (pJoinBlob) delete pJoinBlob;
		if (pBlob) delete pBlob;
	}

	void gsServerRoom::__ClientLeave(gsServerClient* pClient)
	{
		for (int i = 0; i < __pClientVector->GetSize(); i++)
		{
			if (__pClientVector->Get(i) == pClient)
			{
				OnClientLeave(pClient);
				__pClientVector->Erase(i);
				for (int j = 0; j < pClient->__pRoomVector->GetSize(); j++)
				{
					if (pClient->__pRoomVector->Get(j) == this)
					{
						pClient->__pRoomVector->Erase(j);
						gsBlob* pBlob = new gsBlob();
						pBlob->PackUint32(__nRoomId);
						pBlob->PackUint32(__nRoomType);
						pClient->Send(0, gsClient::__ROOM_LEAVE_HASH, pBlob);
						if (pBlob) delete pBlob;
						return;
					}
				}
				Assert::Plz(false);
			}
		}
		Assert::Plz(false);
	}

	gsServerRoom::~gsServerRoom()
	{
		if (__sRoomType) delete __sRoomType;
		if (__pClientVector) delete __pClientVector;
	}

}

