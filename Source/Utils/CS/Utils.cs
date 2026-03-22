namespace NumbatLogic
{
    class Utils
    {
        public static double Pow(double fBase, double fExponent)
        {
            return System.Math.Pow(fBase, fExponent);
        }

        public static double ByteConvertUint64ToDouble(ulong nValue)
        {
            byte[] nByteArray = System.BitConverter.GetBytes(nValue);
            return System.BitConverter.ToDouble(nByteArray, 0);
        }

        public static int ByteConvertUint32ToInt32(uint nValue)
        {
            byte[] nByteArray = System.BitConverter.GetBytes(nValue);
            return System.BitConverter.ToInt32(nByteArray, 0);
        }

        public static uint ByteConvertInt32ToUint32(int nValue)
        {
            byte[] nByteArray = System.BitConverter.GetBytes(nValue);
            return System.BitConverter.ToUInt32(nByteArray, 0);
        }

        public static void Indent(int nTabDepth, InternalString sOut)
        {
            for (int i = 0; i < nTabDepth; i++)
                sOut.AppendChar('\t');
        }

        public static void Sleep(int nMilliseconds)
        {
            System.Threading.Thread.Sleep(nMilliseconds);
        }
    }
}
