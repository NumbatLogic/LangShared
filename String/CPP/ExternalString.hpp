#pragma once

namespace NumbatLogic
{
	class ExternalString
	{
		public:
			static bool Equal(const char* sxA, const char* sxB);
			static int GetChecksum(const char* sxString);
			static long hextol(const char* sxString);

			static int atoi(const char* sxString);

			static double atof(const char* sxString);
			static long atol(const char* sxString);
	};
}