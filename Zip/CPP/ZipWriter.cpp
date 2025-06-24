#include "ZipWriter.hpp"
#include "../../Assert/CPP/Assert.hpp"
#include "../../Blob/CPP/Blob.hpp"
#include "../../InternalString/CPP/InternalString.hpp"
#include "../../Vector/CPP/Vector.hpp"

namespace NumbatLogic
{
    ZipEntry::ZipEntry(const char* szFileName, Blob* pBlob)
	{
		sFileName = new InternalString(szFileName);
		this->pBlob = pBlob;
	}

	ZipEntry::~ZipEntry()
	{
		delete sFileName;
		delete pBlob;
	}

	ZipWriter::ZipWriter()
	{
		m_pZipEntryVector = new Vector<ZipEntry*>();
	}

	ZipWriter::~ZipWriter()
	{
		while (m_pZipEntryVector->GetSize() > 0)
		{
			ZipEntry* pEntry = m_pZipEntryVector->PopBack();
			delete pEntry;
		}
		delete m_pZipEntryVector;
	}

	bool ZipWriter::AddFileFromBlob(const char* szFileName, Blob* pBlob)
	{
		try
		{
			ZipEntry* pEntry = new ZipEntry(szFileName, pBlob);
			m_pZipEntryVector->PushBack(pEntry);
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool ZipWriter::SaveBlobView(BlobView* pBlobView)
	{
		try
		{
			// Create a zip archive for writing to memory
			mz_zip_archive zipArchive;
			mz_zip_zero_struct(&zipArchive);
			
			// Initialize for writing to memory
			if (!mz_zip_writer_init_heap(&zipArchive, 0, 0))
			{
				return false;
			}

			// Add all files to the zip archive
			for (int i = 0; i < m_pZipEntryVector->GetSize(); i++)
			{
				ZipEntry* pEntry = m_pZipEntryVector->Get(i);
				BlobView* pEntryBlobView = pEntry->pBlob->GetBlobView();
				
				pEntryBlobView->SetOffset(0);
				
				if (!mz_zip_writer_add_mem(&zipArchive, 
					pEntry->sFileName->GetExternalString(),
					pEntry->pBlob->GetData() + pEntryBlobView->GetStart() + pEntryBlobView->GetOffset(),
					pEntryBlobView->GetSize() - pEntryBlobView->GetOffset(),
					MZ_DEFAULT_COMPRESSION))
				{
					mz_zip_writer_end(&zipArchive);
					return false;
				}
			}

			// Finalize the archive
			void* pData = NULL;
			size_t nSize = 0;
			if (!mz_zip_writer_finalize_heap_archive(&zipArchive, &pData, &nSize))
			{
				mz_zip_writer_end(&zipArchive);
				return false;
			}

			// Write to blob view
			pBlobView->PackDataAt(pBlobView->GetOffset(), (unsigned char*)pData, (int)nSize);

			// Clean up
			mz_free(pData);
			mz_zip_writer_end(&zipArchive);
			
			return true;
		}
		catch (...)
		{
			return false;
		}
	}
} 