#pragma once

namespace NumbatLogic
{
	class ExternalString
	{
		public:
			static bool Equal(const char* szA, const char* szB);
			static int GetChecksum(const char* szString);
			static long hextol(const char* szString);

			static int atoi(const char* szString);

			static double atof(const char* szString);
			static long atol(const char* szString);
	};
}