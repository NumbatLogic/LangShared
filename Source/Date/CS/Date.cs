using System;

namespace NumbatLogic
{
    public class Date
    {
        public static uint GetUnixDate()
        {
            long value = DateTimeOffset.UtcNow.ToUnixTimeSeconds();
            if (value < 0)
                return 0;
            if (value > uint.MaxValue)
                return uint.MaxValue;
            return (uint)value;
        }
    }
}

