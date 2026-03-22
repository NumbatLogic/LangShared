#pragma once

#include "../GameStrutServer/gsServer.hpp"

namespace NumbatLogic
{
	class gsServer;
}
#line 0 "/home/cliffya/git/LangShared/Source/GameStrutTest/TestServer.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/LangShared/Source/GameStrutTest/TestServer.nll"
	class TestServer : public gsServer
	{
		public: TestServer(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath);
	};
}

