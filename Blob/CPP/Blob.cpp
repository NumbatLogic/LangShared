#include "Blob.hpp"
#include "../../Assert/CPP/Assert.hpp"
#include "../../InternalString/CPP/InternalString.hpp"

#ifdef _WIN32
	#include <string>

	#include <Windows.h>
#endif

#include <cstdlib>

#include <stdio.h>
#include <string.h>

namespace NumbatLogic
{
	Blob::Blob(bool bAutoResize)
	{
		m_nBufferSize = DEFAULT_SIZE;
		m_pBuffer = (unsigned char*)malloc(m_nBufferSize);
		memset(m_pBuffer, 0, m_nBufferSize);
		m_nSize = 0;
		m_bAutoResize = bAutoResize;

		m_pBlobView = new BlobView(this, 0, 0);
	}

	Blob::~Blob()
	{
		free(m_pBuffer);
		delete m_pBlobView;
	}

	bool Blob::Load(const char* szFileName)
	{
		#ifdef _WIN32
			int size_needed = MultiByteToWideChar(CP_UTF8, 0, szFileName, (int)strlen(szFileName), NULL, 0);
			std::wstring wsFileName(size_needed, 0);
			MultiByteToWideChar(CP_UTF8, 0, szFileName, (int)strlen(szFileName), &wsFileName[0], size_needed);
			FILE* pFile = _wfopen(wsFileName.c_str(), L"rb");
		#else
			FILE* pFile = fopen(szFileName, "rb");
		#endif

		if (pFile != NULL)
		{
			fseek(pFile, 0, SEEK_END );
			unsigned int nFileSize = ftell(pFile);
			rewind(pFile);

			if (nFileSize > 0)
			{
				free(m_pBuffer);

				m_nBufferSize = nFileSize;
				m_pBuffer = (unsigned char*)malloc(m_nBufferSize);
				m_nSize = 0;

				if (fread(m_pBuffer, m_nBufferSize, 1, pFile) == 1)
				{
					m_nSize = m_nBufferSize;
					fclose(pFile);
					m_pBlobView->SetEnd(m_nSize);
					return true;
				}
			}

			fclose(pFile);
		}
		return false;
	}

	bool Blob::Save(const char* szFileName)
	{
		#ifdef _WIN32
			int size_needed = MultiByteToWideChar(CP_UTF8, 0, szFileName, (int)strlen(szFileName), NULL, 0);
			std::wstring wsFileName(size_needed, 0);
			MultiByteToWideChar(CP_UTF8, 0, szFileName, (int)strlen(szFileName), &wsFileName[0], size_needed);
			FILE* pFile = _wfopen(wsFileName.c_str(), L"wb");
		#else
			FILE* pFile = fopen(szFileName, "wb");
		#endif

		if (pFile != NULL)
		{
			fwrite(m_pBuffer, 1, m_nSize, pFile);
			fclose(pFile);
			return true;
		}
		return false;
	}

	void Blob::Resize(int nSize, bool bAutoResize)
	{
		unsigned char* pOldBuffer = m_pBuffer;

		if (bAutoResize)
			Assert::Plz(m_bAutoResize);

		if (nSize > m_nSize)
		{
			while (nSize > m_nBufferSize)
			{
				// if we are over 100mb, just use the target size, otherwise we'll blow out the RAMs
				if (nSize > 1024 * 1024 * 100)
					m_nBufferSize = nSize;
				else
					m_nBufferSize <<= 1;
			}

			m_pBuffer = (unsigned char*)malloc(m_nBufferSize);
			memcpy(m_pBuffer, pOldBuffer, m_nSize);
			memset(m_pBuffer + m_nSize, 0, m_nBufferSize - m_nSize);
			free(pOldBuffer);
		}
		m_nSize = nSize;

		m_pBlobView->SetEnd(nSize);
	}

	int Blob::GetSize()
	{
		return m_nSize;
	}

	unsigned char* Blob::GetData()
	{
		return m_pBuffer;
	}

	unsigned int Blob::GetMsoCrc32()
	{
		// https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-oshared/324014d1-39aa-4038-bbf4-f3781732f767
		// https://github.com/chakannom/algorithm/blob/master/MsoCRC32Compute/MsoCRC32Compute/MsoCRC32Compute.cpp
		unsigned int nCache[256];
		{
			unsigned int i;
			for (i = 0; i < 256; i++)
			{
				unsigned int nBit;
				unsigned int nValue = i << 24;
				for (nBit = 0; nBit < 8; nBit++)
				{
					if (nValue & (0x1 << 31))
						nValue = (nValue << 1) ^ 0xAF;
					else
						nValue = nValue << 1;
				}

				nCache[i] = nValue & 0xFFFF;
			}
		}

		unsigned int nCrcValue = 0;
		{
			int i;
			for (i = 0; i < m_nSize; i++)
			{
				unsigned int nIndex = nCrcValue;
				nIndex = nIndex >> 24;
				nIndex = nIndex ^ m_pBuffer[i];
				nCrcValue = nCrcValue << 8;
				nCrcValue = nCrcValue ^ nCache[nIndex];
				//printf("%x %lX \n", m_pBuffer[i], nCrcValue);
			}
		}

		return nCrcValue;
	}

