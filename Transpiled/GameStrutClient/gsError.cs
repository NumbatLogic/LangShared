#line 1 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
namespace NumbatLogic
{
	class gsError
	{
		public enum Error
		{
			BAD_HANDSHAKE,
		}

#line 9 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
		public static string Stringify(Error eError)
		{
			switch (eError)
			{
				case Error.BAD_HANDSHAKE:
				{
#line 13 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
					return "Bad handshake";
				}

			}
#line 16 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
			return "Unknown error?";
		}

	}
}

