#pragma once

namespace NumbatLogic
{
	class ExternalString
	{
		public:
			static bool Equal(const char* szA, const char* szB);
		
			// a bad checksum
			static constexpr unsigned int GetChecksum(const char* szString)
			{
				unsigned int nResult = 0xABC123;
				const char* p = szString;
				while (*p)
					nResult = (nResult ^ *(p++)) << 2;
				return nResult;
			}

			static long hextol(const char* szString);

			static int atoi(const char* szString);

			static double atof(const char* szString);
			static long atol(const char* szString);


			static int GetByteLength(const char* sxString);
	};
}