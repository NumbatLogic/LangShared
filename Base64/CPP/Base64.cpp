#include "Base64.hpp"
#include "base64/base64.h"

#include "../../Blob/CPP/Blob.hpp"
//#include "../../ExternalString/CPP/ExternalString.hpp"
//#include "../../InternalString/CPP/InternalString.hpp"

#include <cstring>

namespace NumbatLogic
{
	gsBlob* Base64::Decode(const char* sxBase64)
	{
		int nSize;
		unsigned char* pData = unbase64(sxBase64, strlen(sxBase64), &nSize);

		gsBlob* pBlob = new gsBlob();
		pBlob->PackData(pData, nSize);
		pBlob->SetOffset(0);

		return pBlob;
	}
}
