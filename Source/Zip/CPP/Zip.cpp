#include "../../Assert/CPP/Assert.hpp"
#include "../../InternalString/CPP/InternalString.hpp"
#include "../../Blob/CPP/Blob.hpp"
#include "Zip.hpp"

namespace NumbatLogic
{
	ZipFileInfo::ZipFileInfo()
	{
		m_pFileStat = new mz_zip_archive_file_stat();
	}

	ZipFileInfo::~ZipFileInfo()
	{
		delete m_pFileStat;
	}

	const char* ZipFileInfo::GetFileName()
	{
		return m_pFileStat->m_filename;
	}

	int ZipFileInfo::GetSize()
	{
		return (int)m_pFileStat->m_uncomp_size;
	}

	/*unsigned int ZipFileInfo :: GetCrc32()
	   {
		return (unsigned int)m_pFileStat->m_crc32;
	   }*/

	Zip::Zip()
	{
		m_pArchive = NULL;
		m_pTempFileInfo = new ZipFileInfo();
	}

	Zip::~Zip()
	{
		CleanupArchive();
		delete m_pTempFileInfo;
	}

	bool Zip::Load(gsBlob* pBlob)
	{
		if (!pBlob)
			return false;

		CleanupArchive();

		mz_bool bResult;

		m_pArchive = new mz_zip_archive();
		mz_zip_zero_struct(m_pArchive);

		const unsigned char* pData = pBlob->GetData();
		int nOffset = pBlob->GetOffset();
		int nSizeAvailable = pBlob->GetSize() - nOffset;
		if (!pData || nSizeAvailable <= 0)
		{
			CleanupArchive();
			return false;
		}

		bResult = mz_zip_reader_init_mem(
			m_pArchive,
			pData + nOffset,
			(size_t)nSizeAvailable,
			0);

		if (!bResult)
		{
			CleanupArchive();
			return false;
		}

		// Advance blob offset by archive size so callers can chain reads.
		pBlob->SetOffset(nOffset + (int)m_pArchive->m_archive_size);

		return true;
	}

	bool Zip::LoadFile(const char* szFileName)
	{
		gsBlob blob;
		if (!blob.Load(szFileName))
			return false;
		blob.SetOffset(0);
		return Load(&blob);
	}

	bool Zip::Save(gsBlob* pBlob)
	{
		if (!pBlob)
			return false;

		// Create a separate archive for writing
		mz_zip_archive writeArchive;
		mz_zip_zero_struct(&writeArchive);
		
		// Initialize for writing to memory
		if (!mz_zip_writer_init_heap(&writeArchive, 0, 0))
		{
			return false;
		}

		// Finalize the archive
		void* pData = NULL;
		size_t nSize = 0;
		if (!mz_zip_writer_finalize_heap_archive(&writeArchive, &pData, &nSize))
		{
			mz_zip_writer_end(&writeArchive);
			return false;
		}

		// Write the zip data to the gsBlob
		pBlob->Reset();
		pBlob->PackData((unsigned char*)pData, (int)nSize);
		pBlob->SetOffset(0);

		// Clean up
		mz_free(pData);
		mz_zip_writer_end(&writeArchive);

		return true;
	}

	int Zip::GetNumFile()
	{
		return mz_zip_reader_get_num_files(m_pArchive);
	}

	ZipFileInfo* Zip::GetFileInfo(int nIndex)
	{
		if (!mz_zip_reader_file_stat(m_pArchive, nIndex, m_pTempFileInfo->m_pFileStat))
			return NULL;
		return m_pTempFileInfo;
	}

	bool Zip::ExtractFileByIndexToBlob(int nIndex, gsBlob* pOutBlob)
	{
		if (!pOutBlob)
			return false;

		size_t nSize = 0;
		uint8_t* pData = (uint8_t*)mz_zip_reader_extract_to_heap(m_pArchive, nIndex, &nSize, 0);
		if (!pData)
			return false;

		pOutBlob->Reset();
		pOutBlob->PackData((unsigned char*)pData, (int)nSize);
		pOutBlob->SetOffset(0);

		mz_free(pData);
		return true;
	}

	bool Zip::ExtractFileByNameToBlob(const char* szFileName, gsBlob* pOutBlob)
	{
		int nIndex = mz_zip_reader_locate_file(m_pArchive, szFileName, NULL, 0);
		if (nIndex == -1)
			return false;

		return ExtractFileByIndexToBlob(nIndex, pOutBlob);
	}

	bool Zip::ExtractFileByIndexToString(int nIndex, InternalString* sOut)
	{
		size_t nSize = 0;
		uint8_t* pData = (uint8_t*)mz_zip_reader_extract_to_heap(m_pArchive, nIndex, &nSize, 0);
		if (!pData)
			return false;

		sOut->AppendStringData(pData, (int)nSize);

		mz_free(pData);

		return true;
	}

	void Zip::CleanupArchive()
	{
		if (m_pArchive)
		{
			// It is safe to ignore the return value here; CleanupArchive
			// is called in both success and failure paths.
			(void)mz_zip_reader_end(m_pArchive);
			delete m_pArchive;
			m_pArchive = NULL;
		}
	}
}
