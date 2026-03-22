namespace NumbatLogic
{
	class Assert
	{
		public static void Plz(bool result, string test, string file, int line)
		{
			if (!result)
				throw new System.Exception(test + "\n" + file + ":" + line);
		}

		public static void Plz(bool result)
		{
			Plz(result, "", "", 0);
		}
	}
}