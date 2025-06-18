#include "File.hpp"
#include "../../Blob/CPP/Blob.hpp"
#include "../../InternalString/CPP/InternalString.hpp"
#include "../../Vector/CPP/Vector.hpp"
#include "../../../Lang/Transpiled/LangShared/Vector/OwnedVector.hpp"

#include "tinydir/tinydir.h"

#include <stdio.h>
#include <cstring>

namespace NumbatLogic
{
	InternalString* File::GetContents(const char* sPath)
	{
		Blob* pBlob = new Blob(true);
		if (!pBlob->Load(sPath))
		{
			delete pBlob;
			return NULL;
		}

		BlobView* pBlobView = pBlob->GetBlobView();
		pBlobView->SetOffset(pBlobView->GetSize());
		pBlobView->PackUint8(0);

		InternalString* sTemp = new InternalString((const char*)pBlob->GetData());
		delete pBlob;

		return sTemp;
	}

	void File::PutContents(const char* sxPath, const char* sxContents)
	{
		Blob* pBlob = new Blob(true);
		BlobView* pBlobView = pBlob->GetBlobView();
		pBlobView->PackData((unsigned char*)sxContents, (int)strlen(sxContents));
		pBlob->Save(sxPath);
		delete pBlob;
	}

	OwnedVector<InternalString*>* File::GetRecursiveFileVector(const char* sPath)
	{
		OwnedVector<InternalString*>* sFileVector = new OwnedVector<InternalString*>();
		Vector<InternalString*>* sDirectoryVector = new Vector<InternalString*>();

		sDirectoryVector->PushBack(new InternalString(sPath));

		tinydir_dir dir;
		while (sDirectoryVector->GetSize() > 0)
		{
			int i;
			InternalString* sDirectory = sDirectoryVector->PopBack();

			tinydir_open_sorted(&dir, sDirectory->GetExternalString());
			for (i = 0; i < (int)dir.n_files; i++)
			{
				tinydir_file file;
				tinydir_readfile_n(&dir, &file, i);

				InternalString* sFullPath = new InternalString(sDirectory->GetExternalString());
				sFullPath->AppendString("/");
				sFullPath->AppendString(file.name);

				if (file.is_dir)
				{
					if (strcmp(file.name, ".") != 0 && strcmp(file.name, "..") != 0)
					{
						sDirectoryVector->PushBack(sFullPath);
						continue;
					}
				}
				else
				{
					if (sFullPath->EndsWith(".nll") || sFullPath->EndsWith(".nll.def"))
					{
						sFileVector->PushBack(sFullPath);
						continue;
					}
				}
				delete sFullPath;
			}
			delete sDirectory;
		}
		delete sDirectoryVector;
		return sFileVector;
	}

	#ifndef _WIN32
		InternalString* File::GetFileDirectory(const char* sxPath)
		{
			char* sxTemp = strdup(sxPath);
			char* sxDirname = dirname(sxTemp);

			if (!sxDirname || strlen(sxDirname) <= 2)
				return NULL;

			InternalString* sDirname = new InternalString(sxDirname);
			free(sxTemp);
			return sDirname;
		}

		void File::CreateDirectory(const char* sxPath)
		{
			InternalString* sDirname = File::GetFileDirectory(sxPath);
			if (sDirname)
			{
				CreateDirectory(sDirname->GetExternalString());
				delete sDirname;
			}
			mkdir(sxPath, 0700);
		}
	#endif
}