#pragma once

namespace NumbatLogic
{
	template <class T>
	class OwnedVector;

	class InternalString;

	class File
	{
		public: static InternalString* GetContents(const char* sPath);
		public: static void PutContents(const char* sxPath, const char* sxContents);
		public: static OwnedVector<InternalString*>* GetRecursiveFileVector(const char* sPath);

		public: static InternalString* GetFileDirectory(const char* sxPath);
		public: static void CreateDirectory(const char* sxPath);
	};
}