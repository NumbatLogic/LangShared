#pragma once

namespace NumbatLogic
{
	class gsServerSocket;
	class gsClientSocket;
	class gsServer;
	class gsClient;
}
namespace NumbatLogic
{
	class GameStrutTestUtil
	{
		public: static void Update(gsServerSocket* pServerSocket, gsClientSocket* pClientSocket);
		public: static void Update(gsServer* pServer, gsClient* pClient);
	};
}

