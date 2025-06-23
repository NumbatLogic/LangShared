namespace NumbatLogic
{
	class XmlFile : XmlNode
	{
		public XmlFile() : base(null)
		{
		}

		public bool Load(BlobView pBlobView)
		{
			try
			{
				System.Xml.XmlDocument document = new System.Xml.XmlDocument();
				document.Load(pBlobView.CreateStream());
				m_pNode = document;
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
				if (m_pNode == null)
					return false;

				System.Xml.XmlDocument document = m_pNode as System.Xml.XmlDocument;
				if (document == null)
					return false;

				// Create a memory stream to hold the XML
				using (System.IO.MemoryStream stream = new System.IO.MemoryStream())
				{
					document.Save(stream);
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