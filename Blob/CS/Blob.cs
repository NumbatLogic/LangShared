namespace NumbatLogic
{
    class Blob
    {
        private const int DEFAULT_SIZE = 1024 * 32;

        internal byte[] m_pBuffer;
        internal int m_nSize;
        private bool m_bAutoResize;
        private BlobView m_pBlobView;

        public Blob(bool bAutoResize)
        {
            m_pBuffer = new byte[DEFAULT_SIZE];
            m_nSize = 0;
            m_bAutoResize = bAutoResize;
            m_pBlobView = new BlobView(this, 0, 0);
        }

        public bool Load(string fileName)
        {
            try
            {
                byte[] temp = System.IO.File.ReadAllBytes(fileName);
                m_pBuffer = temp;
            }
            catch
            {
                return false;
            }

            m_nSize = m_pBuffer.Length;
            m_pBlobView.m_nEnd = m_nSize;
            return true;
        }

        public bool Save(string fileName)
        {
            try
            {
                using (System.IO.FileStream fs = new System.IO.FileStream(fileName, System.IO.FileMode.Create, System.IO.FileAccess.Write))
                {
                    fs.Write(m_pBuffer, 0, (int)m_nSize);
                }
            }
            catch //(Exception e)
            {
                return false;
            }
            return true;
        }

        public void Resize(int nSize, bool bAutoResize)
        {
            byte[] pOldBuffer = m_pBuffer;
            int nBufferSize = m_pBuffer.Length;

            if (bAutoResize)
                Secret.nbAssert.Assert(m_bAutoResize);

            if (nSize > nBufferSize)
            {
                while (nSize > nBufferSize)
                {
                    // if we are over 100mb, just use the target size, otherwise we'll blow out the RAMs
                    if (nSize > 1024 * 1024 * 100)
                        nBufferSize = nSize;
                    else
                        nBufferSize <<= 1;
                }

                m_pBuffer = new byte[nBufferSize];
                pOldBuffer.CopyTo(m_pBuffer, 0);
                pOldBuffer = null;
            }
            m_nSize = nSize;

            m_pBlobView.m_nEnd = m_nSize;

        }

        public int GetSize()
        {
            return m_nSize;
        }

        public System.IO.Stream CreateStream(int nStart, int nEnd)
        {
            return new System.IO.MemoryStream(m_pBuffer, nStart, nEnd - nStart);
        }

        public uint GetMsoCrc32()
        {
            // https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-oshared/324014d1-39aa-4038-bbf4-f3781732f767
            // https://github.com/chakannom/algorithm/blob/master/MsoCRC32Compute/MsoCRC32Compute/MsoCRC32Compute.cpp
            uint[] nCache = new uint[256];
            {
                uint i;
                for (i = 0; i < 256; i++)
                {
                    uint nBit;
                    uint nValue = i << 24;
                    for (nBit = 0; nBit < 8; nBit++)
                    {
                        if ((nValue & (0x1 << 31)) > 0)
                            nValue = (nValue << 1) ^ 0xAF;
                        else
                            nValue = nValue << 1;
                    }

                    nCache[i] = nValue & 0xFFFF;
                }
            }

            uint nCrcValue = 0;
            {
                uint i;
                for (i = 0; i < m_nSize; i++)
                {
                    uint nIndex = nCrcValue;
                    nIndex = nIndex >> 24;
                    nIndex = nIndex ^ m_pBuffer[i];
                    nCrcValue = nCrcValue << 8;
                    nCrcValue = nCrcValue ^ nCache[nIndex];
                    //printf("%x %lX \n", m_pBuffer[i], nCrcValue);
                }
            }

            return nCrcValue;
        }

        public void Md4Hash(BlobView pOut)
        {
            for (int i = 0; i < 16; i++)
                pOut.PackUint8(0);
            /*unsigned char nTemp[16];
            MD4_CTX ctx;
            MD4_Init(&ctx);
            MD4_Update(&ctx, (void*)m_pBuffer, m_nSize);
            MD4_Final(nTemp, &ctx);

            pOut->PackData(nTemp, 16);*/
        }


        /*public void Unpack(byte[] pTo, int nToOffset, int nFromOffset, int nSize)
		{
			Buffer.BlockCopy(pData, 0, m_pBuffer, (int)nOffset, (int)nSize);
		}*/


        public void UnpackData(byte[] pData, int nOffset, int nSize)
        {
            Secret.nbAssert.Assert(nOffset + nSize <= m_nSize);
            System.Buffer.BlockCopy(m_pBuffer, nOffset, pData, 0, nSize);
        }


        public void PackUint8(byte val, int nOffset) { m_pBuffer[nOffset] = val; }


        public short UnpackInt16(int nOffset) { Secret.nbAssert.Assert(nOffset + 2 <= m_nSize); return System.BitConverter.ToInt16(m_pBuffer, nOffset); }
        public int UnpackInt32(int nOffset) { Secret.nbAssert.Assert(nOffset + 4 <= m_nSize); return System.BitConverter.ToInt32(m_pBuffer, nOffset); }
        public byte UnpackUint8(int nOffset) { Secret.nbAssert.Assert(nOffset + 1 <= m_nSize); return m_pBuffer[nOffset]; }
        public ushort UnpackUint16(int nOffset) { Secret.nbAssert.Assert(nOffset + 2 <= m_nSize); return System.BitConverter.ToUInt16(m_pBuffer, nOffset); }
        public uint UnpackUint32(int nOffset) { Secret.nbAssert.Assert(nOffset + 4 <= m_nSize); return System.BitConverter.ToUInt32(m_pBuffer, nOffset); }
        public double UnpackDouble(int nOffset) { Secret.nbAssert.Assert(nOffset + 8 <= m_nSize); return System.BitConverter.ToDouble(m_pBuffer, nOffset); }


        public void PackData(byte[] pData, int nOffset, int nSize)
        {
            Secret.nbAssert.Assert(nOffset + nSize <= m_nSize);
            System.Buffer.BlockCopy(pData, 0, m_pBuffer, nOffset, nSize);
        }


        public void Pack(byte[] pData, int nDataOffset, int nOffset, int nSize)
        {
            Secret.nbAssert.Assert(nSize > 0);
            Secret.nbAssert.Assert(nOffset + nSize <= m_nSize);
            System.Buffer.BlockCopy(pData, nDataOffset, m_pBuffer, nOffset, nSize);
        }




        //m_pBlob->GetBlobView()->Pack(pBlobView, nSize);


        //public coid UnpackData()

        /*void Blob :: UnpackData(unsigned char* pData, unsigned int nOffset, unsigned int nSize)
		{
			CLIFFY_ASSERT(nOffset + nSize <= m_nSize);
			memcpy(pData, m_pBuffer + nOffset, nSize);
		}*/

        public BlobView GetBlobView()
        {
            return m_pBlobView;
        }

        public bool Equal(Blob pOther)
        {
            if (m_nSize != pOther.m_nSize)
                return false;

            for (int i = 0; i < m_nSize; i++)
                if (m_pBuffer[i] != pOther.m_pBuffer[i])
                    return false;
            return true;
        }
    }

    class BlobView
    {
        internal int m_nStart;
        internal int m_nEnd;
        internal int m_nOffset;
        internal Blob m_pBlob;


        public BlobView(Blob pBlob, int nStart, int nEnd)
        {
            Secret.nbAssert.Assert(nStart <= nEnd);
            Secret.nbAssert.Assert(nEnd <= pBlob.GetSize());

            m_pBlob = pBlob;
            m_nStart = nStart;
            m_nEnd = nEnd;
            m_nOffset = 0;
        }



        public Blob GetBlob()
        {
            return m_pBlob;
        }



        public int GetStart() { return m_nStart; }
        public int GetEnd() { return m_nEnd; }
        public int GetSize()
        {
            int nEnd = m_nEnd;
            if (nEnd == 0)
                nEnd = m_pBlob.GetSize();
            return nEnd - m_nStart;
        }

        public int GetOffset() { return m_nOffset; }

        public void SetOffset(int nOffset)
        {
            // todo: cap?
            m_nOffset = nOffset;
        }

        public System.IO.Stream CreateStream()
        {
            if (this == m_pBlob.GetBlobView())
                return m_pBlob.CreateStream(m_nStart + m_nOffset, m_nStart + m_pBlob.GetSize());
            return m_pBlob.CreateStream(m_nStart + m_nOffset, m_nEnd);
        }

        public void Pack(BlobView pBlobView, int nSize)
        {
            PackAt(m_nOffset, pBlobView, nSize);
            m_nOffset += nSize;
        }

        public void PackAt(int nOffset, BlobView pBlobView, int nSize)
        {
            byte[] pData = new byte[nSize];
            pBlobView.UnpackData(pData, nSize);
            PackDataAt(nOffset, pData, nSize);
        }

        public void PackDataAt(int nOffset, byte[] pData, int nSize)
        {
            int nBlobOffset = m_nStart + nOffset;
            if (this == m_pBlob.GetBlobView())
            {
                if (nBlobOffset + nSize > m_pBlob.GetSize())
                {
                    m_pBlob.Resize(nBlobOffset + nSize, true);
                    //this.m_nEnd = m_pBlob.GetSize();
                }
            }
            else
            {
                Secret.nbAssert.Assert(nBlobOffset + nSize <= m_nEnd);
            }
            m_pBlob.PackData(pData, nBlobOffset, nSize);
        }


        public void Pack(byte[] pData, int nDataSize)
        {
            PackDataAt(m_nOffset, pData, nDataSize);
            m_nOffset += nDataSize;
        }

        public void PackInt16(short val) { Pack(System.BitConverter.GetBytes(val), 2); }
        public void PackInt32(int val) { Pack(System.BitConverter.GetBytes(val), 4); }
        public void PackUint8(byte val) { Pack(System.BitConverter.GetBytes(val), 1); }
        public void PackUint16(ushort val) { Pack(System.BitConverter.GetBytes(val), 2); }
        public void PackUint32(uint val) { Pack(System.BitConverter.GetBytes(val), 4); }
        public void PackDouble(double val) { Pack(System.BitConverter.GetBytes(val), 8); }


        public void Unpack(BlobView pBlobView, int nSize)
        {
            UnpackAt(m_nOffset, pBlobView, nSize);
            m_nOffset += nSize;
        }

        public void UnpackAt(int nOffset, BlobView pBlobView, int nSize)
        {
            byte[] pData = new byte[nSize];
            UnpackDataAt(nOffset, pData, nSize);

            pBlobView.Pack(pData, nSize);
        }


        public void UnpackData(byte[] pData, int nSize)
        {
            UnpackDataAt(m_nOffset, pData, nSize);
            m_nOffset += nSize;
        }

        public void UnpackDataAt(int nOffset, byte[] pData, int nSize)
        {
            int nBlobOffset = m_nStart + nOffset;
            int nEnd = m_nEnd;
            if (nEnd == 0)
                nEnd = m_pBlob.GetSize();
            Secret.nbAssert.Assert(nBlobOffset + nSize <= nEnd);
            m_pBlob.UnpackData(pData, nBlobOffset, nSize);
        }


        /*public void Unpack(BlobView pBlobView, int nSize)
		{
			CliffyAssert.Assert(m_nStart + m_nOffset + nSize < m_nEnd);



			m_pBlob.Unpack(m_nStart + m_nOffset, nSize, pBlobView->m_pBlob, pBlobView.m_nStart + m_nOffset);

			//m_pBlob.UnpackAt
		}*/

        /*void BlobView :: Unpack(BlobView* pBlobView, unsigned int nSize)
		{
			UnpackAt(m_nOffset, pBlobView, nSize);
			m_nOffset += nSize;
		}

		void BlobView :: UnpackAt(unsigned int nOffset, BlobView* pBlobView, unsigned int nSize)
		{
			unsigned char* pData = new unsigned char[nSize];
			UnpackDataAt(nOffset, pData,nSize);

			pBlobView->PackData(pData, nSize);
			delete [] pData;
		}*/



        public short UnpackInt16() { short nTemp = m_pBlob.UnpackInt16(m_nStart + m_nOffset); m_nOffset += 2; return nTemp; }
        public int UnpackInt32() { int nTemp = m_pBlob.UnpackInt32(m_nStart + m_nOffset); m_nOffset += 4; return nTemp; }

        public int UnpackInt32At(int nOffset) { return m_pBlob.UnpackInt32(m_nStart + nOffset); }

        public byte UnpackUint8() { byte nTemp = m_pBlob.UnpackUint8(m_nStart + m_nOffset++); return nTemp; }
        public ushort UnpackUint16() { ushort nTemp = m_pBlob.UnpackUint16(m_nStart + m_nOffset); m_nOffset += 2; return nTemp; }
        public uint UnpackUint32() { uint nTemp = m_pBlob.UnpackUint32(m_nStart + m_nOffset); m_nOffset += 4; return nTemp; }
        public double UnpackDouble() { double fTemp = m_pBlob.UnpackDouble(m_nStart + m_nOffset); m_nOffset += 8; return fTemp; }






        public byte GetChecksum()
        {
            const int WIDTH = 8;
            const byte TOPBIT = (1 << (WIDTH - 1));
            const byte POLYNOMIAL = 0xD8;  /* 11011 followed by 0's */

            byte remainder = 0;
            int nEnd = m_nEnd;
            if (nEnd == 0)
                nEnd = m_pBlob.m_nSize;

            for (int currentByte = m_nStart; currentByte < nEnd; currentByte++)
            {
                remainder ^= m_pBlob.m_pBuffer[currentByte];
                for (int bit = 8; bit > 0; --bit)
                {
                    if ((remainder & TOPBIT) > 0)
                    {
                        remainder = (byte)((remainder << 1) ^ POLYNOMIAL);
                    }
                    else
                    {
                        remainder = (byte)(remainder << 1);
                    }
                }
            }
            return (remainder);
        }


    }
}
