#include "gsError.hpp"

namespace NumbatLogic
{
	class gsError;
}
#line 1 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
#line 10 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
	const char* gsError::Stringify(Error eError)
	{
#line 12 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
		switch (eError)
		{
			case Error::BAD_HANDSHAKE:
			{
#line 14 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
				return "Bad handshake";
			}

		}
#line 17 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
		return "Unknown error?";
	}

}

