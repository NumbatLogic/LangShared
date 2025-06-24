#pragma once

#ifndef CLANG_PARSE
	#include "miniz/miniz.h"
#endif

namespace NumbatLogic { class Blob; }
namespace NumbatLogic { class BlobView; }

namespace NumbatLogic
{
	class InternalString;

	class ZipFileInfo
	{
		public:
			const char* GetFileName();
			int GetSize();

		//unsigned int GetCrc32();

		protected:
			#ifndef CLANG_PARSE
				friend class Zip;
				ZipFileInfo();
				~ZipFileInfo();

				mz_zip_archive_file_stat* m_pFileStat;
			#endif
	};

	class Zip
	{
		public:
			Zip();
			~Zip();

			bool LoadBlobView(BlobView* pBlobView);
			bool LoadFile(const char* szFileName);
			bool SaveBlobView(BlobView* pBlobView);

			int GetNumFile();
			ZipFileInfo* GetFileInfo(int nIndex);

			bool ExtractFileByIndex(int nIndex, BlobView* pOutBlobView);
			bool ExtractFileByName(const char* szFileName, BlobView* pOutBlobView);

			bool ExtractFileByIndexToString(int nIndex, InternalString* sOut);

			bool AddFileFromBlobView(const char* szFileName, BlobView* pBlobView);

		private:
			#ifndef CLANG_PARSE
				void CleanupArchive();
				void Cleanup();

				Blob* m_pBlob;
				mz_zip_archive* m_pArchive;
				ZipFileInfo* m_pTempFileInfo;
			#endif
	};
}
