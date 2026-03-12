#line 1 "../LangShared/Transpiled/Rand/Rand.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/Rand/Rand.nll"
	class Rand
	{
#line 6 "../LangShared/Transpiled/Rand/Rand.nll"
		protected const ulong MULTIPLIER = 0x5851f42d4c957f2d;
#line 7 "../LangShared/Transpiled/Rand/Rand.nll"
		protected ulong m_nState;
#line 8 "../LangShared/Transpiled/Rand/Rand.nll"
		protected ulong m_nInc;
#line 10 "../LangShared/Transpiled/Rand/Rand.nll"
		public Rand(uint nSeed)
		{
#line 12 "../LangShared/Transpiled/Rand/Rand.nll"
			Seed(nSeed);
		}

#line 15 "../LangShared/Transpiled/Rand/Rand.nll"
		public void Seed(uint nSeed)
		{
#line 17 "../LangShared/Transpiled/Rand/Rand.nll"
			m_nState = 0;
#line 18 "../LangShared/Transpiled/Rand/Rand.nll"
			m_nInc = ((ulong)(nSeed) << 1) | 1;
#line 19 "../LangShared/Transpiled/Rand/Rand.nll"
			NextUint32();
#line 20 "../LangShared/Transpiled/Rand/Rand.nll"
			m_nState = m_nState + (ulong)(nSeed);
#line 21 "../LangShared/Transpiled/Rand/Rand.nll"
			NextUint32();
		}

#line 24 "../LangShared/Transpiled/Rand/Rand.nll"
		public uint NextUint32()
		{
#line 26 "../LangShared/Transpiled/Rand/Rand.nll"
			ulong nOldState = m_nState;
#line 27 "../LangShared/Transpiled/Rand/Rand.nll"
			m_nState = nOldState * MULTIPLIER + m_nInc;
#line 29 "../LangShared/Transpiled/Rand/Rand.nll"
			uint nXorShifted = (uint)(((nOldState >> 18) ^ nOldState) >> 27);
#line 30 "../LangShared/Transpiled/Rand/Rand.nll"
			int nRot = (int)(nOldState >> 59);
#line 31 "../LangShared/Transpiled/Rand/Rand.nll"
			int nRotNeg = (32 - nRot) & 31;
#line 33 "../LangShared/Transpiled/Rand/Rand.nll"
			return (nXorShifted >> nRot) | (nXorShifted << nRotNeg);
		}

#line 36 "../LangShared/Transpiled/Rand/Rand.nll"
		public double NextDouble()
		{
#line 38 "../LangShared/Transpiled/Rand/Rand.nll"
			const double SCALE = 1.0 / 0xFFFFFFFF;
#line 39 "../LangShared/Transpiled/Rand/Rand.nll"
			return NextUint32() * SCALE;
		}

	}
}

