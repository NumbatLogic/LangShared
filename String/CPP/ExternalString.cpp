#include "ExternalString.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <cstring>

namespace NumbatLogic
{
	bool ExternalString::Equal(const char* sxA, const char* sxB)
	{
		return strcmp(sxA, sxB) == 0;
	}

	// a bad checksum
	int ExternalString::GetChecksum(const char* sxString)
	{
		int nResult = 0xABC123;
		const char* p = sxString;
		while (*p)
			nResult = (nResult ^ *(p++)) << 1;
		return nResult;
	}

	long ExternalString::hextol(const char* sxString)
	{
		return ::strtol(sxString, NULL, 16);
	}

	int ExternalString::atoi(const char* sxString)
	{
		return ::atoi(sxString);
	}

	double ExternalString::atof(const char* sxString)
	{
		return ::atof(sxString);
	}

	long ExternalString::atol(const char* sxString)
	{
		return ::atol(sxString);
	}
}