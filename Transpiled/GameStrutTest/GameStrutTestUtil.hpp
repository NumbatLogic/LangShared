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
#line 0 "/home/cliffya/git/LangShared/Source/GameStrutTest/GameStrutTestUtil.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/LangShared/Source/GameStrutTest/GameStrutTestUtil.nll"
	class GameStrutTestUtil
	{
		public: static void Update(gsServerSocket* pServerSocket, gsClientSocket* pClientSocket);
#line 21 "/home/cliffya/git/LangShared/Source/GameStrutTest/GameStrutTestUtil.nll"
		public: static void Update(gsServer* pServer, gsClient* pClient);
#line 37 "/home/cliffya/git/LangShared/Source/GameStrutTest/GameStrutTestUtil.nll"
		public: static void UpdateVector(gsServer* pServer, OwnedVector<gsClient*>* pClientVector);
	};
}

