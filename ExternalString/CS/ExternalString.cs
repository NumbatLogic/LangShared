namespace NumbatLogic
{
	class ExternalString
	{
		public static bool Equal(string szA, string szB)
		{
			return string.Equals(szA, szB);
		}

		public static uint GetChecksum(string szString)
		{
			ulong hash = 0;
			for (int i = 0; i < szString.Length; i++)
			{
				ulong c = szString[i];
				hash = c + (hash << 6) + (hash << 16) - hash;
			}
			return (uint)hash;
		}

		public static long hextol(string szString)
		{
			return long.Parse(szString, System.Globalization.NumberStyles.HexNumber);
		}

		public static int atoi(string szString)
		{
			return int.Parse(szString);
		}

		public static long atol(string szString)
		{
			return long.Parse(szString);
		}

		public static double atof(string szString)
		{
			return double.Parse(szString);
		}

	}
}