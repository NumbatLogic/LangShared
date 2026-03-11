#pragma once

#ifndef CLANG_PARSE
	#include "miniz/miniz.h"
#endif

namespace NumbatLogic { class gsBlob; }

namespace NumbatLogic
{
	class InternalString;

	class ZipFileInfo
	{
		public:
			const char* GetFileName();
			int GetSize();

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

			bool Load(gsBlob* pBlob);
			bool Save(gsBlob* pBlob);
			bool LoadFile(const char* szFileName);

			int GetNumFile();
			ZipFileInfo* GetFileInfo(int nIndex);

			bool ExtractFileByIndexToBlob(int nIndex, gsBlob* pOutBlob);
			bool ExtractFileByNameToBlob(const char* szFileName, gsBlob* pOutBlob);
			bool ExtractFileByIndexToString(int nIndex, InternalString* sOut);

		private:
			#ifndef CLANG_PARSE
				void CleanupArchive();

				mz_zip_archive* m_pArchive;
				ZipFileInfo* m_pTempFileInfo;
			#endif
	};
}
