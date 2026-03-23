namespace NumbatLogic
{
    public class Zip
    {
        System.IO.Compression.ZipArchive m_pZipArchive = null;
        System.IO.MemoryStream m_pStream = null;

        public Zip()
        {

        }

        public bool Load(gsBlob pBlob)
        {
            int nOffset = pBlob.GetOffset();
            int nSize = pBlob.GetSize() - nOffset;
            if (nSize <= 0)
                return false;

            // Clean up any previous archive/stream
            if (m_pZipArchive != null)
            {
                m_pZipArchive.Dispose();
                m_pZipArchive = null;
            }
            if (m_pStream != null)
            {
                m_pStream.Dispose();
                m_pStream = null;
            }

            try
            {
                // Keep the backing stream alive as long as the archive is in use
                m_pStream = new System.IO.MemoryStream(pBlob.__pBuffer, nOffset, nSize, false);
                m_pZipArchive = new System.IO.Compression.ZipArchive(m_pStream, System.IO.Compression.ZipArchiveMode.Read, false);
            }
            catch
            {
                if (m_pZipArchive != null)
                {
                    m_pZipArchive.Dispose();
                    m_pZipArchive = null;
                }
                if (m_pStream != null)
                {
                    m_pStream.Dispose();
                    m_pStream = null;
                }
                return false;
            }

            // For symmetry with C++, we leave blob offset unchanged in C#.
            return true;
        }

        public bool LoadFile(string szFileName)
        {
            gsBlob blob = new gsBlob();
            if (!blob.Load(szFileName))
                return false;
            blob.SetOffset(0);
            return Load(blob);
        }

        public bool Save(gsBlob pBlob)
        {
            try
            {
                // Create a new zip archive in memory
                using (System.IO.MemoryStream memoryStream = new System.IO.MemoryStream())
                {
                    using (System.IO.Compression.ZipArchive zipArchive = new System.IO.Compression.ZipArchive(memoryStream, System.IO.Compression.ZipArchiveMode.Create))
                    {
                        // Empty zip archive - no files added
                    }

                    // Get the zip data
                    byte[] zipData = memoryStream.ToArray();
                    
                    // Write to gsBlob
                    pBlob.Reset();
                    pBlob.Pack(zipData, zipData.Length);
                    pBlob.SetOffset(0);
                }
                return true;
            }
            catch
            {
                return false;
            }
        }

        public int GetNumFile()
        {
            if (m_pZipArchive == null)
                return 0;
            return m_pZipArchive.Entries.Count;
        }

        public ZipFileInfo GetFileInfo(int nIndex)
        {
            if (m_pZipArchive == null)
                return null;
            System.IO.Compression.ZipArchiveEntry entry = m_pZipArchive.Entries[nIndex];
            return new ZipFileInfo(entry.FullName, (int)entry.Length);
        }

        public bool ExtractFileByIndexToBlob(int nIndex, gsBlob pOutBlob)
        {
            if (m_pZipArchive == null)
                return false;
            try
            {
                System.IO.Compression.ZipArchiveEntry entry = m_pZipArchive.Entries[nIndex];
                using (System.IO.Stream stream = entry.Open())
                {
                    byte[] buffer = new byte[entry.Length];
                    stream.ReadExactly(buffer, 0, (int)entry.Length);
                    pOutBlob.Reset();
                    pOutBlob.Pack(buffer, buffer.Length);
                    pOutBlob.SetOffset(0);
                }
            }
            catch
            {
                return false;
            }
            return true;
        }

        public bool ExtractFileByNameToBlob(string szFileName, gsBlob pOutBlob)
        {
            if (m_pZipArchive == null)
                return false;
            for (int i = 0; i < m_pZipArchive.Entries.Count; i++)
            {
                if (m_pZipArchive.Entries[i].FullName.Equals(szFileName))
                    return ExtractFileByIndexToBlob(i, pOutBlob);
            }
            return false;
        }

        public bool ExtractFileByIndexToString(int nIndex, InternalString sOut)
        {
            if (m_pZipArchive == null)
                return false;
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
