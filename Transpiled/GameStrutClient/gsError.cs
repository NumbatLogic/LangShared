namespace NumbatLogic
{
	class gsError
	{
		public enum Error
		{
			BAD_HANDSHAKE,
		}

		public static string Stringify(Error eError)
		{
			switch (eError)
			{
				case Error.BAD_HANDSHAKE:
				{
					return "Bad handshake";
				}

			}
			return "Unknown error?";
		}

	}
}

