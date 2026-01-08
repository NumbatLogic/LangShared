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
				unsigned long hash = 0;
        		int c = 0;

				const char* p = szString;
				while (c = *p++)
					hash = c + (hash << 6) + (hash << 16) - hash;

				return (unsigned int)hash;
			}

			static long hextol(const char* szString);

			static int atoi(const char* szString);

			static double atof(const char* szString);
			static long atol(const char* szString);


			static int GetByteLength(const char* sxString);
	};
}