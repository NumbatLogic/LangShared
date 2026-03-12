#pragma once

#line 0 "../LangShared/Transpiled/Rand/Rand.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/Rand/Rand.nll"
	class Rand
	{
#line 6 "../LangShared/Transpiled/Rand/Rand.nll"
		protected: static const unsigned long long MULTIPLIER = 0x5851f42d4c957f2d;
		protected: unsigned long long m_nState;
		protected: unsigned long long m_nInc;
#line 10 "../LangShared/Transpiled/Rand/Rand.nll"
		public: Rand(unsigned int nSeed);
#line 15 "../LangShared/Transpiled/Rand/Rand.nll"
		public: void Seed(unsigned int nSeed);
#line 24 "../LangShared/Transpiled/Rand/Rand.nll"
		public: unsigned int NextUint32();
#line 36 "../LangShared/Transpiled/Rand/Rand.nll"
		public: double NextDouble();
	};
}

