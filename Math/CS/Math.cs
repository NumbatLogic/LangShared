using System;

namespace NumbatLogic
{
	class Math
	{
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
	}
} 