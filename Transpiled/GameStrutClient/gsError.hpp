#pragma once

#line 1 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
	class gsError
	{
#line 6 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
		public: enum Error
		{
			BAD_HANDSHAKE,
		};

#line 10 "../LangShared/Transpiled/GameStrutClient/gsError.nll"
		public: static const char* Stringify(Error eError);
	};
}

