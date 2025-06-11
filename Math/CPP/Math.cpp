#include "Math.hpp"

#include <math.h>

namespace NumbatLogic
{
	float Math::Abs(float fAngle)
	{
		return abs(fAngle);
	}

	float Math::Sin(float fAngle)
	{
		return sin(fAngle);
	}

	float Math::Cos(float fAngle)
	{
		return cos(fAngle);
	}

	float Math::Sqrt(float fX)
	{
		return sqrt(fX);
	}

	float Math::Atan2(float fX, float fY)
	{
		return atan2(fX, fY);
	}
}