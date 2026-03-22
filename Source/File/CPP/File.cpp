#include "File.hpp"
#include "../../Blob/CPP/Blob.hpp"
#include "../../InternalString/CPP/InternalString.hpp"
#include "../../Vector/CPP/Vector.hpp"
#include "../../../Transpiled/Vector/OwnedVector.hpp"

#include "tinydir/tinydir.h"

#include <stdio.h>
#include <cstring>
#include <limits.h>
#include <stdlib.h>
#include <libgen.h>

namespace NumbatLogic
{
	InternalString* File::GetContents(const char* sPath)
	{
		gsBlob* pBlob = new gsBlob();
		if (!pBlob->Load(sPath))
		{
			delete pBlob;
			return NULL;
		}

		pBlob->SetOffset(pBlob->GetSize());
		pBlob->PackUint8(0);

		InternalString* sTemp = new InternalString((const char*)pBlob->GetData());
		delete pBlob;

		return sTemp;
	}

	void File::PutContents(const char* sxPath, const char* sxContents)
	{
		gsBlob* pBlob = new gsBlob();
		pBlob->PackData((unsigned char*)sxContents, (int)strlen(sxContents));
		pBlob->Save(sxPath);
		delete pBlob;
	}

	OwnedVector<InternalString*>* File::GetRecursiveFileVector(const char* sPath, OwnedVector<InternalString*>* pAllowedSuffixVector)
	{
		tinydir_dir initialDir;
		if (tinydir_open_sorted(&initialDir, sPath) == -1)
		{
			return NULL;
		}
		tinydir_close(&initialDir);

		OwnedVector<InternalString*>* sFileVector = new OwnedVector<InternalString*>();
		Vector<InternalString*>* sDirectoryVector = new Vector<InternalString*>();

		sDirectoryVector->PushBack(new InternalString(sPath));

		tinydir_dir dir;
		while (sDirectoryVector->GetSize() > 0)
		{
			int i;
			InternalString* sDirectory = sDirectoryVector->PopBack();

			if (tinydir_open_sorted(&dir, sDirectory->GetExternalString()) == -1)
			{
				delete sDirectory;
				continue;
			}

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
					bool bInclude = false;

					if (pAllowedSuffixVector == NULL || pAllowedSuffixVector->GetSize() == 0)
					{
						bInclude = true;
					}
					else
					{
						for (int j = 0; j < pAllowedSuffixVector->GetSize(); ++j)
						{
							InternalString* sSuffix = pAllowedSuffixVector->Get(j);
							if (sFullPath->EndsWith(sSuffix->GetExternalString()))
							{
								bInclude = true;
								break;
							}
						}
					}

					if (bInclude)
					{
						sFileVector->PushBack(sFullPath);
						continue;
					}
				}
				delete sFullPath;
			}
			tinydir_close(&dir);
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
			{
				free(sxTemp);
				return NULL;
			}

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

	InternalString* File::GetFullPath(const char* sxPath)
	{
		#ifndef _WIN32
			char* sxResolved = realpath(sxPath, NULL);
			if (!sxResolved)
			{
				return new InternalString(sxPath);
			}

			InternalString* sOut = new InternalString(sxResolved);
			free(sxResolved);
			return sOut;
		#else
			return new InternalString(sxPath);
		#endif
	}
}