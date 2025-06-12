#include "Math.hpp"

#include <math.h>

namespace NumbatLogic
{
	double Math::Abs(double fAngle)
	{
		return abs(fAngle);
	}

	double Math::Sin(double fAngle)
	{
		return sin(fAngle);
	}

	double Math::Cos(double fAngle)
	{
		return cos(fAngle);
	}

	double Math::Sqrt(double fX)
	{
		return sqrt(fX);
	}

	double Math::Atan2(double fX, double fY)
	{
		return atan2(fX, fY);
	}
}