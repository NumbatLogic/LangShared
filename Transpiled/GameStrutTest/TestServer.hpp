#pragma once

#include "../GameStrutServer/gsServer.hpp"

namespace NumbatLogic
{
	class gsServer;
}
#line 0 "../LangShared/Transpiled/GameStrutTest/TestServer.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutTest/TestServer.nll"
	class TestServer : public gsServer
	{
		public: TestServer(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath);
	};
}

