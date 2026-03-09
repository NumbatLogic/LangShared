#pragma once

#line 1 "../LangShared/Transpiled/Rand/Rand.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/Rand/Rand.nll"
	class Rand
	{
#line 7 "../LangShared/Transpiled/Rand/Rand.nll"
		protected: static const unsigned long long MULTIPLIER = 0x5851f42d4c957f2d;
#line 8 "../LangShared/Transpiled/Rand/Rand.nll"
		protected: unsigned long long m_nState;
#line 9 "../LangShared/Transpiled/Rand/Rand.nll"
		protected: unsigned long long m_nInc;
#line 11 "../LangShared/Transpiled/Rand/Rand.nll"
		public: Rand(unsigned int nSeed);
#line 16 "../LangShared/Transpiled/Rand/Rand.nll"
		public: void Seed(unsigned int nSeed);
#line 25 "../LangShared/Transpiled/Rand/Rand.nll"
		public: unsigned int NextUint32();
#line 37 "../LangShared/Transpiled/Rand/Rand.nll"
		public: double NextDouble();
	};
}

