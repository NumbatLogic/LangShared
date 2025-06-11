namespace NumbatLogic
{
	class InternalString
	{
		private System.Text.StringBuilder m_pStringBuilder;

		public InternalString(string szString)
		{
			Set(szString);
		}

		public InternalString CreateClone()
		{
			return new InternalString(m_pStringBuilder.ToString());
		}

		public void Set(string szString)
		{
			m_pStringBuilder = new System.Text.StringBuilder(szString);
		}

		public string GetExternalString()
		{
			return m_pStringBuilder.ToString();
		}

		public void Append(string sString)
		{
			m_pStringBuilder.Append(sString);
		}

		public void AppendChar(char nChar)
		{
			m_pStringBuilder.Append(nChar);
		}

		public void AppendString(string szString)
		{
			m_pStringBuilder.Append(szString);
		}

		public void AppendInt(int nInt)
		{
			m_pStringBuilder.Append("" + nInt);
		}

		public void AppendUint32(uint nUint)
		{
			AppendUnsignedInt(nUint);
		}

		public void AppendUnsignedInt(uint nUint)
		{
			m_pStringBuilder.Append("" + nUint);
		}

		public void AppendDouble(double fDouble)
		{
			m_pStringBuilder.Append(fDouble.ToString("G6"));
		}

		public void PrependString(string sString)
		{
			m_pStringBuilder = new System.Text.StringBuilder(sString + m_pStringBuilder.ToString());
		}

		public void PrependChar(char cChar)
		{
			m_pStringBuilder = new System.Text.StringBuilder(cChar + m_pStringBuilder.ToString());
		}

		public void SubStr(int nStart, int nLength)
		{
			m_pStringBuilder = new System.Text.StringBuilder(m_pStringBuilder.ToString().Substring(nStart, nLength));
		}

		public void CropFront(int nLength)
		{
			m_pStringBuilder = new System.Text.StringBuilder(m_pStringBuilder.ToString().Substring(nLength));
		}

		public int GetLength()
		{
			return m_pStringBuilder.Length;
		}

		public char GetChar(int nIndex)
		{
			return m_pStringBuilder[nIndex];
		}

		public void BlobWriteUtf8(BlobView pBlobView, bool bZeroTerminator)
		{
			byte[] pData = System.Text.Encoding.UTF8.GetBytes(m_pStringBuilder.ToString());
			pBlobView.Pack(pData, pData.Length);
			if (bZeroTerminator)
				pBlobView.PackUint8(0);
		}

		public void BlobWrite16Bit(BlobView pBlobView, bool bZeroTerminator)
		{
			byte[] pData = System.Text.Encoding.Unicode.GetBytes(m_pStringBuilder.ToString());
			pBlobView.Pack(pData, pData.Length);
			if (bZeroTerminator)
				pBlobView.PackUint16(0);
		}

		public bool IsAscii()
		{
			return System.Text.Encoding.UTF8.GetByteCount(m_pStringBuilder.ToString()) == m_pStringBuilder.Length;
		}

		public bool IsEqual(string sString)
		{
			return m_pStringBuilder.ToString().Equals(sString);
		}

		public bool StartsWith(string szString)
		{
			return m_pStringBuilder.ToString().StartsWith(szString);
		}

		public bool EndsWith(string szString)
		{
			return m_pStringBuilder.ToString().EndsWith(szString);
		}

		public double ParseDouble()
		{
			return double.Parse(m_pStringBuilder.ToString());
		}

		public uint ParseHex()
		{
			string sTemp = m_pStringBuilder.ToString();
			if (!sTemp.StartsWith("0x", System.StringComparison.Ordinal))
				return 0;
			sTemp = sTemp.Substring(2);
			return uint.Parse(sTemp, System.Globalization.NumberStyles.HexNumber);
		}

		public int FindChar(char nChar)
		{
			return m_pStringBuilder.ToString().IndexOf((char)nChar);
		}

		public void Replace(string sxFind, string sxReplace)
		{
			m_pStringBuilder = new System.Text.StringBuilder(m_pStringBuilder.ToString().Replace(sxFind, sxReplace));
		}
	}
}