	void Blob::PackData(unsigned char* pData, int nOffset, int nSize)
	{
		Assert::Plz(nOffset + nSize <= m_nSize);
		memcpy(m_pBuffer + nOffset, pData, nSize);
	}

	void Blob::UnpackData(unsigned char* pData, int nOffset, int nSize)
	{
		Assert::Plz(nOffset + nSize <= m_nSize);
		memcpy(pData, m_pBuffer + nOffset, nSize);
	}

	BlobView* Blob::GetBlobView()
	{
		return m_pBlobView;
	}

	bool Blob::Equal(Blob* pOther)
	{
		if (m_nSize != pOther->m_nSize)
			return false;
		return memcmp(m_pBuffer, pOther->m_pBuffer, m_nSize) == 0;
	}

	Blob* Blob::Clone()
	{
		Blob* pClone = new Blob(m_bAutoResize);
		pClone->m_nBufferSize = m_nBufferSize;
		pClone->m_nSize = m_nSize;
		
		// Reallocate buffer to match original size
		free(pClone->m_pBuffer);
		pClone->m_pBuffer = (unsigned char*)malloc(m_nBufferSize);
		
		// Copy all data from original buffer
		memcpy(pClone->m_pBuffer, m_pBuffer, m_nBufferSize);
		
		// Update the blob view to reflect the new size
		pClone->m_pBlobView->SetEnd(m_nSize);
		
		return pClone;
	}

	// Blob View
	BlobView::BlobView(Blob* pBlob, int nStart, int nEnd)
	{
		Assert::Plz(nStart >= 0);
		Assert::Plz(nStart <= nEnd);
		Assert::Plz(nEnd <= pBlob->GetSize());

		m_pBlob = pBlob;
		m_nStart = nStart;
		m_nEnd = nEnd;
		m_nOffset = 0;
	}

	BlobView::~BlobView()
	{
	}

	#define WIDTH  (8 * sizeof(unsigned char))
	#define TOPBIT (1 << (WIDTH - 1))
	#define POLYNOMIAL 0xD8		/* 11011 followed by 0's */

	unsigned char BlobView::GetChecksum()
	{
		unsigned char remainder = 0;
		unsigned int nEnd = m_nEnd;
		if (nEnd == 0)
			nEnd = m_pBlob->m_nSize;

		for (unsigned int byte = m_nStart; byte < nEnd; byte++)
		{
			remainder ^= (m_pBlob->m_pBuffer[byte] << (WIDTH - 8));
			for (unsigned int bit = 8; bit > 0; --bit)
			{
				if (remainder & TOPBIT)
				{
					remainder = (remainder << 1) ^ POLYNOMIAL;
				}
				else
				{
					remainder = (remainder << 1);
				}
			}
		}
		return (remainder);
	}

	void BlobView::PackBool(bool b)
	{
		PackUint8(b ? 1 : 0);
	}

	// todo: this is probably wrong on different endians and stuff?
	// casting values weirdly with 64bit ints...
	// maybe we should shift and & 0xFF etc
	void BlobView::PackUint8(unsigned char n)
	{
		PackData(&n, 1);
	}

	void BlobView::PackUint16(unsigned short n)
	{
		PackData((unsigned char*)&n, 2);
	}

	void BlobView::PackUint32(unsigned int n)
	{
		PackData((unsigned char*)&n, 4);
	}

	void BlobView::PackInt8(signed char n)
	{
		PackData((unsigned char*)&n, 1);
	}

	void BlobView::PackInt16(signed short n)
	{
		PackData((unsigned char*)&n, 2);
	}

	void BlobView::PackInt32(signed int n)
	{
		PackData((unsigned char*)&n, 4);
	}

	void BlobView::PackDouble(double n)
	{
		PackData((unsigned char*)&n, 8);
	}

	void BlobView::PackInternalString(InternalString* sString)
	{
		PackInt32(sString->GetByteLength());
		PackData((unsigned char*)sString->GetExternalString(), sString->GetLength());	
	}

	void BlobView::PackBlob(Blob* pBlob)
	{
		PackInt32(pBlob->m_nSize);
		PackData(pBlob->m_pBuffer, pBlob->m_nSize);
	}

	bool BlobView::UnpackBool()
	{
		unsigned char n = UnpackUint8();
		return n == 1;
	}

	unsigned char BlobView::UnpackUint8()
	{
		unsigned char n = 0;
		UnpackData(&n, 1);
		return n;
	}

	unsigned short BlobView::UnpackUint16()
	{
		unsigned short n = 0;
		UnpackData((unsigned char*)&n, 2);
		return n;
	}

