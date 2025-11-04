#include "TestServer.hpp"

namespace NumbatLogic
{
	class TestServer;
	class gsServer;
}
namespace NumbatLogic
{
	TestServer::TestServer(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath) : gsServer(sxAddress, nPort, nVersion, sxDatabasePath)
	{
	}

}

