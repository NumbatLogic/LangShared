#include "Date.hpp"

#include <chrono>

namespace NumbatLogic
{
	uint32_t Date::GetUnixDate()
	{
		auto now = std::chrono::system_clock::now();
		auto epoch = std::chrono::system_clock::from_time_t(0);
		auto diff = std::chrono::duration_cast<std::chrono::seconds>(now - epoch);
		auto value = diff.count();
		if (value < 0)
			return 0;
		if (value > 0xFFFFFFFFull)
			return 0xFFFFFFFFu;
		return static_cast<uint32_t>(value);
	}
}

