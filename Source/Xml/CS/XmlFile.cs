namespace NumbatLogic
{
	class XmlFile : XmlNode
	{

		public XmlFile() : base(new System.Xml.XmlDocument())
		{
		}

		public XmlNode CreateElement(string szName)
		{
			System.Xml.XmlElement newElement = ((System.Xml.XmlDocument)m_pNode).CreateElement(szName);
			return new XmlNode(newElement);
		}

		public bool Load(gsBlob pBlob)
		{
			try
			{
				if (pBlob == null || pBlob.__pBuffer == null)
					return false;

				int nOffset = pBlob.GetOffset();
				int nSizeAvailable = pBlob.GetSize() - nOffset;
				if (nSizeAvailable <= 0)
					return false;

				int nStart = nOffset;
				int nCount = nSizeAvailable;

				using (var stream = new System.IO.MemoryStream(pBlob.__pBuffer, nStart, nCount))
				{
					System.Xml.XmlDocument pDocument = new System.Xml.XmlDocument();
					pDocument.Load(stream);
					m_pNode = pDocument;
				}
			}
			catch (System.Exception)
			{
				return false;
			}
			return true;
		}

		public bool Save(gsBlob pBlob)
		{
			try
			{
				if (pBlob == null)
					return false;

				using (System.IO.MemoryStream stream = new System.IO.MemoryStream())
				{
					((System.Xml.XmlDocument)m_pNode).Save(stream);
					byte[] buffer = stream.ToArray();

					pBlob.Resize(buffer.Length);
					System.Buffer.BlockCopy(buffer, 0, pBlob.__pBuffer, 0, buffer.Length);
					pBlob.SetOffset(0);
				}
			}
			catch (System.Exception)
			{
				return false;
			}
			return true;
		}

		public bool SaveToString(InternalString sOut)
		{
			try
			{
				using (var stringWriter = new System.IO.StringWriter())
				{
					((System.Xml.XmlDocument)m_pNode).Save(stringWriter);
					sOut.AppendString(stringWriter.ToString());
				}
			}
			catch (System.Exception)
			{
				return false;
			}
			return true;
		}
	}
}