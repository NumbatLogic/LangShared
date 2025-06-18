#pragma once

#include <stdint.h>

namespace NumbatLogic
{
	class InternalString;
	class Utils
	{
		public:
			static double Pow(double fBase, double fExponent);
			static double ByteConvertUint64ToDouble(uint64_t nValue);
			static int32_t ByteConvertUint32ToInt32(uint32_t nValue);
			static uint32_t ByteConvertInt32ToUint32(int32_t nValue);

			static void Indent(int nTabDepth, InternalString* sOut);
	};
}

