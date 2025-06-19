#include "../../Assert/CPP/Assert.hpp"
#include "../../InternalString/CPP/InternalString.hpp"
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
		m_pBlob = NULL;
		m_pArchive = NULL;
		m_pTempFileInfo = new ZipFileInfo();
	}

	Zip::~Zip()
	{
		Cleanup();
		delete m_pTempFileInfo;
	}

	bool Zip::LoadBlobView(BlobView* pBlobView)
	{
		CleanupArchive();

		mz_bool bResult;

		m_pArchive = new mz_zip_archive();
		mz_zip_zero_struct(m_pArchive);

		bResult = mz_zip_reader_init_mem(m_pArchive, pBlobView->GetBlob()->GetData() + pBlobView->GetStart() + pBlobView->GetOffset(), pBlobView->GetSize() - pBlobView->GetOffset(), 0);

		pBlobView->SetOffset(pBlobView->GetOffset() + (int)(m_pArchive->m_archive_size));

		if (!bResult)
		{
			CleanupArchive();
			return false;
		}

		return true;
	}

	bool Zip::LoadFile(const char* szFileName)
	{
		Cleanup();
		m_pBlob = new Blob(false);

		if (!m_pBlob->Load(szFileName) || !LoadBlobView(m_pBlob->GetBlobView()))
		{
			Cleanup();
			return false;
		}

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

	bool Zip::ExtractFileByIndex(int nIndex, BlobView* pOutBlobView)
	{
		// todo: write direct to blob instead of heap

		size_t nSize = 0;
		uint8_t* pData = (uint8_t*)mz_zip_reader_extract_to_heap(m_pArchive, nIndex, &nSize, 0);
		if (!pData)
			return false;

		pOutBlobView->PackData(pData, (int)nSize);
		pOutBlobView->SetOffset(0);

		mz_free(pData);

		return true;
	}

	bool Zip::ExtractFileByName(const char* szFileName, BlobView* pOutBlobView)
	{
		int nIndex = mz_zip_reader_locate_file(m_pArchive, szFileName, NULL, 0);
		if (nIndex == -1)
			return false;

		return ExtractFileByIndex(nIndex, pOutBlobView);
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
			mz_bool bResult;
			bResult = mz_zip_reader_end(m_pArchive);
			Assert::Plz(bResult);
			delete m_pArchive;
			m_pArchive = NULL;
		}
	}

	void Zip::Cleanup()
	{
		CleanupArchive();
		if (m_pBlob)
		{
			delete m_pBlob;
			m_pBlob = NULL;
		}
	}
}
