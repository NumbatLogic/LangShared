namespace NumbatLogic
{
	class ExternalString
	{
		public static bool Equal(string sxA, string sxB)
		{
			return string.Equals(sxA, sxB);
		}

		public static int GetChecksum(string sxString)
		{
			int nResult = 0xABC123;
			for (int i = 0; i < sxString.Length; i++)
			{
				char c = sxString[i];
				nResult = (nResult ^ c) << 1;
			}
			return nResult;
		}

		public static long hextol(string sxString)
		{
			return long.Parse(sxString, System.Globalization.NumberStyles.HexNumber);
		}

		public static int atoi(string sxString)
		{
			return int.Parse(sxString);
		}

		public static long atol(string sxString)
		{
			return long.Parse(sxString);
		}

		public static double atof(string sxString)
		{
			return double.Parse(sxString);
		}
	}
}