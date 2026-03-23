namespace NumbatLogic
{
	public class ZipWriter
	{
		private System.Collections.Generic.List<ZipEntry> m_lstEntries = new System.Collections.Generic.List<ZipEntry>();

		public class ZipEntry
		{
			public string FileName;
			public gsBlob Blob;

			public ZipEntry(string fileName, gsBlob blob)
			{
				FileName = fileName;
				Blob = blob;
			}
		}

		public ZipWriter()
		{
		}

		public bool AddFileFromBlob(string szFileName, gsBlob pBlob)
		{
			try
			{
				// Take ownership of the blob - no copying needed
				ZipEntry entry = new ZipEntry(szFileName, pBlob);
				m_lstEntries.Add(entry);
				return true;
			}
			catch
			{
				return false;
			}
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
						// Add all files to the zip archive
						foreach (ZipEntry entry in m_lstEntries)
						{
							System.IO.Compression.ZipArchiveEntry zipEntry = zipArchive.CreateEntry(entry.FileName);
							using (System.IO.Stream entryStream = zipEntry.Open())
							{
								int nOffset = entry.Blob.__nOffset;
								int nSize = entry.Blob.__nSize - nOffset;
								if (nSize > 0)
								{
									entryStream.Write(entry.Blob.__pBuffer, nOffset, nSize);
								}
							}
						}
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
	}
} 