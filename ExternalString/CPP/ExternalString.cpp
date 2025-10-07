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

	int ExternalString::GetByteLength(const char* sxString)
	{
		return strlen(sxString);
	}

}