namespace NumbatLogic
{
	class ZipWriter
	{
		private System.Collections.Generic.List<ZipEntry> m_lstEntries = new System.Collections.Generic.List<ZipEntry>();

		private class ZipEntry
		{
			public string FileName;
			public Blob Blob;

			public ZipEntry(string fileName, Blob blob)
			{
				FileName = fileName;
				Blob = blob;
			}
		}

		public ZipWriter()
		{
		}

		public bool AddFileFromBlob(string szFileName, Blob pBlob)
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

		public bool SaveBlobView(BlobView pBlobView)
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
								entry.Blob.GetBlobView().SetOffset(0);
								System.IO.Stream blobStream = entry.Blob.GetBlobView().CreateStream();
								blobStream.CopyTo(entryStream);
								blobStream.Close();
							}
						}
					}

					// Get the zip data
					byte[] zipData = memoryStream.ToArray();
					
					// Write to blob view
					pBlobView.PackDataAt(pBlobView.GetOffset(), zipData, zipData.Length);
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