	unsigned int BlobView::UnpackUint32()
	{
		unsigned int n;
		UnpackData((unsigned char*)&n, 4);
		return n;
	}

	signed char BlobView::UnpackInt8()
	{
		signed char n = 0;
		UnpackData((unsigned char*)&n, 1);
		return n;
	}

	signed short BlobView::UnpackInt16()
	{
		signed short n = 0;
		UnpackData((unsigned char*)&n, 2);
		return n;
	}

	signed int BlobView::UnpackInt32()
	{
		signed int n = 0;
		UnpackData((unsigned char*)&n, 4);
		return n;
	}

	double BlobView::UnpackDouble()
	{
		double n = 0;
		UnpackData((unsigned char*)&n, 8);
		return n;
	}

	bool BlobView::UnpackInternalString(InternalString* sString)
	{
		signed int nByteLength = 0;
		UnpackData((unsigned char*)&nByteLength, 4);

		if (nByteLength == 0)
		{
			sString->Set("");
			return true;
		}

		if (nByteLength > 0 && nByteLength < 1024)
		{
			unsigned char* pBuffer = (unsigned char*)malloc(nByteLength+1);
			UnpackData(pBuffer, nByteLength);
			pBuffer[nByteLength] = 0;
			sString->Set((char*)pBuffer);
			return true;
		}

		return false;
	}

	bool BlobView::UnpackBlob(Blob* pBlob)
	{
		signed int nSize = UnpackInt32();
		pBlob->Resize(nSize, true);

		if (nSize == 0)
			return true;

		UnpackData(pBlob->m_pBuffer, nSize);
		return true;
	}

	signed int BlobView::UnpackInt32At(int nOffset)
	{
		signed int n = 0;
		UnpackDataAt(nOffset, (unsigned char*)&n, 4);
		return n;
	}

	int BlobView::GetStart()
	{
		return m_nStart;
	}

	int BlobView::GetEnd()
	{
		return m_nEnd;
	}

	void BlobView::SetEnd(int nEnd)
	{
		if (nEnd > 0)
		{
			Assert::Plz(nEnd > m_nOffset);
			Assert::Plz(nEnd >= m_nStart);
		}

		m_nEnd = nEnd;
	}

	int BlobView::GetSize()
	{
		int nEnd = m_nEnd;
		if (nEnd == 0)
			nEnd = m_pBlob->m_nSize;
		return nEnd - m_nStart;
	}

	int BlobView::GetOffset()
	{
		return m_nOffset;
	}

	void BlobView::SetOffset(int nOffset)
	{
		// todo: cap?
		m_nOffset = nOffset;
	}

	void BlobView::Pack(BlobView* pBlobView, int nSize)
	{
		PackAt(m_nOffset, pBlobView, nSize);
		m_nOffset += nSize;
	}

	void BlobView::PackAt(int nOffset, BlobView* pBlobView, int nSize)
	{
		unsigned char* pData = new unsigned char[nSize];
		pBlobView->UnpackData(pData, nSize);
		PackDataAt(nOffset, pData, nSize);
		delete [] pData;
	}

	void BlobView::Unpack(BlobView* pBlobView, int nSize)
	{
		UnpackAt(m_nOffset, pBlobView, nSize);
		m_nOffset += nSize;
	}

	void BlobView::UnpackAt(int nOffset, BlobView* pBlobView, int nSize)
	{
		unsigned char* pData = new unsigned char[nSize];
		UnpackDataAt(nOffset, pData, nSize);

		pBlobView->PackData(pData, nSize);
		delete [] pData;
	}

	void BlobView::PackData(unsigned char* pData, int nSize)
	{
		PackDataAt(m_nOffset, pData, nSize);
		m_nOffset += nSize;
	}

	void BlobView::UnpackData(unsigned char* pData, int nSize)
	{
		UnpackDataAt(m_nOffset, pData, nSize);
		m_nOffset += nSize;
	}

	// Single Blob View

	Blob* BlobView::GetBlob()
	{
		return m_pBlob;
	}

	void BlobView::PackDataAt(int nOffset, unsigned char* pData, int nSize)
	{
		int nBlobOffset = m_nStart + nOffset;
		if (this == m_pBlob->GetBlobView())
		{
			if (nBlobOffset + nSize > m_pBlob->GetSize())
				m_pBlob->Resize(nBlobOffset + nSize, true);
		}
		else
		{
			Assert::Plz(nBlobOffset + nSize <= m_nEnd);
		}
		m_pBlob->PackData(pData, nBlobOffset, nSize);
	}

	void BlobView::UnpackDataAt(int nOffset, unsigned char* pData, int nSize)
	{
		int nBlobOffset = m_nStart + nOffset;
		int nEnd = m_nEnd;
		if (nEnd == 0)
			nEnd = m_pBlob->GetSize();
		Assert::Plz(nBlobOffset + nSize <= nEnd);
		m_pBlob->UnpackData(pData, nBlobOffset, nSize);
	}
}
