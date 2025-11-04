#pragma once

#include <stdint.h>

namespace NumbatLogic
{
	class Math
	{
		public:
			static double Abs(double fX);
			static double Sin(double fAngle);
			static double Cos(double fAngle);
			static double Sqrt(double fX);
			static double Pow(double fbase, double fExponent);
			static double Atan2(double fX, double fY);

			static float FloorF(float fX);
			static float SinF(float fAngle);
			static float CosF(float fAngle);
			static float SqrtF(float fX);
			static float PowF(float fbase, float fExponent);
			static float Atan2F(float fX, float fY);
	};
}

