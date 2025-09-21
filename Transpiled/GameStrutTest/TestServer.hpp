#pragma once

#include "../GameStrutServer/gsServer.hpp"

namespace NumbatLogic
{
	class gsServer;
}
namespace NumbatLogic
{
	class TestServer : public gsServer
	{
		public: TestServer(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath);
	};
}

