#pragma once

#include "../GameStrutServer/gsServer.hpp"

namespace NumbatLogic
{
	class gsServer;
}
#line 1 "../LangShared/Transpiled/GameStrutTest/TestServer.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutTest/TestServer.nll"
	class TestServer : public gsServer
	{
#line 6 "../LangShared/Transpiled/GameStrutTest/TestServer.nll"
		public: TestServer(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath);
	};
}

