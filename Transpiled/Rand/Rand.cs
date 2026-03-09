#line 1 "../LangShared/Transpiled/Rand/Rand.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/Rand/Rand.nll"
	class Rand
	{
#line 7 "../LangShared/Transpiled/Rand/Rand.nll"
		protected const ulong MULTIPLIER = 0x5851f42d4c957f2d;
#line 8 "../LangShared/Transpiled/Rand/Rand.nll"
		protected ulong m_nState;
#line 9 "../LangShared/Transpiled/Rand/Rand.nll"
		protected ulong m_nInc;
#line 11 "../LangShared/Transpiled/Rand/Rand.nll"
		public Rand(uint nSeed)
		{
#line 13 "../LangShared/Transpiled/Rand/Rand.nll"
			Seed(nSeed);
		}

#line 16 "../LangShared/Transpiled/Rand/Rand.nll"
		public void Seed(uint nSeed)
		{
#line 18 "../LangShared/Transpiled/Rand/Rand.nll"
			m_nState = 0;
#line 19 "../LangShared/Transpiled/Rand/Rand.nll"
			m_nInc = ((ulong)(nSeed) << 1) | 1;
#line 20 "../LangShared/Transpiled/Rand/Rand.nll"
			NextUint32();
#line 21 "../LangShared/Transpiled/Rand/Rand.nll"
			m_nState = m_nState + (ulong)(nSeed);
#line 22 "../LangShared/Transpiled/Rand/Rand.nll"
			NextUint32();
		}

#line 25 "../LangShared/Transpiled/Rand/Rand.nll"
		public uint NextUint32()
		{
			ulong nOldState = m_nState;
#line 28 "../LangShared/Transpiled/Rand/Rand.nll"
			m_nState = nOldState * MULTIPLIER + m_nInc;
			uint nXorShifted = (uint)(((nOldState >> 18) ^ nOldState) >> 27);
			uint nRot = (uint)(nOldState >> 59);
			uint nRotNeg = (32 - nRot) & 31;
#line 34 "../LangShared/Transpiled/Rand/Rand.nll"
			return (nXorShifted >> nRot) | (nXorShifted << nRotNeg);
		}

#line 37 "../LangShared/Transpiled/Rand/Rand.nll"
		public double NextDouble()
		{
			const double SCALE = 1.0 / 0xFFFFFFFF;
#line 40 "../LangShared/Transpiled/Rand/Rand.nll"
			return NextUint32() * SCALE;
		}

	}
}

