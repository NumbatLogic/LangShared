#include "Assert.hpp"

#if defined(_MSC_VER)
	#include <stdio.h>
	#include <Windows.h>
#elif defined(CMAKE_PLATFORM_ANDROID)
	#include <android/log.h>
	#include <assert.h>
	#include <stdio.h>
#else
	#include <assert.h>
	#include <stdio.h>
#endif

namespace NumbatLogic
{
	void Assert::Plz(bool bTest, const char* sxAssert, const char* sxFile, int nLine)
	{
		if (!bTest)
		{
			#if defined(_MSC_VER)
				printf("Assert: %s (%d) : %s\n", sxFile, nLine, sxAssert);
				DebugBreak();
			#elif defined(CMAKE_PLATFORM_ANDROID)
				//__android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "test");
				__android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "Assert: %s (%d) : %s\n", sxFile, nLine, sxAssert);
				assert(0);
			#else
				printf("Assert: %s (%d) : %s\n", sxFile, nLine, sxAssert);
				assert(0);
			#endif
		}
	}

	void Assert::Plz(bool bTest)
	{
		if (!bTest)
		{
			#if defined(_MSC_VER)
				//printf("Assert: %s (%d) : %s\n", szFile, nLine, szAssert);
				DebugBreak();
			#elif defined(CMAKE_PLATFORM_ANDROID)
				//__android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "Assert: %s (%d) : %s\n", szFile, nLine, szAssert);
				assert(0);
			#else
				//printf("Assert: %s (%d) : %s\n", szFile, nLine, szAssert);
				assert(0);
			#endif
		}
	}
}
