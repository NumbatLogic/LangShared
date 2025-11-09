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

		public void PackBool(bool val) { PackUint8(val ? (byte)1 : (byte)0); }
		public void PackInt16(short val) { Pack(System.BitConverter.GetBytes(val), 2); }
		public void PackInt32(int val) { Pack(System.BitConverter.GetBytes(val), 4); }
		public void PackUint8(byte val) { Pack(System.BitConverter.GetBytes(val), 1); }
		public void PackUint16(ushort val) { Pack(System.BitConverter.GetBytes(val), 2); }
		public void PackUint32(uint val) { Pack(System.BitConverter.GetBytes(val), 4); }
		public void PackDouble(double val) { Pack(System.BitConverter.GetBytes(val), 8); }
		

		public void PackInternalString(InternalString sString)
		{
			byte[] pData = System.Text.Encoding.UTF8.GetBytes(sString.GetExternalString());
			PackUint16((ushort)pData.Length);
			Pack(pData, pData.Length);
		}

		public void PackBlob(gsBlob pBlob)
		{
			PackUint16((ushort)pBlob.m_nSize);
			Pack(pBlob.m_pBuffer, pBlob.m_nSize);
		}

		




		public bool UnpackBool(ref bool val)
		{
			byte n = 0;
			if (!UnpackUint8(ref n))
				return false;
			val = n == 1;
			return true;
		}
		
		public bool UnpackInt16(ref short val) { const int SIZE = 2; if (m_nOffset + SIZE > m_nSize) return false; val = System.BitConverter.ToInt16(m_pBuffer, m_nOffset); m_nOffset += SIZE; return true; }
		public bool UnpackInt32(ref int val) {  const int SIZE = 4; if (m_nOffset + SIZE > m_nSize) return false; val = System.BitConverter.ToInt32(m_pBuffer, m_nOffset); m_nOffset += SIZE; return true; }
		public bool UnpackUint8(ref byte val) { const int SIZE = 1; if (m_nOffset + SIZE > m_nSize) return false; val = m_pBuffer[m_nOffset]; m_nOffset += SIZE; return true; }
		public bool UnpackUint16(ref ushort val) { const int SIZE = 2; if (m_nOffset + SIZE > m_nSize) return false; val = System.BitConverter.ToUInt16(m_pBuffer, m_nOffset); m_nOffset += SIZE; return true; }
		public bool UnpackUint32(ref uint val) { const int SIZE = 4; if (m_nOffset + SIZE > m_nSize) return false; val = System.BitConverter.ToUInt32(m_pBuffer, m_nOffset); m_nOffset += SIZE; return true; }
		public bool UnpackDouble(ref double val) { const int SIZE = 8; if (m_nOffset + SIZE > m_nSize) return false; val = System.BitConverter.ToDouble(m_pBuffer, m_nOffset); m_nOffset += SIZE; return true; }


		public bool UnpackInternalString(InternalString sString)
		{
			ushort nByteLength = 0;
			if (!UnpackUint16(ref nByteLength))
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

		public bool UnpackBlob(gsBlob pBlob)
		{
			ushort nSize = 0;
			if (!UnpackUint16(ref nSize))
				return false;

			pBlob.Resize(nSize);

			if (nSize == 0)
				return true;

			if (nSize > m_nOffset - m_nSize)
				return false;

			System.Buffer.BlockCopy(pBlob.m_pBuffer, 0, m_pBuffer, m_nOffset, nSize);

			return true;
		}
	}
}
