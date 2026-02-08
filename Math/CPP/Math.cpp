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

	double Math::Pow(double fbase, double fExponent)
	{
		return pow(fbase, fExponent);
	}

	double Math::Atan2(double fX, double fY)
	{
		return atan2(fX, fY);
	}

	double Math::Asin(double fX)
	{
		return asin(fX);
	}

	float Math::FloorF(float fX)
	{
		return floorf(fX);
	}

	float Math::SinF(float fAngle)
	{
		return sinf(fAngle);
	}

	float Math::CosF(float fAngle)
	{
		return cosf(fAngle);
	}

	float Math::SqrtF(float fX)
	{
		return sqrtf(fX);
	}

	float Math::PowF(float fbase, float fExponent)
	{
		return powf(fbase, fExponent);
	}

	float Math::Atan2F(float fX, float fY)
	{
		return atan2f(fX, fY);
	}

	float Math::AsinF(float fX)
	{
		return asinf(fX);
	}

	float Math::LerpF(float fA, float fB, float fT)
	{
		return fA + (fB - fA) * fT;
	}

	float Math::LerpAngleF(float fAngle1, float fAngle2, float fT)
	{
		float fDiff = fAngle2 - fAngle1;
		if (fDiff > PI_F)
			fDiff -= 2.0f * PI_F;
		else if (fDiff < -PI_F)
			fDiff += 2.0f * PI_F;
		return fAngle1 + fDiff * fT;
	}
}