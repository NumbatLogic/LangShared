#pragma once

#include "miniz/miniz.h"

namespace NumbatLogic { 
	class Blob; 
	class BlobView; 
	template<typename T> class Vector;
	class InternalString;
}

namespace NumbatLogic
{
	struct ZipEntry
	{
		InternalString* sFileName;
		Blob* pBlob;

		ZipEntry(const char* szFileName, Blob* pBlob);
		~ZipEntry();
	};
	
	class ZipWriter
	{
		public:
			ZipWriter();
			~ZipWriter();

			bool SaveBlobView(BlobView* pBlobView);
			bool AddFileFromBlob(const char* szFileName, Blob* pBlob);

		private:
			

			Vector<ZipEntry*>* m_pZipEntryVector;
	};
} 