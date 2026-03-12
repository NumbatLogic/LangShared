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

	void Rand::Seed(unsigned int nSeed)
	{
		m_nState = 0;
		m_nInc = ((unsigned long long)(nSeed) << 1) | 1;
		NextUint32();
		m_nState = m_nState + (unsigned long long)(nSeed);
		NextUint32();
	}

	unsigned int Rand::NextUint32()
	{
		unsigned long long nOldState = m_nState;
		m_nState = nOldState * MULTIPLIER + m_nInc;
#line 29 "../LangShared/Transpiled/Rand/Rand.nll"
		unsigned int nXorShifted = (unsigned int)(((nOldState >> 18) ^ nOldState) >> 27);
		int nRot = (int)(nOldState >> 59);
		int nRotNeg = (32 - nRot) & 31;
#line 33 "../LangShared/Transpiled/Rand/Rand.nll"
		return (nXorShifted >> nRot) | (nXorShifted << nRotNeg);
	}

	double Rand::NextDouble()
	{
		const double SCALE = 1.0 / 0xFFFFFFFF;
		return NextUint32() * SCALE;
	}

}

