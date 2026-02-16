using System;

namespace NumbatLogic
{
	class Math
	{
		public const double PI = 3.14159265358979323846;
		public const double DEG_TO_RAD = 0.01745329251994329577;

		public const float PI_F = 3.14159265358979323846f;
		public const float DEG_TO_RAD_F = 0.01745329251994329577f;

		public static double Abs(double fX)
		{
			return System.Math.Abs(fX);
		}

		public static double Sin(double fAngle)
		{
			return System.Math.Sin(fAngle);
		}

		public static double Cos(double fAngle)
		{
			return System.Math.Cos(fAngle);
		}

		public static double Sqrt(double fValue)
		{
			return System.Math.Sqrt(fValue);
		}

		public static double Atan2(double fY, double fX)
		{
			return System.Math.Atan2(fY, fX);
		}

		public static double Asin(double fX)
		{
			return System.Math.Asin(fX);
		}

		public static float AbsF(float fX)
		{
			return System.MathF.Abs(fX);
		}

		public static float SinF(float fAngle)
		{
			return System.MathF.Sin(fAngle);
		}

		public static float CosF(float fAngle)
		{
			return System.MathF.Cos(fAngle);
		}

		public static float SqrtF(float fValue)
		{
			return System.MathF.Sqrt(fValue);
		}

		public static float Atan2F(float fY, float fX)
		{
			return System.MathF.Atan2(fY, fX);
		}

		public static float AsinF(float fX)
		{
			return System.MathF.Asin(fX);
		}

		public static float LerpF(float fA, float fB, float fT)
		{
			return fA + (fB - fA) * fT;
		}

		public static float LerpAngleF(float fAngle1, float fAngle2, float fT)
		{
			float fDiff = fAngle2 - fAngle1;
			if (fDiff > PI_F)
				fDiff -= 2.0f * PI_F;
			else if (fDiff < -PI_F)
				fDiff += 2.0f * PI_F;
			return fAngle1 + fDiff * fT;
		}
	}
} 