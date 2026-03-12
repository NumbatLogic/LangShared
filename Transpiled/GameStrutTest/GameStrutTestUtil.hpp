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
#line 0 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
	class GameStrutTestUtil
	{
		public: static void Update(gsServerSocket* pServerSocket, gsClientSocket* pClientSocket);
#line 21 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
		public: static void Update(gsServer* pServer, gsClient* pClient);
#line 37 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
		public: static void UpdateVector(gsServer* pServer, OwnedVector<gsClient*>* pClientVector);
	};
}

