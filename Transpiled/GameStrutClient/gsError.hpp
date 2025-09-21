#pragma once

namespace NumbatLogic
{
	class gsError
	{
		public: enum Error
		{
			BAD_HANDSHAKE,
		};

		public: static const char* Stringify(Error eError);
	};
}

