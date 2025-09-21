#include "gsError.hpp"

namespace NumbatLogic
{
	class gsError;
}
namespace NumbatLogic
{
	const char* gsError::Stringify(Error eError)
	{
		switch (eError)
		{
			case Error::BAD_HANDSHAKE:
			{
				return "Bad handshake";
			}

		}
		return "Unknown error?";
	}

}

