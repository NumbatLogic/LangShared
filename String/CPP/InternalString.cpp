#include "Blob.hpp"
#include "Assert.hpp"
#include "InternalString.hpp"

#include <stdio.h>
#include <stdlib.h>

namespace NumbatLogic
{
	InternalString::InternalString(const char* sxString)
	{
		m_sxBuffer = NULL;
		m_nBufferSize = 0;
		m_nByteLength = 0;
		m_nCharLength = 0;
		Set(sxString);
	}

	InternalString::~InternalString()
	{
		if (m_sxBuffer)
			delete [] m_sxBuffer;
	}

	InternalString* InternalString::CreateClone()
	{
		return new InternalString(m_sxBuffer);
	}

	void InternalString::Set(const char* sxString)
	{
		GetUtf8Length(sxString, &m_nCharLength, &m_nByteLength);
		Resize(m_nByteLength);
		memcpy(m_sxBuffer, sxString, m_nByteLength);
		m_sxBuffer[m_nByteLength] = 0;
	}

	const char* InternalString::GetExternalString() const
	{
		return m_sxBuffer;
	}

	void InternalString::Append(const char* sxString)
	{
		AppendString(sxString);
	}

	void InternalString::AppendChar(unsigned short nChar)
	{
		if (nChar <= 0x7F)
		{
			m_sxBuffer[m_nByteLength] = (unsigned char)nChar;
			m_nCharLength++;
			m_nByteLength++;
			Resize(m_nByteLength);
			m_sxBuffer[m_nByteLength] = 0;
			return;
		}

		if (nChar <= 0x7FF)
		{
			Resize(m_nByteLength + 2);
			m_nCharLength++;
			m_sxBuffer[m_nByteLength++] = 0xC0 | ((nChar >> 6) & 0xFF);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 0) & 0x3F);
			m_sxBuffer[m_nByteLength] = 0;
			return;
		}

		if (nChar <= 0xFFFF)
		{
			Resize(m_nByteLength + 3);
			m_nCharLength++;
			m_sxBuffer[m_nByteLength++] = 0xE0 | ((nChar >> 12) & 0xFF);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 6) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 0) & 0x3F);
			m_sxBuffer[m_nByteLength] = 0;
			return;
		}

		/*if (nChar <= 0x1FFFFF)
		   {
			Resize(m_nByteLength+4);
			m_nCharLength++;
			m_sxBuffer[m_nByteLength++] = 0xF0 | ((nChar >> 18) & 0xFF);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 12) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 6) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 0) & 0x3F);
			m_sxBuffer[m_nByteLength] = 0;
			return;
		   }

		   if (nChar <= 0x3FFFFFF)
		   {
			Resize(m_nByteLength+5);
			m_nCharLength++;
			m_sxBuffer[m_nByteLength++] = 0xF8 | ((nChar >> 24) & 0xFF);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 18) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 12) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 6) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 0) & 0x3F);
			m_sxBuffer[m_nByteLength] = 0;
			return;
		   }

		   if (nChar <= 0x7FFFFFFF)
		   {
			Resize(m_nByteLength+6);
			m_nCharLength++;
			m_sxBuffer[m_nByteLength++] = 0xFC | ((nChar >> 30) & 0xFF);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 24) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 18) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 12) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 6) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 0) & 0x3F);
			m_sxBuffer[m_nByteLength] = 0;
			return;
		   }*/

		CLIFFY_ASSERT(false);
	}

	void InternalString::AppendString(const char* sxString)
	{
		int nCharLength = 0;
		int nByteLength = 0;
		GetUtf8Length(sxString, &nCharLength, &nByteLength);
		Resize(m_nByteLength + nByteLength);
		memcpy(m_sxBuffer + m_nByteLength, sxString, nByteLength);
		m_nCharLength += nCharLength;
		m_nByteLength += nByteLength;
		m_sxBuffer[m_nByteLength] = 0;
	}

	void InternalString::AppendInt(int nInt)
	{
		if (nInt == -0)
			nInt = 0;

		char sxTemp[1024];
		sprintf(sxTemp, "%d", nInt);
		AppendString(sxTemp);
	}

	void InternalString::AppendUnsignedInt(unsigned int nUint32)
	{
		AppendUint32(nUint32);
	}

	void InternalString::AppendUint32(unsigned int nUint32)
	{
		char sxTemp[1024];
		sprintf(sxTemp, "%u", nUint32);
		AppendString(sxTemp);
	}

	void InternalString::AppendDouble(double fDouble)
	{
		char sxTemp[1024];
		sprintf(sxTemp, "%G", fDouble);
		if (strcmp(sxTemp, "-0") == 0)
			AppendString("0");
		else
			AppendString(sxTemp);
	}

	void InternalString::PrependChar(unsigned short nChar)
	{
		int nCharSize = GetCharSize(nChar);
		Resize(m_nByteLength + nCharSize);

		memmove(m_sxBuffer + nCharSize, m_sxBuffer, m_nByteLength);

		EncodeChar(nChar, (unsigned char*)m_sxBuffer);

		m_nCharLength++;
		m_nByteLength += nCharSize;
		m_sxBuffer[m_nByteLength] = 0;
	}

	void InternalString::PrependString(const char* sxString)
	{
		int nCharLength = 0;
		int nByteLength = 0;
		GetUtf8Length(sxString, &nCharLength, &nByteLength);
		Resize(m_nByteLength + nByteLength);
		memmove(m_sxBuffer + nByteLength, m_sxBuffer, m_nByteLength);
		memcpy(m_sxBuffer, sxString, nByteLength);

		m_nCharLength += nCharLength;
		m_nByteLength += nByteLength;
		m_sxBuffer[m_nByteLength] = 0;
	}

	void InternalString::AppendStringData(unsigned char* pData, int nLength)
	{
		// not utf8
		int nNewLength = m_nCharLength + nLength;
		Resize(nNewLength);

		memcpy(m_sxBuffer + m_nCharLength, pData, nLength);

		m_nCharLength = nNewLength;
		m_nByteLength = m_nCharLength;
		m_sxBuffer[m_nByteLength] = 0;
	}

	void InternalString::SubStr(int nStart, int nLength)
	{
		CLIFFY_ASSERT(nStart >= 0);
		CLIFFY_ASSERT(nLength >= 0);
		CLIFFY_ASSERT(nStart + nLength <= m_nCharLength);

		if (IsAscii())
		{
			memmove(m_sxBuffer, m_sxBuffer+nStart, nLength);
			m_sxBuffer[nLength] = 0;
			m_nCharLength = nLength;
			m_nByteLength = nLength;
			return;
		}

		int i;
		unsigned char* p = (unsigned char*)m_sxBuffer;
		for (i = 0; i < nStart; i++)
			p += GetUtf8CharSize((*p));

		char* sxTemp = new char[m_nBufferSize];

		unsigned char* pOut = (unsigned char*)sxTemp;
		for (i = 0; i < nLength; i++)
		{
			unsigned short nChar = DecodeChar(p);
			int nCharSize = EncodeChar(nChar, pOut);

			p += nCharSize;
			pOut += nCharSize;
		}
		(*pOut) = 0;

		m_nCharLength = nLength;
		m_nByteLength = (int)(pOut - (unsigned char*)sxTemp);

		delete m_sxBuffer;
		m_sxBuffer = sxTemp;
	}

	/*void InternalString :: CropBack(int nLength)
	   {
		CLIFFY_ASSERT(nLength <= m_nCharLength);
		SubStr(0, m_nCharLength - nLength);
	   }*/

	void InternalString::CropFront(int nLength)
	{
		CLIFFY_ASSERT(nLength >= 0);
		CLIFFY_ASSERT(nLength <= m_nCharLength);

		int i;
		unsigned char* p = (unsigned char*)m_sxBuffer;
		for (i = 0; i < nLength; i++)
			p += GetUtf8CharSize((*p));

		m_nByteLength -= (int)(p - (unsigned char*)m_sxBuffer);
		m_nCharLength -= nLength;

		memmove(m_sxBuffer, p, m_nByteLength);
		m_sxBuffer[m_nByteLength] = 0;
	}

	int InternalString::GetLength()
	{
		return m_nCharLength;
	}

	unsigned short InternalString::GetChar(int nIndex)
	{
		CLIFFY_ASSERT(nIndex >= 0);
		CLIFFY_ASSERT(nIndex < m_nCharLength);

		int i;
		unsigned char* p = (unsigned char*)m_sxBuffer;
		for (i = 0; i < nIndex; i++)
			p += GetUtf8CharSize((*p));
		return DecodeChar(p);
	}

	void InternalString::BlobWriteUtf8(BlobView* pBlobView, bool bZeroTerminator)
	{
		unsigned char* p = (unsigned char*)m_sxBuffer;
		pBlobView->PackData(p, m_nByteLength);
		if (bZeroTerminator)
			pBlobView->PackUint8(0);
	}

	void InternalString::BlobWrite16Bit(BlobView* pBlobView, bool bZeroTerminator)
	{
		int i;
		unsigned char* p = (unsigned char*)m_sxBuffer;
		for (i = 0; i < m_nCharLength; i++)
		{
			pBlobView->PackUint16(DecodeChar(p));
			p += GetUtf8CharSize(p[0]);
		}
		if (bZeroTerminator)
			pBlobView->PackUint16(0);
	}

	bool InternalString::IsAscii()
	{
		return m_nCharLength == m_nByteLength;
	}

	bool InternalString::IsEqual(const char* sxCompare)
	{
		return strcmp(m_sxBuffer, sxCompare) == 0;
	}

	bool InternalString::StartsWith(const char* sxString)
	{
		int nCharLength;
		int nByteLength;
		GetUtf8Length(sxString, &nCharLength, &nByteLength);

		if (nByteLength <= m_nByteLength)
			if (memcmp(sxString, m_sxBuffer, nByteLength) == 0)
				return true;
		return false;
	}

	bool InternalString::EndsWith(const char* sxString)
	{
		int nCharLength;
		int nByteLength;
		GetUtf8Length(sxString, &nCharLength, &nByteLength);

		if (nByteLength <= m_nByteLength)
			if (memcmp(sxString, m_sxBuffer + m_nByteLength - nByteLength, nByteLength) == 0)
				return true;
		return false;
	}

	double InternalString::ParseDouble()
	{
		double fTemp = 0.0f;
		sscanf(m_sxBuffer, "%lf", &fTemp);
		return fTemp;
	}

	unsigned int InternalString::ParseHex()
	{
		unsigned int nTemp;
		sscanf(m_sxBuffer, "%x", &nTemp);
		return nTemp;
	}

	int InternalString::FindChar(unsigned short nChar)
	{
		int nIndex = 0;
		unsigned char* p = (unsigned char*)m_sxBuffer;
		while (nIndex < m_nCharLength)
		{
			unsigned short nTestChar = DecodeChar(p);
			if (nTestChar == nChar)
				return nIndex;
			p += GetUtf8CharSize((*p));
			nIndex++;
		}
		return -1;
	}

	// probably broken...
	void InternalString::Replace(const char* sxFind, const char* sxReplace)
	{
		InternalString* sFind = new InternalString(sxFind);
		InternalString* sReplace = new InternalString(sxReplace);
		int nByteLengthDelta = sReplace->m_nByteLength - sFind->m_nByteLength;
		int nCharLengthDelta = sReplace->m_nCharLength - sFind->m_nCharLength;

		int nOffset = 0;
		while (true)
		{
			if (nOffset + sFind->m_nByteLength > m_nByteLength)
			{
				delete sFind;
				delete sReplace;
				return;
			}

			unsigned char c = m_sxBuffer[nOffset];
			if (c == 0)
				break;

			if (memcmp(m_sxBuffer + nOffset, sFind->m_sxBuffer, sFind->m_nByteLength) == 0)
			{
				if (nByteLengthDelta > 0)
					Resize(m_nByteLength + nByteLengthDelta);

				int nFrom = nOffset + sFind->m_nByteLength;
				int nTo = nFrom + nByteLengthDelta;
				int nRemain = m_nByteLength - nFrom + 1;
				if (nRemain < 1)
					nRemain = 1;
				memmove(m_sxBuffer+nTo, m_sxBuffer+nFrom, nRemain);
				memcpy(m_sxBuffer + nOffset, sReplace->m_sxBuffer, sReplace->m_nByteLength);

				m_nByteLength += nByteLengthDelta;
				nCharLengthDelta += nCharLengthDelta;

				nOffset = nTo;
				continue;
			}

			nOffset += GetUtf8CharSize(c);
		}

		delete sFind;
		delete sReplace;
	}

	void InternalString::Resize(int nSize)
	{
		CLIFFY_ASSERT(nSize < 1024 * 1024 * 100);
		nSize++;
		if (m_nBufferSize < nSize)
		{
			nSize *= 2;
			char* sxTemp = new char[nSize];
			if (m_sxBuffer)
			{
				memcpy(sxTemp, m_sxBuffer, m_nBufferSize);
				delete [] 
				m_sxBuffer;
			}
			m_sxBuffer = sxTemp;
			m_nBufferSize = nSize;
		}
	}

	int InternalString::GetCharSize(unsigned short nChar)
	{
		if (nChar <= 0x7F)
			return 1;
		if (nChar <= 0x7FF)
			return 2;
		if (nChar <= 0xFFFF)
			return 3;

		/*if (nChar <= 0x1FFFFF)
		   {
			Resize(m_nByteLength+4);
			m_nCharLength++;
			m_sxBuffer[m_nByteLength++] = 0xF0 | ((nChar >> 18) & 0xFF);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 12) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 6) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 0) & 0x3F);
			m_sxBuffer[m_nByteLength] = 0;
			return;
		   }

		   if (nChar <= 0x3FFFFFF)
		   {
			Resize(m_nByteLength+5);
			m_nCharLength++;
			m_sxBuffer[m_nByteLength++] = 0xF8 | ((nChar >> 24) & 0xFF);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 18) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 12) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 6) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 0) & 0x3F);
			m_sxBuffer[m_nByteLength] = 0;
			return;
		   }

		   if (nChar <= 0x7FFFFFFF)
		   {
			Resize(m_nByteLength+6);
			m_nCharLength++;
			m_sxBuffer[m_nByteLength++] = 0xFC | ((nChar >> 30) & 0xFF);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 24) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 18) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 12) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 6) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 0) & 0x3F);
			m_sxBuffer[m_nByteLength] = 0;
			return;
		   }*/

		CLIFFY_ASSERT(false);
		return 0;
	}

	int InternalString::GetUtf8CharSize(unsigned char cLeadChar)
	{
		if (cLeadChar < 128)
			return 1;
		if (cLeadChar < 234)
			return 2;
		if (cLeadChar < 240)
			return 3;
		return 4;
	}

	bool InternalString::GetUtf8Length(const char* sxString, int* pCharLength, int* pByteLength)
	{
		const char* p = sxString;
		(*pCharLength) = 0;
		(*pByteLength) = 0;

		while (true)
		{
			unsigned char c = p[(*pByteLength)];

			if (c == 0)
				break;

			int nCharSize = GetUtf8CharSize(c);
			(*pCharLength)++;
			(*pByteLength) += nCharSize;
		}

		return true;
	}

	unsigned short InternalString::DecodeChar(unsigned char* pUtf8Char)
	{
		if (pUtf8Char[0] <= 0x7F)
			return pUtf8Char[0];

		if ((pUtf8Char[0] & 0xE0) == 0xC0)	// 110xxxxx
		{
			if ((pUtf8Char[1] & 0xC0) != 0x80)	// 10xxxxxx
				return 0;
			return (((unsigned short)(pUtf8Char[0] & 0x1F)) << 6) + (pUtf8Char[1] & 0x3F);
		}

		if ((pUtf8Char[0] & 0xF0) == 0xE0)	// 1110xxxx
		{
			if ((pUtf8Char[1] & 0xC0) != 0x80)	// 10xxxxxx
				return 0;
			if ((pUtf8Char[2] & 0xC0) != 0x80)	// 10xxxxxx
				return 0;

			// untested
			return (((unsigned short)(pUtf8Char[0] & 0x1F)) << 12) + (((unsigned short)(pUtf8Char[1] & 0x3F)) << 6) + (pUtf8Char[2] & 0x3F);
		}

		//printf("%04X - %s\n", pUtf8Char[0], pUtf8Char);
		CLIFFY_ASSERT(false);

		return 0;
	}

	int InternalString::EncodeChar(unsigned short nChar, unsigned char* pBuffer)
	{
		if (nChar <= 0x7F)
		{
			pBuffer[0] = (unsigned char)nChar;
			return 1;
		}

		if (nChar <= 0x7FF)
		{
			pBuffer[0] = 0xC0 | ((nChar >> 6) & 0xFF);
			pBuffer[1] = 0x80 | ((nChar >> 0) & 0x3F);
			return 2;
		}

		if (nChar <= 0xFFFF)
		{
			pBuffer[0] = 0xE0 | ((nChar >> 12) & 0xFF);
			pBuffer[1] = 0x80 | ((nChar >> 6) & 0x3F);
			pBuffer[2] = 0x80 | ((nChar >> 0) & 0x3F);
			return 3;
		}

		/*if (nChar <= 0x1FFFFF)
		   {
			Resize(m_nByteLength+4);
			m_nCharLength++;
			m_sxBuffer[m_nByteLength++] = 0xF0 | ((nChar >> 18) & 0xFF);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 12) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 6) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 0) & 0x3F);
			m_sxBuffer[m_nByteLength] = 0;
			return;
		   }

		   if (nChar <= 0x3FFFFFF)
		   {
			Resize(m_nByteLength+5);
			m_nCharLength++;
			m_sxBuffer[m_nByteLength++] = 0xF8 | ((nChar >> 24) & 0xFF);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 18) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 12) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 6) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 0) & 0x3F);
			m_sxBuffer[m_nByteLength] = 0;
			return;
		   }

		   if (nChar <= 0x7FFFFFFF)
		   {
			Resize(m_nByteLength+6);
			m_nCharLength++;
			m_sxBuffer[m_nByteLength++] = 0xFC | ((nChar >> 30) & 0xFF);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 24) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 18) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 12) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 6) & 0x3F);
			m_sxBuffer[m_nByteLength++] = 0x80 | ((nChar >> 0) & 0x3F);
			m_sxBuffer[m_nByteLength] = 0;
			return;
		   }*/

		CLIFFY_ASSERT(false);
		return 0;
	}
}