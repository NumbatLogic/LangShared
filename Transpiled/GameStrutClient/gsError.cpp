#include "gsError.hpp"

namespace NumbatLogic
{
	class gsError;
}
#line 0 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsError.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsError.nll"
#line 9 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsError.nll"
	const char* gsError::Stringify(Error eError)
	{
		switch (eError)
		{
			case Error::BAD_HANDSHAKE:
			{
#line 13 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsError.nll"
				return "Bad handshake";
			}

		}
#line 16 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsError.nll"
		return "Unknown error?";
	}

}

