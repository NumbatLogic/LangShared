#include "../../Blob/CPP/Blob.hpp"
#include "../../Assert/CPP/Assert.hpp"
#include "InternalString.hpp"

#include <stdio.h>
#include <stdlib.h>

namespace NumbatLogic
{
	InternalString::InternalString(const char* szString)
	{
		m_szBuffer = NULL;
		m_nBufferSize = 0;
		m_nByteLength = 0;
		m_nCharLength = 0;
		Set(szString);
	}

	InternalString::~InternalString()
	{
		if (m_szBuffer)
			delete [] m_szBuffer;
	}

	InternalString* InternalString::CreateClone()
	{
		return new InternalString(m_szBuffer);
	}

	void InternalString::Set(const char* szString)
	{
		GetUtf8Length(szString, &m_nCharLength, &m_nByteLength);
		Resize(m_nByteLength);
		memcpy(m_szBuffer, szString, m_nByteLength);
		m_szBuffer[m_nByteLength] = 0;
	}

	const char* InternalString::GetExternalString() const
	{
		return m_szBuffer;
	}

	void InternalString::Append(const char* szString)
	{
		AppendString(szString);
	}

	void InternalString::AppendChar(unsigned short nChar)
	{
		if (nChar <= 0x7F)
		{
			m_szBuffer[m_nByteLength] = (unsigned char)nChar;
			m_nCharLength++;
			m_nByteLength++;
			Resize(m_nByteLength);
			m_szBuffer[m_nByteLength] = 0;
			return;
		}

		if (nChar <= 0x7FF)
		{
			Resize(m_nByteLength + 2);
			m_nCharLength++;
			m_szBuffer[m_nByteLength++] = 0xC0 | ((nChar >> 6) & 0xFF);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 0) & 0x3F);
			m_szBuffer[m_nByteLength] = 0;
			return;
		}

		if (nChar <= 0xFFFF)
		{
			Resize(m_nByteLength + 3);
			m_nCharLength++;
			m_szBuffer[m_nByteLength++] = 0xE0 | ((nChar >> 12) & 0xFF);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 6) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 0) & 0x3F);
			m_szBuffer[m_nByteLength] = 0;
			return;
		}

		/*if (nChar <= 0x1FFFFF)
			{
			Resize(m_nByteLength+4);
			m_nCharLength++;
			m_szBuffer[m_nByteLength++] = 0xF0 | ((nChar >> 18) & 0xFF);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 12) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 6) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 0) & 0x3F);
			m_szBuffer[m_nByteLength] = 0;
			return;
			}

			if (nChar <= 0x3FFFFFF)
			{
			Resize(m_nByteLength+5);
			m_nCharLength++;
			m_szBuffer[m_nByteLength++] = 0xF8 | ((nChar >> 24) & 0xFF);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 18) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 12) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 6) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 0) & 0x3F);
			m_szBuffer[m_nByteLength] = 0;
			return;
			}

			if (nChar <= 0x7FFFFFFF)
			{
			Resize(m_nByteLength+6);
			m_nCharLength++;
			m_szBuffer[m_nByteLength++] = 0xFC | ((nChar >> 30) & 0xFF);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 24) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 18) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 12) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 6) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 0) & 0x3F);
			m_szBuffer[m_nByteLength] = 0;
			return;
			}*/

		Assert::Plz(false);
	}

	void InternalString::AppendString(const char* szString)
	{
		int nCharLength = 0;
		int nByteLength = 0;
		GetUtf8Length(szString, &nCharLength, &nByteLength);
		Resize(m_nByteLength + nByteLength);
		memcpy(m_szBuffer + m_nByteLength, szString, nByteLength);
		m_nCharLength += nCharLength;
		m_nByteLength += nByteLength;
		m_szBuffer[m_nByteLength] = 0;
	}

	void InternalString::AppendInt(int nInt)
	{
		if (nInt == -0)
			nInt = 0;

		char szTemp[32];
		sprintf(szTemp, "%d", nInt);
		AppendString(szTemp);
	}

	void InternalString::AppendUnsignedInt(unsigned int nUint32)
	{
		AppendUint32(nUint32);
	}

	void InternalString::AppendUint32(unsigned int nUint32)
	{
		char szTemp[32];
		sprintf(szTemp, "%u", nUint32);
		AppendString(szTemp);
	}

	void InternalString::AppendDouble(double fDouble)
	{
		char szTemp[32];
		sprintf(szTemp, "%G", fDouble);
		if (strcmp(szTemp, "-0") == 0)
			AppendString("0");
		else
			AppendString(szTemp);
	}

	void InternalString::AppendHex(unsigned int nUint32)
	{
		char szTemp[32]; // 8 hex digits + null terminator
		sprintf(szTemp, "%X", nUint32);
		AppendString(szTemp);
	}

	void InternalString::PrependChar(unsigned short nChar)
	{
		int nCharSize = GetCharSize(nChar);
		Resize(m_nByteLength + nCharSize);

		memmove(m_szBuffer + nCharSize, m_szBuffer, m_nByteLength);

		EncodeChar(nChar, (unsigned char*)m_szBuffer);

		m_nCharLength++;
		m_nByteLength += nCharSize;
		m_szBuffer[m_nByteLength] = 0;
	}

	void InternalString::PrependString(const char* szString)
	{
		int nCharLength = 0;
		int nByteLength = 0;
		GetUtf8Length(szString, &nCharLength, &nByteLength);
		Resize(m_nByteLength + nByteLength);
		memmove(m_szBuffer + nByteLength, m_szBuffer, m_nByteLength);
		memcpy(m_szBuffer, szString, nByteLength);

		m_nCharLength += nCharLength;
		m_nByteLength += nByteLength;
		m_szBuffer[m_nByteLength] = 0;
	}

	void InternalString::AppendStringData(unsigned char* pData, int nLength)
	{
		// not utf8
		int nNewLength = m_nCharLength + nLength;
		Resize(nNewLength);

		memcpy(m_szBuffer + m_nCharLength, pData, nLength);

		m_nCharLength = nNewLength;
		m_nByteLength = m_nCharLength;
		m_szBuffer[m_nByteLength] = 0;
	}

	void InternalString::SubStr(int nStart, int nLength)
	{
		Assert::Plz(nStart >= 0);
		Assert::Plz(nLength >= 0);
		Assert::Plz(nStart + nLength <= m_nCharLength);

		if (IsAscii())
		{
			memmove(m_szBuffer, m_szBuffer+nStart, nLength);
			m_szBuffer[nLength] = 0;
			m_nCharLength = nLength;
			m_nByteLength = nLength;
			return;
		}

		int i;
		unsigned char* p = (unsigned char*)m_szBuffer;
		for (i = 0; i < nStart; i++)
			p += GetUtf8CharSize((*p));

		char* szTemp = new char[m_nBufferSize];

		unsigned char* pOut = (unsigned char*)szTemp;
		for (i = 0; i < nLength; i++)
		{
			unsigned short nChar = DecodeChar(p);
			int nCharSize = EncodeChar(nChar, pOut);

			p += nCharSize;
			pOut += nCharSize;
		}
		(*pOut) = 0;

		m_nCharLength = nLength;
		m_nByteLength = (int)(pOut - (unsigned char*)szTemp);

		delete [] m_szBuffer;
		m_szBuffer = szTemp;
	}

	/*void InternalString :: CropBack(int nLength)
		{
		Assert::Plz(nLength <= m_nCharLength);
		SubStr(0, m_nCharLength - nLength);
		}*/

	void InternalString::CropFront(int nLength)
	{
		Assert::Plz(nLength >= 0);
		Assert::Plz(nLength <= m_nCharLength);

		int i;
		unsigned char* p = (unsigned char*)m_szBuffer;
		for (i = 0; i < nLength; i++)
			p += GetUtf8CharSize((*p));

		m_nByteLength -= (int)(p - (unsigned char*)m_szBuffer);
		m_nCharLength -= nLength;

		memmove(m_szBuffer, p, m_nByteLength);
		m_szBuffer[m_nByteLength] = 0;
	}

	int InternalString::GetLength()
	{
		return m_nCharLength;
	}

	unsigned short InternalString::GetChar(int nIndex)
	{
		Assert::Plz(nIndex >= 0);
		Assert::Plz(nIndex < m_nCharLength);

		int i;
		unsigned char* p = (unsigned char*)m_szBuffer;
		for (i = 0; i < nIndex; i++)
			p += GetUtf8CharSize((*p));
		return DecodeChar(p);
	}

	void InternalString::BlobWriteUtf8(BlobView* pBlobView, bool bZeroTerminator)
	{
		unsigned char* p = (unsigned char*)m_szBuffer;
		pBlobView->PackData(p, m_nByteLength);
		if (bZeroTerminator)
			pBlobView->PackUint8(0);
	}

	void InternalString::BlobWrite16Bit(BlobView* pBlobView, bool bZeroTerminator)
	{
		int i;
		unsigned char* p = (unsigned char*)m_szBuffer;
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

	bool InternalString::IsEqual(const char* szCompare)
	{
		return strcmp(m_szBuffer, szCompare) == 0;
	}

	bool InternalString::StartsWith(const char* szString)
	{
		int nCharLength;
		int nByteLength;
		GetUtf8Length(szString, &nCharLength, &nByteLength);

		if (nByteLength <= m_nByteLength)
			if (memcmp(szString, m_szBuffer, nByteLength) == 0)
				return true;
		return false;
	}

	bool InternalString::EndsWith(const char* szString)
	{
		int nCharLength;
		int nByteLength;
		GetUtf8Length(szString, &nCharLength, &nByteLength);

		if (nByteLength <= m_nByteLength)
			if (memcmp(szString, m_szBuffer + m_nByteLength - nByteLength, nByteLength) == 0)
				return true;
		return false;
	}

	double InternalString::ParseDouble()
	{
		double fTemp = 0.0f;
		sscanf(m_szBuffer, "%lf", &fTemp);
		return fTemp;
	}

	unsigned int InternalString::ParseHex()
	{
		unsigned int nTemp;
		sscanf(m_szBuffer, "%x", &nTemp);
		return nTemp;
	}

	int InternalString::FindChar(unsigned short nChar)
	{
		int nIndex = 0;
		unsigned char* p = (unsigned char*)m_szBuffer;
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

			unsigned char c = m_szBuffer[nOffset];
			if (c == 0)
				break;

			if (memcmp(m_szBuffer + nOffset, sFind->m_szBuffer, sFind->m_nByteLength) == 0)
			{
				if (nByteLengthDelta > 0)
					Resize(m_nByteLength + nByteLengthDelta);

				int nFrom = nOffset + sFind->m_nByteLength;
				int nTo = nFrom + nByteLengthDelta;
				int nRemain = m_nByteLength - nFrom + 1;
				if (nRemain < 1)
					nRemain = 1;
				memmove(m_szBuffer+nTo, m_szBuffer+nFrom, nRemain);
				memcpy(m_szBuffer + nOffset, sReplace->m_szBuffer, sReplace->m_nByteLength);

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
		Assert::Plz(nSize < 1024 * 1024 * 100);
		nSize++;
		if (m_nBufferSize < nSize)
		{
			nSize *= 2;
			char* szTemp = new char[nSize];
			if (m_szBuffer)
			{
				memcpy(szTemp, m_szBuffer, m_nBufferSize);
				delete [] 
				m_szBuffer;
			}
			m_szBuffer = szTemp;
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
			m_szBuffer[m_nByteLength++] = 0xF0 | ((nChar >> 18) & 0xFF);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 12) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 6) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 0) & 0x3F);
			m_szBuffer[m_nByteLength] = 0;
			return;
			}

			if (nChar <= 0x3FFFFFF)
			{
			Resize(m_nByteLength+5);
			m_nCharLength++;
			m_szBuffer[m_nByteLength++] = 0xF8 | ((nChar >> 24) & 0xFF);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 18) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 12) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 6) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 0) & 0x3F);
			m_szBuffer[m_nByteLength] = 0;
			return;
			}

			if (nChar <= 0x7FFFFFFF)
			{
			Resize(m_nByteLength+6);
			m_nCharLength++;
			m_szBuffer[m_nByteLength++] = 0xFC | ((nChar >> 30) & 0xFF);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 24) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 18) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 12) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 6) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 0) & 0x3F);
			m_szBuffer[m_nByteLength] = 0;
			return;
			}*/

		Assert::Plz(false);
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

	bool InternalString::GetUtf8Length(const char* szString, int* pCharLength, int* pByteLength)
	{
		const char* p = szString;
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
		Assert::Plz(false);

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
			m_szBuffer[m_nByteLength++] = 0xF0 | ((nChar >> 18) & 0xFF);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 12) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 6) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 0) & 0x3F);
			m_szBuffer[m_nByteLength] = 0;
			return;
			}

			if (nChar <= 0x3FFFFFF)
			{
			Resize(m_nByteLength+5);
			m_nCharLength++;
			m_szBuffer[m_nByteLength++] = 0xF8 | ((nChar >> 24) & 0xFF);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 18) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 12) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 6) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 0) & 0x3F);
			m_szBuffer[m_nByteLength] = 0;
			return;
			}

			if (nChar <= 0x7FFFFFFF)
			{
			Resize(m_nByteLength+6);
			m_nCharLength++;
			m_szBuffer[m_nByteLength++] = 0xFC | ((nChar >> 30) & 0xFF);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 24) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 18) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 12) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 6) & 0x3F);
			m_szBuffer[m_nByteLength++] = 0x80 | ((nChar >> 0) & 0x3F);
			m_szBuffer[m_nByteLength] = 0;
			return;
			}*/

		Assert::Plz(false);
		return 0;
	}
}