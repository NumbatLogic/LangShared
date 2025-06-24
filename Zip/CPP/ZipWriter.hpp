#pragma once

#include "miniz/miniz.h"
#include "../../InternalString/CPP/InternalString.hpp"
#include "../../Vector/CPP/Vector.hpp"

namespace NumbatLogic { class Blob; class BlobView; }

namespace NumbatLogic
{
	class ZipWriter
	{
		public:
			ZipWriter();
			~ZipWriter();

			bool SaveBlobView(BlobView* pBlobView);
			bool AddFileFromBlobView(const char* szFileName, BlobView* pBlobView);

		private:
			struct ZipEntry
			{
				InternalString* sFileName;
				Blob* pBlob;

				ZipEntry(const char* szFileName, Blob* pBlob)
				{
					sFileName = new InternalString(szFileName);
					this->pBlob = pBlob;
				}

				~ZipEntry()
				{
					delete sFileName;
				}
			};

			Vector<ZipEntry*>* m_lstEntries;
	};
} 