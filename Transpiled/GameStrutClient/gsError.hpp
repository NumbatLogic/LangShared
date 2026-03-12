#pragma once

#line 0 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
	class gsError
	{
		public: enum Error
		{
			BAD_HANDSHAKE,
		};

#line 9 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
		public: static const char* Stringify(Error eError);
	};
}

