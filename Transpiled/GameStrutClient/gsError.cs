#line 1 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsError.nll"
namespace NumbatLogic
{
	class gsError
	{
		public enum Error
		{
			BAD_HANDSHAKE,
		}

#line 9 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsError.nll"
		public static string Stringify(Error eError)
		{
			switch (eError)
			{
				case Error.BAD_HANDSHAKE:
				{
#line 13 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsError.nll"
					return "Bad handshake";
				}

			}
#line 16 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsError.nll"
			return "Unknown error?";
		}

	}
}

