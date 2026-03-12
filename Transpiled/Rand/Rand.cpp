#include "Rand.hpp"

namespace NumbatLogic
{
	class Rand;
}
#line 0 "../LangShared/Transpiled/Rand/Rand.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/Rand/Rand.nll"
#line 10 "../LangShared/Transpiled/Rand/Rand.nll"
	Rand::Rand(unsigned int nSeed)
	{
		m_nState = 0;
		m_nInc = 0;
#line 12 "../LangShared/Transpiled/Rand/Rand.nll"
		Seed(nSeed);
	}

#line 15 "../LangShared/Transpiled/Rand/Rand.nll"
	void Rand::Seed(unsigned int nSeed)
	{
#line 17 "../LangShared/Transpiled/Rand/Rand.nll"
		m_nState = 0;
#line 18 "../LangShared/Transpiled/Rand/Rand.nll"
		m_nInc = ((unsigned long long)(nSeed) << 1) | 1;
#line 19 "../LangShared/Transpiled/Rand/Rand.nll"
		NextUint32();
#line 20 "../LangShared/Transpiled/Rand/Rand.nll"
		m_nState = m_nState + (unsigned long long)(nSeed);
#line 21 "../LangShared/Transpiled/Rand/Rand.nll"
		NextUint32();
	}

#line 24 "../LangShared/Transpiled/Rand/Rand.nll"
	unsigned int Rand::NextUint32()
	{
#line 26 "../LangShared/Transpiled/Rand/Rand.nll"
		unsigned long long nOldState = m_nState;
#line 27 "../LangShared/Transpiled/Rand/Rand.nll"
		m_nState = nOldState * MULTIPLIER + m_nInc;
#line 29 "../LangShared/Transpiled/Rand/Rand.nll"
		unsigned int nXorShifted = (unsigned int)(((nOldState >> 18) ^ nOldState) >> 27);
#line 30 "../LangShared/Transpiled/Rand/Rand.nll"
		int nRot = (int)(nOldState >> 59);
#line 31 "../LangShared/Transpiled/Rand/Rand.nll"
		int nRotNeg = (32 - nRot) & 31;
#line 33 "../LangShared/Transpiled/Rand/Rand.nll"
		return (nXorShifted >> nRot) | (nXorShifted << nRotNeg);
	}

#line 36 "../LangShared/Transpiled/Rand/Rand.nll"
	double Rand::NextDouble()
	{
#line 38 "../LangShared/Transpiled/Rand/Rand.nll"
		const double SCALE = 1.0 / 0xFFFFFFFF;
#line 39 "../LangShared/Transpiled/Rand/Rand.nll"
		return NextUint32() * SCALE;
	}

}

