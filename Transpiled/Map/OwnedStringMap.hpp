#pragma once

#include "../../Map/CPP/StringMap.hpp"

namespace NumbatLogic
{
	template <class TValue>
	class StringMap;
}
#line 0 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
namespace NumbatLogic
{
#line 3 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
	template <class TValue>
	class OwnedStringMap
	{
#line 5 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		protected: StringMap<TValue>* m_pMap;
#line 7 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public: OwnedStringMap()
		{
			m_pMap = 0;
#line 9 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			m_pMap = new StringMap<TValue>();
		}

#line 12 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public: virtual ~OwnedStringMap()
		{
#line 14 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			Clear();
			if (m_pMap) delete m_pMap;
		}

#line 17 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public: TValue Set(const char* xKey, TValue pObject)
		{
#line 19 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			if (m_pMap->Contains(xKey))
			{
#line 21 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
				TValue pOld = m_pMap->Get(xKey);
#line 22 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
				if (pOld != 0)
#line 23 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
					{
						delete pOld;
						pOld = 0;
					}
			}
#line 26 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			m_pMap->Set(xKey, pObject);
#line 27 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			return m_pMap->Get(xKey);
		}

#line 30 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public: int GetSize()
		{
#line 32 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			return m_pMap->GetSize();
		}

#line 35 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public: TValue Get(const char* xKey)
		{
#line 37 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			return m_pMap->Get(xKey);
		}

#line 40 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public: bool Contains(const char* xKey)
		{
#line 42 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			return m_pMap->Contains(xKey);
		}

#line 45 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public: void Clear()
		{
#line 47 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			while (m_pMap->GetSize() > 0)
			{
#line 49 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
				const char* xKey = m_pMap->GetAnyKey();
#line 50 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
				if (xKey == 0)
#line 51 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
					break;
#line 53 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
				{
					delete m_pMap->Get(xKey);
				}
#line 54 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
				m_pMap->Remove(xKey);
			}
		}

#line 58 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public: TValue Remove(const char* xKey)
		{
#line 60 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			if (!m_pMap->Contains(xKey))
#line 61 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
				return 0;
#line 63 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			TValue pTemp = m_pMap->Get(xKey);
#line 64 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			m_pMap->Remove(xKey);
#line 65 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			return pTemp;
		}

#line 68 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public: void Erase(const char* xKey)
		{
#line 70 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			if (!m_pMap->Contains(xKey))
#line 71 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
				return;
#line 73 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			{
				delete m_pMap->Get(xKey);
			}
#line 74 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			m_pMap->Remove(xKey);
		}

	};
}

