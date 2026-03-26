using System;

namespace NumbatLogic
{
	public class Base64
	{
		public static gsBlob Decode(string sxBase64)
		{
			if (sxBase64 == null)
				return null;

			try
			{
				byte[] data = Convert.FromBase64String(sxBase64);
				gsBlob blob = new gsBlob();
				blob.Pack(data, data.Length);
				blob.SetOffset(0);
				return blob;
			}
			catch
			{
				return null;
			}
		}
	}
}
