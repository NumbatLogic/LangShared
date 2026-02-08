#pragma once

#include <stdint.h>

namespace NumbatLogic
{
	class Math
	{
		public:
			static constexpr double PI = 3.14159265358979323846;
			static constexpr double DEG_TO_RAD = 0.01745329251994329577;

			static constexpr float PI_F = 3.14159265358979323846f;
			static constexpr float DEG_TO_RAD_F = 0.01745329251994329577f;

			static double Abs(double fX);
			static double Sin(double fAngle);
			static double Cos(double fAngle);
			static double Sqrt(double fX);
			static double Pow(double fbase, double fExponent);
			static double Atan2(double fX, double fY);
			static double Asin(double fX);

			static float FloorF(float fX);
			static float SinF(float fAngle);
			static float CosF(float fAngle);
			static float SqrtF(float fX);
			static float PowF(float fbase, float fExponent);
			static float Atan2F(float fX, float fY);
			static float AsinF(float fX);

			static float LerpF(float fA, float fB, float fT);
			static float LerpAngleF(float fAngle1, float fAngle2, float fT);
	};
}

