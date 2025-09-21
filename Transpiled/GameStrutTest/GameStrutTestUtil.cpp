#include "GameStrutTestUtil.hpp"
#include "../../GameStrutClient/CPP/gsServerSocket.hpp"
#include "../../GameStrutClient/CPP/gsClientSocket.hpp"
#include "../GameStrutServer/gsServer.hpp"
#include "../GameStrutClient/gsClient.hpp"

namespace NumbatLogic
{
	class GameStrutTestUtil;
	class gsServerSocket;
	class gsClientSocket;
	class gsServer;
	class gsClient;
}
namespace NumbatLogic
{
	void GameStrutTestUtil::Update(gsServerSocket* pServerSocket, gsClientSocket* pClientSocket)
	{
		int nNotPendingCount = 0;
		while (nNotPendingCount < 5)
		{
			pServerSocket->Update();
			pClientSocket->Update();
			if (pServerSocket->Pending() || pClientSocket->Pending())
				nNotPendingCount = 0;
			else
				nNotPendingCount++;
		}
	}

	void GameStrutTestUtil::Update(gsServer* pServer, gsClient* pClient)
	{
		int nNotPendingCount = 0;
		while (nNotPendingCount < 5)
		{
			pServer->Update();
			pClient->Update();
			if (pServer->Pending() || pClient->GetPending())
				nNotPendingCount = 0;
			else
				nNotPendingCount++;
		}
	}

}

