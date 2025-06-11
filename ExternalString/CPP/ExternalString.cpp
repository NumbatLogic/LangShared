#include "ExternalString.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <cstring>

namespace NumbatLogic
{
	bool ExternalString::Equal(const char* szA, const char* szB)
	{
		return strcmp(szA, szB) == 0;
	}

	// a bad checksum
	int ExternalString::GetChecksum(const char* szString)
	{
		int nResult = 0xABC123;
		const char* p = szString;
		while (*p)
			nResult = (nResult ^ *(p++)) << 1;
		return nResult;
	}

	long ExternalString::hextol(const char* szString)
	{
		return ::strtol(szString, NULL, 16);
	}

	int ExternalString::atoi(const char* szString)
	{
		return ::atoi(szString);
	}

	double ExternalString::atof(const char* szString)
	{
		return ::atof(szString);
	}

	long ExternalString::atol(const char* szString)
	{
		return ::atol(szString);
	}
}