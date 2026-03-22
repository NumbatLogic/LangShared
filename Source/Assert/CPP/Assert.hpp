#pragma once

namespace NumbatLogic
{
	class Assert
	{
		public: static void Plz(bool bTest, const char* sxAssert, const char* sxFile, int nLine);
		public: static void Plz(bool bTest);
	};
}