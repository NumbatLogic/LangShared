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

        public static OwnedVector<InternalString> GetRecursiveFileVector(string sPath)
        {
            OwnedVector<InternalString> sFileVector = new OwnedVector<InternalString>();
            Vector<InternalString> sDirectoryVector = new Vector<InternalString>();

            sDirectoryVector.PushBack(new InternalString(sPath));

            while (sDirectoryVector.GetSize() > 0)
            {
                string sDirectory = sDirectoryVector.PopBack().GetExternalString();

                string[] sDirectories = System.IO.Directory.GetDirectories(sDirectory);
                for (int i = 0; i < sDirectories.Length; i++)
                    sDirectoryVector.PushBack(new InternalString(sDirectories[i]));

                string[] sFiles = System.IO.Directory.GetFiles(sDirectory);
                for (int i = 0; i < sFiles.Length; i++)
                {
                    string sFile = sFiles[i];
                    if (sFile.EndsWith(".nll") || sFile.EndsWith(".nll.def"))
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
    }
}