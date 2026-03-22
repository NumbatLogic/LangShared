#include "GameStrutTestUtil.hpp"
#include "../../Source/GameStrutClient/CPP/gsServerSocket.hpp"
#include "../../Source/GameStrutClient/CPP/gsClientSocket.hpp"
#include "../../Source/Utils/CPP/Utils.hpp"
#include "../GameStrutServer/gsServer.hpp"
#include "../GameStrutClient/gsClient.hpp"
#include "../Vector/OwnedVector.hpp"

namespace NumbatLogic
{
	class GameStrutTestUtil;
	class gsServerSocket;
	class gsClientSocket;
	class Utils;
	class gsServer;
	class gsClient;
	template <class T>
	class OwnedVector;
}
#line 0 "/home/cliffya/git/LangShared/Source/GameStrutTest/GameStrutTestUtil.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/LangShared/Source/GameStrutTest/GameStrutTestUtil.nll"
#line 5 "/home/cliffya/git/LangShared/Source/GameStrutTest/GameStrutTestUtil.nll"
	void GameStrutTestUtil::Update(gsServerSocket* pServerSocket, gsClientSocket* pClientSocket)
	{
		int nNotPendingCount = 0;
		while (nNotPendingCount < 10)
		{
			pServerSocket->Update();
			pClientSocket->Update();
#line 13 "/home/cliffya/git/LangShared/Source/GameStrutTest/GameStrutTestUtil.nll"
			if (pServerSocket->Pending() || pClientSocket->Pending())
				nNotPendingCount = 0;
			else
				nNotPendingCount++;
			Utils::Sleep(5 + nNotPendingCount);
		}
	}

	void GameStrutTestUtil::Update(gsServer* pServer, gsClient* pClient)
	{
		int nNotPendingCount = 0;
		while (nNotPendingCount < 10)
		{
			pServer->Update();
			pClient->Update();
#line 29 "/home/cliffya/git/LangShared/Source/GameStrutTest/GameStrutTestUtil.nll"
			if (pServer->Pending() || pClient->GetPending())
				nNotPendingCount = 0;
			else
				nNotPendingCount++;
			Utils::Sleep(5 + nNotPendingCount);
		}
	}

	void GameStrutTestUtil::UpdateVector(gsServer* pServer, OwnedVector<gsClient*>* pClientVector)
	{
		int nNotPendingCount = 0;
		while (nNotPendingCount < 10)
		{
			pServer->Update();
			for (int i = 0; i < pClientVector->GetSize(); i++)
			{
				gsClient* pClient = pClientVector->Get(i);
				pClient->Update();
			}
#line 49 "/home/cliffya/git/LangShared/Source/GameStrutTest/GameStrutTestUtil.nll"
			bool bPending = pServer->Pending();
			if (!bPending)
			{
				for (int i = 0; i < pClientVector->GetSize(); i++)
				{
					gsClient* pClient = pClientVector->Get(i);
					if (pClient->GetPending())
					{
						bPending = true;
						break;
					}
				}
			}
#line 63 "/home/cliffya/git/LangShared/Source/GameStrutTest/GameStrutTestUtil.nll"
			if (bPending)
				nNotPendingCount = 0;
			else
				nNotPendingCount++;
			Utils::Sleep(5 + nNotPendingCount);
		}
	}

}

