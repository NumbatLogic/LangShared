#pragma once

#include "miniz/miniz.h"

namespace NumbatLogic { class gsBlob; }

namespace NumbatLogic
{
	template<typename T> class Vector;
	class InternalString;

	struct ZipEntry
	{
		InternalString* sFileName;
		gsBlob* pBlob;

		ZipEntry(const char* szFileName, gsBlob* pBlob);
		~ZipEntry();
	};
	
	class ZipWriter
	{
		public:
			ZipWriter();
			~ZipWriter();

			bool Save(gsBlob* pBlob);
			bool AddFileFromBlob(const char* szFileName, gsBlob* pBlob);

		private:
			Vector<ZipEntry*>* m_pZipEntryVector;
	};
}  