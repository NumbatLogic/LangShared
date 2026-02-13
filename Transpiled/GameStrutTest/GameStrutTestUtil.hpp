#pragma once

#include "../Vector/OwnedVector.hpp"

namespace NumbatLogic
{
	class gsServerSocket;
	class gsClientSocket;
	class gsServer;
	class gsClient;
	template <class T>
	class OwnedVector;
}
namespace NumbatLogic
{
	class GameStrutTestUtil
	{
		public: static void Update(gsServerSocket* pServerSocket, gsClientSocket* pClientSocket);
		public: static void Update(gsServer* pServer, gsClient* pClient);
		public: static void UpdateVector(gsServer* pServer, OwnedVector<gsClient*>* pClientVector);
	};
}

