
namespace NumberDuck
{
    namespace Secret
    {
        public class ZipFileInfo
        {
            private string m_sFileName;
            private int m_nSize;
            //private uint m_nCrc32;

            internal ZipFileInfo(string sFileName, int nSize /*, uint nCrc32*/)
            {
                m_sFileName = sFileName;
                m_nSize = nSize;
                //m_nCrc32 = nCrc32;
            }

            public string GetFileName()
            {
                return m_sFileName;
            }

            public int GetSize()
            {
                return m_nSize;
            }

            /*public uint GetCrc32()
            {
                return m_nCrc32;
            }*/
        }
    }
}