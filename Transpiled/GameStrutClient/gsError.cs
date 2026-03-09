#line 1 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
	class gsError
	{
#line 6 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
		public enum Error
		{
			BAD_HANDSHAKE,
		}

#line 10 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
		public static string Stringify(Error eError)
		{
#line 12 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
			switch (eError)
			{
				case Error.BAD_HANDSHAKE:
				{
#line 14 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
					return "Bad handshake";
				}

			}
#line 17 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
			return "Unknown error?";
		}

	}
}

