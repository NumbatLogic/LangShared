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
#line 1 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
	class GameStrutTestUtil
	{
#line 6 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
		public: static void Update(gsServerSocket* pServerSocket, gsClientSocket* pClientSocket);
#line 22 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
		public: static void Update(gsServer* pServer, gsClient* pClient);
#line 38 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
		public: static void UpdateVector(gsServer* pServer, OwnedVector<gsClient*>* pClientVector);
	};
}

