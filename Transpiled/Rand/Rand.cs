#line 1 "../LangShared/Transpiled/Rand/Rand.nll"
namespace NumbatLogic
{
	class Rand
	{
#line 6 "../LangShared/Transpiled/Rand/Rand.nll"
		protected const ulong MULTIPLIER = 0x5851f42d4c957f2d;
		protected ulong m_nState;
		protected ulong m_nInc;
#line 10 "../LangShared/Transpiled/Rand/Rand.nll"
		public Rand(uint nSeed)
		{
			Seed(nSeed);
		}

		public void Seed(uint nSeed)
		{
			m_nState = 0;
			m_nInc = ((ulong)(nSeed) << 1) | 1;
			NextUint32();
			m_nState = m_nState + (ulong)(nSeed);
			NextUint32();
		}

		public uint NextUint32()
		{
			ulong nOldState = m_nState;
			m_nState = nOldState * MULTIPLIER + m_nInc;
#line 29 "../LangShared/Transpiled/Rand/Rand.nll"
			uint nXorShifted = (uint)(((nOldState >> 18) ^ nOldState) >> 27);
			int nRot = (int)(nOldState >> 59);
			int nRotNeg = (32 - nRot) & 31;
#line 33 "../LangShared/Transpiled/Rand/Rand.nll"
			return (nXorShifted >> nRot) | (nXorShifted << nRotNeg);
		}

		public double NextDouble()
		{
			const double SCALE = 1.0 / 0xFFFFFFFF;
			return NextUint32() * SCALE;
		}

	}
}

