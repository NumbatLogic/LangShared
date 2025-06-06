#include "Console.hpp"
#include <stdio.h>

namespace NumbatLogic
{
	void Console::Log(const char* sxMessage)
	{
		printf("%s\n", sxMessage);
		fflush(stdout);
	}
}