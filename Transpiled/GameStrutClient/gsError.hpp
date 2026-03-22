#pragma once

#line 0 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsError.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsError.nll"
	class gsError
	{
		public: enum Error
		{
			BAD_HANDSHAKE,
		};

#line 9 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsError.nll"
		public: static const char* Stringify(Error eError);
	};
}

