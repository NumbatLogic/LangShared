#include "gsError.hpp"

namespace NumbatLogic
{
	class gsError;
}
#line 0 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
#line 9 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
	const char* gsError::Stringify(Error eError)
	{
#line 11 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
		switch (eError)
		{
			case Error::BAD_HANDSHAKE:
			{
#line 13 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
				return "Bad handshake";
			}

		}
#line 16 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
		return "Unknown error?";
	}

}

