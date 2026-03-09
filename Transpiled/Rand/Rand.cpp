#include "Rand.hpp"

namespace NumbatLogic
{
	class Rand;
}
#line 1 "../LangShared/Transpiled/Rand/Rand.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/Rand/Rand.nll"
#line 11 "../LangShared/Transpiled/Rand/Rand.nll"
	Rand::Rand(unsigned int nSeed)
	{
		m_nState = 0;
		m_nInc = 0;
#line 13 "../LangShared/Transpiled/Rand/Rand.nll"
		Seed(nSeed);
	}

#line 16 "../LangShared/Transpiled/Rand/Rand.nll"
	void Rand::Seed(unsigned int nSeed)
	{
#line 18 "../LangShared/Transpiled/Rand/Rand.nll"
		m_nState = 0;
#line 19 "../LangShared/Transpiled/Rand/Rand.nll"
		m_nInc = ((unsigned long long)(nSeed) << 1) | 1;
#line 20 "../LangShared/Transpiled/Rand/Rand.nll"
		NextUint32();
#line 21 "../LangShared/Transpiled/Rand/Rand.nll"
		m_nState = m_nState + (unsigned long long)(nSeed);
#line 22 "../LangShared/Transpiled/Rand/Rand.nll"
		NextUint32();
	}

#line 25 "../LangShared/Transpiled/Rand/Rand.nll"
	unsigned int Rand::NextUint32()
	{
		unsigned long long nOldState = m_nState;
#line 28 "../LangShared/Transpiled/Rand/Rand.nll"
		m_nState = nOldState * MULTIPLIER + m_nInc;
		unsigned int nXorShifted = (unsigned int)(((nOldState >> 18) ^ nOldState) >> 27);
		unsigned int nRot = (unsigned int)(nOldState >> 59);
		unsigned int nRotNeg = (32 - nRot) & 31;
#line 34 "../LangShared/Transpiled/Rand/Rand.nll"
		return (nXorShifted >> nRot) | (nXorShifted << nRotNeg);
	}

#line 37 "../LangShared/Transpiled/Rand/Rand.nll"
	double Rand::NextDouble()
	{
		const double SCALE = 1.0 / 0xFFFFFFFF;
#line 40 "../LangShared/Transpiled/Rand/Rand.nll"
		return NextUint32() * SCALE;
	}

}

