namespace NumbatLogic
{
	class ExternalString
	{
		public static bool Equal(string szA, string szB)
		{
			return string.Equals(szA, szB);
		}

		public static int GetChecksum(string szString)
		{
			int nResult = 0xABC123;
			for (int i = 0; i < szString.Length; i++)
			{
				char c = szString[i];
				nResult = (nResult ^ c) << 1;
			}
			return nResult;
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