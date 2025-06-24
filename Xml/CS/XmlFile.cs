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

		public bool Load(BlobView pBlobView)
		{
			try
			{
				System.Xml.XmlDocument pDocument = new System.Xml.XmlDocument();
				pDocument.Load(pBlobView.CreateStream());
				m_pNode = pDocument;
			}
			catch (System.Exception)
			{
				return false;
			}
			return true;
		}

		public bool Save(BlobView pBlobView)
		{
			try
			{
				using (System.IO.MemoryStream stream = new System.IO.MemoryStream())
				{
					((System.Xml.XmlDocument)m_pNode).Save(stream);
					stream.Position = 0;
					
					// Ensure the blob has enough space
					int nSize = (int)stream.Length;
					if (pBlobView.GetBlob().GetSize() < pBlobView.GetStart() + nSize)
					{
						pBlobView.GetBlob().Resize(pBlobView.GetStart() + nSize, true);
					}
					
					// Copy the XML data to the blob
					byte[] buffer = stream.ToArray();
					System.Array.Copy(buffer, 0, pBlobView.GetBlob().m_pBuffer, pBlobView.GetStart(), nSize);
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