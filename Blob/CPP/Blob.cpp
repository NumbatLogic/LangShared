#include "Blob.hpp"
#include "../../Assert/CPP/Assert.hpp"
#include "../../ExternalString/CPP/ExternalString.hpp"
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
	




	/// --------------------
	gsBlob::gsBlob()
	{
		m_nBufferSize = DEFAULT_SIZE;
		m_pBuffer = (unsigned char*)malloc(m_nBufferSize);
		memset(m_pBuffer, 0, m_nBufferSize);
		m_nSize = 0;
		m_nOffset = 0;
	}

	gsBlob::~gsBlob()
	{
		free(m_pBuffer);
	}

	bool gsBlob::Load(const char* szFileName)
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
				m_nOffset = 0;

				if (fread(m_pBuffer, m_nBufferSize, 1, pFile) == 1)
				{
					m_nSize = m_nBufferSize;
					fclose(pFile);
					return true;
				}
			}

			fclose(pFile);
		}
		return false;
	}

	bool gsBlob::Save(const char* szFileName)
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

	bool gsBlob::IsEqual(gsBlob* pOther)
	{
		if (m_nSize != pOther->m_nSize)
			return false;
		return memcmp(m_pBuffer, pOther->m_pBuffer, m_nSize) == 0;
	}
	
	#define _WIDTH  (8 * sizeof(unsigned char))
	#define _TOPBIT (1 << (_WIDTH - 1))
	#define _POLYNOMIAL 0xD8		/* 11011 followed by 0's */

	unsigned char gsBlob::GetChecksum()
	{
		unsigned char remainder = 0;
		for (int byte = 0; byte < m_nSize; byte++)
		{
			remainder ^= (m_pBuffer[byte] << (_WIDTH - 8));
			for (unsigned int bit = 8; bit > 0; --bit)
			{
				if (remainder & _TOPBIT)
				{
					remainder = (remainder << 1) ^ _POLYNOMIAL;
				}
				else
				{
					remainder = (remainder << 1);
				}
			}
		}
		return (remainder);
	}
	
	gsBlob* gsBlob::Clone()
	{
		gsBlob* pClone = new gsBlob();
		pClone->m_nBufferSize = m_nBufferSize;
		pClone->m_nSize = m_nSize;
		
		// Reallocate buffer to match original size
		free(pClone->m_pBuffer);
		pClone->m_pBuffer = (unsigned char*)malloc(m_nBufferSize);
		
		// Copy all data from original buffer
		memcpy(pClone->m_pBuffer, m_pBuffer, m_nBufferSize);
		
		return pClone;
	}

	int gsBlob::GetSize()
	{
		return m_nSize;
	}

	int gsBlob::GetOffset()
	{
		return m_nOffset;
	}

	void gsBlob::SetOffset(int nOffset)
	{
		Assert::Plz(nOffset <= m_nSize);
		m_nOffset = nOffset;
	}

	void gsBlob::Reset()
	{
		m_nSize = 0;
		m_nOffset = 0;
	}

	// 64 bit considerations????

	// todo: this is probably wrong on different endians and stuff?
	// casting values weirdly with 64bit ints...
	// maybe we should shift and & 0xFF etc

	// Pack
	void gsBlob::PackBool(bool val) { PackUint8(val ? 1 : 0); }
	
	void gsBlob::PackUint8(unsigned char val) { PackData(&val, 1); }
	void gsBlob::PackUint16(unsigned short val) { PackData((unsigned char*)&val, 2); }
	void gsBlob::PackUint32(unsigned int val) { PackData((unsigned char*)&val, 4); }

	void gsBlob::PackInt8(signed char val) { PackData((unsigned char*)&val, 1); }
	void gsBlob::PackInt16(signed short val) { PackData((unsigned char*)&val, 2); }
	void gsBlob::PackInt32(signed int val) { PackData((unsigned char*)&val, 4); }

	void gsBlob::PackDouble(double val) { PackData((unsigned char*)&val, 8); }

	void gsBlob::PackExternalString(const char* sxString)
	{
		int nByteLength = ExternalString::GetByteLength(sxString);
		PackInt32(nByteLength);
		PackData((unsigned char*)sxString, nByteLength);	
	}

	void gsBlob::PackInternalString(InternalString* sString)
	{
		unsigned short nByteLength = (unsigned short)sString->GetByteLength();
		PackUint16(nByteLength);
		PackData((unsigned char*)sString->GetExternalString(), nByteLength);
	}

	void gsBlob::PackBlob(gsBlob* pBlob)
	{
		PackUint16((unsigned short)pBlob->m_nSize);
		PackData(pBlob->m_pBuffer, pBlob->m_nSize);
	}


	// Unpack
	bool gsBlob::UnpackBool(bool& val)
	{
		unsigned char n;
		if (!UnpackUint8(n))
			return false;
		val = n == 1;
		return true;
	}

	bool gsBlob::UnpackUint8(unsigned char& val) { return UnpackData((unsigned char*)&val, sizeof(val)); }
	bool gsBlob::UnpackUint16(unsigned short& val) { return UnpackData((unsigned char*)&val, sizeof(val)); }
	bool gsBlob::UnpackUint32(unsigned int& val) { return UnpackData((unsigned char*)&val, sizeof(val)); }

	bool gsBlob::UnpackInt8(signed char& val) { return UnpackData((unsigned char*)&val, sizeof(val)); }
	bool gsBlob::UnpackInt16(signed short& val) { return UnpackData((unsigned char*)&val, sizeof(val)); }
	bool gsBlob::UnpackInt32(signed int& val) { return UnpackData((unsigned char*)&val, sizeof(val)); }

	bool gsBlob::UnpackDouble(double& val) { return UnpackData((unsigned char*)&val, sizeof(val)); }

	bool gsBlob::UnpackInternalString(InternalString* sString)
	{
		unsigned short nByteLength = 0;
		if (!UnpackUint16(nByteLength))
			return false;
		
		if (nByteLength == 0)
		{
			sString->Set("");
			return true;
		}

		if (nByteLength > 0 && nByteLength < 1024*5)
		{
			unsigned char* pBuffer = (unsigned char*)malloc(nByteLength+1);
			if (!UnpackData(pBuffer, nByteLength))
			{
				free(pBuffer);
				return false;
			}
			pBuffer[nByteLength] = 0;
			sString->Set((char*)pBuffer);
			free(pBuffer);
			return true;
		}

		return false;
	}

	bool gsBlob::UnpackBlob(gsBlob* pBlob)
	{
		unsigned short nSize = 0;
		if (!UnpackUint16(nSize))
			return false;

		pBlob->Resize(nSize);

		if (nSize == 0)
			return true;

		return UnpackData(pBlob->m_pBuffer, nSize);
	}

	bool gsBlob::Resize(int nSize)
	{
		if (nSize > m_nBufferSize)
		{
			while (nSize > m_nBufferSize)
			{
				// if we are over 100mb, just use the target size, otherwise we'll blow out the RAMs
				if (nSize > 1024 * 1024 * 100)
					m_nBufferSize = nSize;
				else
					m_nBufferSize <<= 1;
			}

			unsigned char* pOldBuffer = m_pBuffer;
			m_pBuffer = (unsigned char*)malloc(m_nBufferSize);
			memcpy(m_pBuffer, pOldBuffer, m_nSize);
			memset(m_pBuffer + m_nSize, 0, m_nBufferSize - m_nSize);
			free(pOldBuffer);
		}
		m_nSize = nSize;
		return true;
	}

	bool gsBlob::PackData(const unsigned char* pData, int nSize)
	{
		if (m_nOffset + nSize > m_nSize)
			if (!Resize(m_nOffset + nSize))
				return false;
		memcpy(m_pBuffer + m_nOffset, pData, nSize);
		m_nOffset += nSize;
		return true;
	}

	bool gsBlob::UnpackData(unsigned char* pData, int nSize)
	{
		if (m_nOffset + nSize > m_nSize)
			return false;
		memcpy(pData, m_pBuffer + m_nOffset, nSize);
		m_nOffset += nSize;
		return true;
	}

	unsigned char* gsBlob::GetData()
	{
		return m_pBuffer;
	}
}
