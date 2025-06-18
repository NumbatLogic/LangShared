namespace NumbatLogic
{
    class Zip
    {
        System.IO.Compression.ZipArchive m_pZipArchive = null;

        public Zip()
        {

        }

        public bool LoadBlobView(BlobView pBlobView)
        {
            System.IO.Stream stream = pBlobView.CreateStream();

            try
            {
                m_pZipArchive = new System.IO.Compression.ZipArchive(stream);
            }
            catch
            {
                m_pZipArchive = null;
                return false;
            }
            return true;
        }

        public bool LoadFile(string szFileName)
        {
            Blob pBlob = new Blob(false);
            if (!pBlob.Load(szFileName))
                return false;
            return LoadBlobView(pBlob.GetBlobView());
        }

        public int GetNumFile()
        {
            return m_pZipArchive.Entries.Count;
        }

        public ZipFileInfo GetFileInfo(int nIndex)
        {
            System.IO.Compression.ZipArchiveEntry entry = m_pZipArchive.Entries[nIndex];
            return new ZipFileInfo(entry.FullName, (int)entry.Length);
        }

        public bool ExtractFileByIndex(int nIndex, BlobView pOutBlobView)
        {
            try
            {
                System.IO.Compression.ZipArchiveEntry entry = m_pZipArchive.Entries[nIndex];
                System.IO.Stream stream = entry.Open();

                byte[] buffer = new byte[entry.Length];
                stream.Read(buffer, 0, (int)entry.Length);
                pOutBlobView.PackDataAt(pOutBlobView.GetOffset(), buffer, (int)entry.Length);
            }
            catch
            {
                return false;
            }
            return true;
        }

        public bool ExtractFileByName(string szFileName, BlobView pOutBlobView)
        {
            for (int i = 0; i < m_pZipArchive.Entries.Count; i++)
            {
                if (m_pZipArchive.Entries[i].FullName.Equals(szFileName))
                    return ExtractFileByIndex(i, pOutBlobView);
            }
            return false;
        }

        public bool ExtractFileByIndexToString(int nIndex, InternalString sOut)
        {
            try
            {
                System.IO.Compression.ZipArchiveEntry entry = m_pZipArchive.Entries[nIndex];
                System.IO.Stream stream = entry.Open();

                System.IO.StreamReader reader = new System.IO.StreamReader(stream);
                sOut.Append(reader.ReadToEnd());
            }
            catch
            {
                return false;
            }
            return true;
        }
    }
}
