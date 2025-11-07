namespace NumbatLogic
{
	class gsBlob
	{
		private const int DEFAULT_SIZE = 64;

		internal byte[] m_pBuffer;
		internal int m_nSize;
		internal int m_nOffset;
		

		public gsBlob()
		{
			m_pBuffer = new byte[DEFAULT_SIZE];
			m_nSize = 0;
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
			m_nOffset = 0;
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

		public byte GetChecksum()
		{
			const int WIDTH = 8;
			const byte TOPBIT = (1 << (WIDTH - 1));
			const byte POLYNOMIAL = 0xD8;  /* 11011 followed by 0's */

			byte remainder = 0;
			for (int currentByte = 0; currentByte < m_nSize; currentByte++)
			{
				remainder ^= m_pBuffer[currentByte];
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

		public void Resize(int nSize)
		{
			byte[] pOldBuffer = m_pBuffer;
			int nBufferSize = m_pBuffer.Length;

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
		}

		public int GetSize()
		{
			return m_nSize;
		}

		public int GetOffset()
		{
			return m_nOffset;
		}

		public void SetOffset(int nOffset)
		{
			Assert.Plz(nOffset < m_nSize);
			m_nOffset = nOffset;
		}

		public System.IO.Stream CreateStream(int nStart, int nEnd)
		{
			return new System.IO.MemoryStream(m_pBuffer, nStart, nEnd - nStart);
		}

		/*public void Pack(BlobView pBlobView, int nSize)
		{
			PackAt(m_nOffset, pBlobView, nSize);
			m_nOffset += nSize;
		}

		public void PackAt(int nOffset, BlobView pBlobView, int nSize)
		{
			byte[] pData = new byte[nSize];
			pBlobView.UnpackData(pData, nSize);
			PackDataAt(nOffset, pData, nSize);
		}*/

		public void PackDataAt(int nOffset, byte[] pData, int nSize)
		{
			if (nOffset + nSize > m_nSize)
				Resize(nOffset + nSize);
			System.Buffer.BlockCopy(pData, 0, m_pBuffer, nOffset, nSize);
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
		

		public void PackInternalString(InternalString sString)
		{
			byte[] pData = System.Text.Encoding.UTF8.GetBytes(sString.GetExternalString());
			PackUint32((uint)pData.Length);
			Pack(pData, pData.Length);
		}

		





		public bool UnpackInt16(ref short val) { const int SIZE = 2; if (m_nOffset + SIZE > m_nSize) return false; val = System.BitConverter.ToInt16(m_pBuffer, m_nOffset); m_nOffset += SIZE; return true; }
		public bool UnpackInt32(ref int val) {  const int SIZE = 4; if (m_nOffset + SIZE > m_nSize) return false; val = System.BitConverter.ToInt32(m_pBuffer, m_nOffset); m_nOffset += SIZE; return true; }
		public bool UnpackUint8(ref byte val) { const int SIZE = 1; if (m_nOffset + SIZE > m_nSize) return false; val = m_pBuffer[m_nOffset]; m_nOffset += SIZE; return true; }
		public bool UnpackUint16(ref ushort val) { const int SIZE = 2; if (m_nOffset + SIZE > m_nSize) return false; val = System.BitConverter.ToUInt16(m_pBuffer, m_nOffset); m_nOffset += SIZE; return true; }
		public bool UnpackUint32(ref uint val) { const int SIZE = 4; if (m_nOffset + SIZE > m_nSize) return false; val = System.BitConverter.ToUInt32(m_pBuffer, m_nOffset); m_nOffset += SIZE; return true; }
		public bool UnpackDouble(ref double val) { const int SIZE = 8; if (m_nOffset + SIZE > m_nSize) return false; val = System.BitConverter.ToDouble(m_pBuffer, m_nOffset); m_nOffset += SIZE; return true; }


		public bool UnpackInternalString(InternalString sString)
		{
			uint nByteLength = 0;
			if (!UnpackUint32(ref nByteLength))
				return false;
			
			if (nByteLength == 0)
			{
				sString.Set("");
				return true;
			}

			if (m_nOffset + nByteLength > m_nSize)
				return false;

			sString.Set(System.Text.Encoding.UTF8.GetString(m_pBuffer, m_nOffset, (int)nByteLength));
			m_nOffset += (int)nByteLength;

			return true;
		}



		/*public void Unpack(byte[] pTo, int nToOffset, int nFromOffset, int nSize)
		{
			Buffer.BlockCopy(pData, 0, m_pBuffer, (int)nOffset, (int)nSize);
		}*/
/*

		public void UnpackData(byte[] pData, int nOffset, int nSize)
		{
			Assert.Plz(nOffset + nSize <= m_nSize);
			System.Buffer.BlockCopy(m_pBuffer, nOffset, pData, 0, nSize);
		}


		public void PackUint8(byte val, int nOffset) { m_pBuffer[nOffset] = val; }


		


		public void PackData(byte[] pData, int nOffset, int nSize)
		{
			Assert.Plz(nOffset + nSize <= m_nSize);
			System.Buffer.BlockCopy(pData, 0, m_pBuffer, nOffset, nSize);
		}


		public void Pack(byte[] pData, int nDataOffset, int nOffset, int nSize)
		{
			Assert.Plz(nSize > 0);
			Assert.Plz(nOffset + nSize <= m_nSize);
			System.Buffer.BlockCopy(pData, nDataOffset, m_pBuffer, nOffset, nSize);
		}


*/

		//m_pBlob->GetBlobView()->Pack(pBlobView, nSize);


		//public coid UnpackData()

		/*void Blob :: UnpackData(unsigned char* pData, unsigned int nOffset, unsigned int nSize)
		{
			CLIFFY_ASSERT(nOffset + nSize <= m_nSize);
			memcpy(pData, m_pBuffer + nOffset, nSize);
		}*/
/*
		public bool Equal(Blob pOther)
		{
			if (m_nSize != pOther.m_nSize)
				return false;

			for (int i = 0; i < m_nSize; i++)
				if (m_pBuffer[i] != pOther.m_pBuffer[i])
					return false;
			return true;
		}

		public Blob Clone()
		{
			Blob clone = new Blob(m_bAutoResize);
			clone.m_nSize = m_nSize;
			
			// Create a new buffer with the same size as the original
			clone.m_pBuffer = new byte[m_pBuffer.Length];
			
			// Copy all data from original buffer
			System.Buffer.BlockCopy(m_pBuffer, 0, clone.m_pBuffer, 0, m_nSize);
			
			// Update the blob view to reflect the new size
			clone.m_pBlobView.m_nEnd = m_nSize;
			
			return clone;
		}*/
	}
/*
	class BlobView
	{
		internal int m_nStart;
		internal int m_nEnd;
		internal int m_nOffset;
		internal Blob m_pBlob;


		public BlobView(Blob pBlob, int nStart, int nEnd)
		{
			Assert.Plz(nStart <= nEnd);
			Assert.Plz(nEnd <= pBlob.GetSize());

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
			Assert.Plz(nBlobOffset + nSize <= nEnd);
			m_pBlob.UnpackData(pData, nBlobOffset, nSize);
		}




		public short UnpackInt16() { short nTemp = m_pBlob.UnpackInt16(m_nStart + m_nOffset); m_nOffset += 2; return nTemp; }
		public int UnpackInt32() { int nTemp = m_pBlob.UnpackInt32(m_nStart + m_nOffset); m_nOffset += 4; return nTemp; }

		public int UnpackInt32At(int nOffset) { return m_pBlob.UnpackInt32(m_nStart + nOffset); }

		public byte UnpackUint8() { byte nTemp = m_pBlob.UnpackUint8(m_nStart + m_nOffset++); return nTemp; }
		public ushort UnpackUint16() { ushort nTemp = m_pBlob.UnpackUint16(m_nStart + m_nOffset); m_nOffset += 2; return nTemp; }
		public uint UnpackUint32() { uint nTemp = m_pBlob.UnpackUint32(m_nStart + m_nOffset); m_nOffset += 4; return nTemp; }
		public double UnpackDouble() { double fTemp = m_pBlob.UnpackDouble(m_nStart + m_nOffset); m_nOffset += 8; return fTemp; }






		


	}*/
}
