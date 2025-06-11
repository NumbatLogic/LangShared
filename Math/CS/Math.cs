using System;

namespace NumbatLogic
{
	class Math
	{
		public static float Abs(float fX)
		{
			return System.Math.Abs(fX);
		}

		public static float Sin(float fAngle)
		{
			return (float)System.Math.Sin(fAngle);
		}

		public static float Cos(float fAngle)
		{
			return (float)System.Math.Cos(fAngle);
		}

		public static float Sqrt(float fValue)
		{
			return (float)System.Math.Sqrt(fValue);
		}

		public static float Atan2(float fY, float fX)
		{
			return (float)System.Math.Atan2(fY, fX);
		}
	}
} 