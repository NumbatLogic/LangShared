#include "TestServer.hpp"

namespace NumbatLogic
{
	class TestServer;
	class gsServer;
}
#line 0 "/home/cliffya/git/LangShared/Source/GameStrutTest/TestServer.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/LangShared/Source/GameStrutTest/TestServer.nll"
#line 5 "/home/cliffya/git/LangShared/Source/GameStrutTest/TestServer.nll"
	TestServer::TestServer(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath) : gsServer(sxAddress, nPort, nVersion, sxDatabasePath)
	{
	}

}

