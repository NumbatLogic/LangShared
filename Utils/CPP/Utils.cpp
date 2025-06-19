#include "../../InternalString/CPP/InternalString.hpp"
#include "Utils.hpp"

#include <math.h>

namespace NumbatLogic
{
	double Utils::Pow(double fBase, double fExponent)
	{
		return pow(fBase, fExponent);
	}

	double Utils::ByteConvertUint64ToDouble(uint64_t nValue)
	{
		return *(double*)(&nValue);
	}

	int32_t Utils::ByteConvertUint32ToInt32(uint32_t nValue)
	{
		return *(int32_t*)(&nValue);
	}

	uint32_t Utils::ByteConvertInt32ToUint32(int32_t nValue)
	{
		return *(uint32_t*)(&nValue);
	}

	void Utils::Indent(int nTabDepth, InternalString* sOut)
	{
		int i;
		for (i = 0; i < nTabDepth; i++)
			sOut->AppendChar('\t');
	}
}