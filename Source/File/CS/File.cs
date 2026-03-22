namespace NumbatLogic
{
    class File
    {
        public static InternalString GetContents(string sxPath)
        {
            try
            {
                return new InternalString(System.IO.File.ReadAllText(sxPath));
            }
            catch
            {

            }
            return null;
        }

        public static void PutContents(string sPath, string sContents)
        {
            System.IO.File.WriteAllText(sPath, sContents);
        }

        public static OwnedVector<InternalString> GetRecursiveFileVector(string sPath, OwnedVector<InternalString> pAllowedSuffixVector)
        {
            if (!System.IO.Directory.Exists(sPath))
                return null;

            OwnedVector<InternalString> sFileVector = new OwnedVector<InternalString>();
            Vector<InternalString> sDirectoryVector = new Vector<InternalString>();

            sDirectoryVector.PushBack(new InternalString(sPath));

            while (sDirectoryVector.GetSize() > 0)
            {
                string sDirectory = sDirectoryVector.PopBack().GetExternalString();

                if (!System.IO.Directory.Exists(sDirectory))
                    continue;

                string[] sDirectories;
                string[] sFiles;
                try
                {
                    sDirectories = System.IO.Directory.GetDirectories(sDirectory);
                    sFiles = System.IO.Directory.GetFiles(sDirectory);
                }
                catch
                {
                    continue;
                }

                for (int i = 0; i < sDirectories.Length; i++)
                    sDirectoryVector.PushBack(new InternalString(sDirectories[i]));

                for (int i = 0; i < sFiles.Length; i++)
                {
                    string sFile = sFiles[i];

                    bool include = false;
                    if (pAllowedSuffixVector == null || pAllowedSuffixVector.GetSize() == 0)
                    {
                        include = true;
                    }
                    else
                    {
                        for (int j = 0; j < pAllowedSuffixVector.GetSize(); j++)
                        {
                            string suffix = pAllowedSuffixVector.Get(j).GetExternalString();
                            if (sFile.EndsWith(suffix))
                            {
                                include = true;
                                break;
                            }
                        }
                    }

                    if (include)
                        sFileVector.PushBack(new InternalString(sFile));
                }
            }

            return sFileVector;
        }

        public static InternalString GetFileDirectory(string sPath)
        {
            return new InternalString(System.IO.Path.GetDirectoryName(sPath));
        }

        public static void CreateDirectory(string sPath)
        {
            System.IO.Directory.CreateDirectory(sPath);
        }

        public static InternalString GetFullPath(string sPath)
        {
            try
            {
                return new InternalString(System.IO.Path.GetFullPath(sPath));
            }
            catch
            {
            }

            return new InternalString(sPath);
        }
    }
}