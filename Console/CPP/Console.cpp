#include "Console.hpp"
#include <stdio.h>

namespace NumbatLogic
{
	void Console::Log(const char* sxLog)
	{
		printf("%s\n", sxLog);
		fflush(stdout);
	}
}