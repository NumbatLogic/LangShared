namespace NumbatLogic
{
	class gsBlob
	{
		private const int DEFAULT_SIZE = 64;

		public byte[] __pBuffer;
		public int __nSize;
		public int __nOffset;
		

		public gsBlob()
		{
			__pBuffer = new byte[DEFAULT_SIZE];
			__nSize = 0;
		}

		public bool Load(string fileName)
		{
			try
			{
				byte[] temp = System.IO.File.ReadAllBytes(fileName);
				__pBuffer = temp;
			}
			catch
			{
				return false;
			}

			__nSize = __pBuffer.Length;
			__nOffset = 0;
			return true;
		}

		public bool Save(string fileName)
		{
			try
			{
				using (System.IO.FileStream fs = new System.IO.FileStream(fileName, System.IO.FileMode.Create, System.IO.FileAccess.Write))
				{
					fs.Write(__pBuffer, 0, (int)__nSize);
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
			for (int currentByte = 0; currentByte < __nSize; currentByte++)
			{
				remainder ^= __pBuffer[currentByte];
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
			byte[] pOldBuffer = __pBuffer;
			int nBufferSize = __pBuffer.Length;

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

				__pBuffer = new byte[nBufferSize];
				pOldBuffer.CopyTo(__pBuffer, 0);
				pOldBuffer = null;
			}
			__nSize = nSize;
		}

		public int GetSize()
		{
			return __nSize;
		}

		public int GetOffset()
		{
			return __nOffset;
		}

		public void SetOffset(int nOffset)
		{
			Assert.Plz(nOffset < __nSize);
			__nOffset = nOffset;
		}

		public System.IO.Stream CreateStream(int nStart, int nEnd)
		{
			return new System.IO.MemoryStream(__pBuffer, nStart, nEnd - nStart);
		}

		/*public void Pack(BlobView pBlobView, int nSize)
		{
			PackAt(__nOffset, pBlobView, nSize);
			__nOffset += nSize;
		}

		public void PackAt(int nOffset, BlobView pBlobView, int nSize)
		{
			byte[] pData = new byte[nSize];
			pBlobView.UnpackData(pData, nSize);
			PackDataAt(nOffset, pData, nSize);
		}*/

		public void PackDataAt(int nOffset, byte[] pData, int nSize)
		{
			if (nOffset + nSize > __nSize)
				Resize(nOffset + nSize);
			System.Buffer.BlockCopy(pData, 0, __pBuffer, nOffset, nSize);
		}

		public void Pack(byte[] pData, int nDataSize)
		{
			PackDataAt(__nOffset, pData, nDataSize);
			__nOffset += nDataSize;
		}

		public void PackBool(bool val) { PackUint8(val ? (byte)1 : (byte)0); }
		public void PackInt8(sbyte val) { Pack(System.BitConverter.GetBytes(val), 1); }
		public void PackInt16(short val) { Pack(System.BitConverter.GetBytes(val), 2); }
		public void PackInt32(int val) { Pack(System.BitConverter.GetBytes(val), 4); }
		public void PackUint8(byte val) { Pack(System.BitConverter.GetBytes(val), 1); }
		public void PackUint16(ushort val) { Pack(System.BitConverter.GetBytes(val), 2); }
		public void PackUint32(uint val) { Pack(System.BitConverter.GetBytes(val), 4); }
		public void PackFloat(float val) { Pack(System.BitConverter.GetBytes(val), 4); }
		public void PackDouble(double val) { Pack(System.BitConverter.GetBytes(val), 8); }
		

		public void PackInternalString(InternalString sString)
		{
			byte[] pData = System.Text.Encoding.UTF8.GetBytes(sString.GetExternalString());
			PackUint16((ushort)pData.Length);
			Pack(pData, pData.Length);
		}

		public void PackBlob(gsBlob pBlob)
		{
			PackUint16((ushort)pBlob.__nSize);
			Pack(pBlob.__pBuffer, pBlob.__nSize);
		}

		




		public bool UnpackBool(ref bool val)
		{
			byte n = 0;
			if (!UnpackUint8(ref n))
				return false;
			val = n == 1;
			return true;
		}

		public bool UnpackInt8(ref sbyte val) { const int SIZE = 1; if (__nOffset + SIZE > __nSize) return false; val = unchecked((sbyte)__pBuffer[__nOffset]); __nOffset += SIZE; return true; }
		public bool UnpackInt16(ref short val) { const int SIZE = 2; if (__nOffset + SIZE > __nSize) return false; val = System.BitConverter.ToInt16(__pBuffer, __nOffset); __nOffset += SIZE; return true; }
		public bool UnpackInt32(ref int val) {  const int SIZE = 4; if (__nOffset + SIZE > __nSize) return false; val = System.BitConverter.ToInt32(__pBuffer, __nOffset); __nOffset += SIZE; return true; }
		public bool UnpackUint8(ref byte val) { const int SIZE = 1; if (__nOffset + SIZE > __nSize) return false; val = __pBuffer[__nOffset]; __nOffset += SIZE; return true; }
		public bool UnpackUint16(ref ushort val) { const int SIZE = 2; if (__nOffset + SIZE > __nSize) return false; val = System.BitConverter.ToUInt16(__pBuffer, __nOffset); __nOffset += SIZE; return true; }
		public bool UnpackUint32(ref uint val) { const int SIZE = 4; if (__nOffset + SIZE > __nSize) return false; val = System.BitConverter.ToUInt32(__pBuffer, __nOffset); __nOffset += SIZE; return true; }
		public bool UnpackFloat(ref float val) { const int SIZE = 4; if (__nOffset + SIZE > __nSize) return false; val = System.BitConverter.ToSingle(__pBuffer, __nOffset); __nOffset += SIZE; return true; }
		public bool UnpackDouble(ref double val) { const int SIZE = 8; if (__nOffset + SIZE > __nSize) return false; val = System.BitConverter.ToDouble(__pBuffer, __nOffset); __nOffset += SIZE; return true; }


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

			if (__nOffset + nByteLength > __nSize)
				return false;

			sString.Set(System.Text.Encoding.UTF8.GetString(__pBuffer, __nOffset, (int)nByteLength));
			__nOffset += (int)nByteLength;

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

			if (nSize > __nSize - __nOffset)
				return false;
			
			System.Buffer.BlockCopy(pBlob.__pBuffer, 0, __pBuffer, __nOffset, nSize);

			return true;
		}
	}
}
