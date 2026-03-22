#pragma once

#include "../../Source/Map/CPP/StringMap.hpp"

namespace NumbatLogic
{
	template <class TValue>
	class StringMap;
}
#line 0 "/home/cliffya/git/LangShared/Source/Map/OwnedStringMap.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/LangShared/Source/Map/OwnedStringMap.nll"
	template <class TValue>
	class OwnedStringMap
	{
#line 5 "/home/cliffya/git/LangShared/Source/Map/OwnedStringMap.nll"
		protected: StringMap<TValue>* m_pMap;
#line 7 "/home/cliffya/git/LangShared/Source/Map/OwnedStringMap.nll"
		public: OwnedStringMap()
		{
			m_pMap = 0;
#line 9 "/home/cliffya/git/LangShared/Source/Map/OwnedStringMap.nll"
			m_pMap = new StringMap<TValue>();
		}

		public: virtual ~OwnedStringMap()
		{
			Clear();
			if (m_pMap) delete m_pMap;
		}

#line 17 "/home/cliffya/git/LangShared/Source/Map/OwnedStringMap.nll"
		public: TValue Set(const char* xKey, TValue pObject)
		{
			if (m_pMap->Contains(xKey))
			{
				TValue pOld = m_pMap->Get(xKey);
				if (pOld != 0)
					{
						delete pOld;
						pOld = 0;
					}
			}
#line 26 "/home/cliffya/git/LangShared/Source/Map/OwnedStringMap.nll"
			m_pMap->Set(xKey, pObject);
			return m_pMap->Get(xKey);
		}

		public: int GetSize()
		{
			return m_pMap->GetSize();
		}

		public: TValue Get(const char* xKey)
		{
			return m_pMap->Get(xKey);
		}

		public: bool Contains(const char* xKey)
		{
			return m_pMap->Contains(xKey);
		}

		public: void Clear()
		{
			while (m_pMap->GetSize() > 0)
			{
				const char* xKey = m_pMap->GetAnyKey();
				if (xKey == 0)
					break;
#line 53 "/home/cliffya/git/LangShared/Source/Map/OwnedStringMap.nll"
				{
					delete m_pMap->Get(xKey);
				}
#line 54 "/home/cliffya/git/LangShared/Source/Map/OwnedStringMap.nll"
				m_pMap->Remove(xKey);
			}
		}

		public: TValue Remove(const char* xKey)
		{
			if (!m_pMap->Contains(xKey))
				return 0;
#line 63 "/home/cliffya/git/LangShared/Source/Map/OwnedStringMap.nll"
			TValue pTemp = m_pMap->Get(xKey);
			m_pMap->Remove(xKey);
			return pTemp;
		}

		public: void Erase(const char* xKey)
		{
			if (!m_pMap->Contains(xKey))
				return;
#line 73 "/home/cliffya/git/LangShared/Source/Map/OwnedStringMap.nll"
			{
				delete m_pMap->Get(xKey);
			}
#line 74 "/home/cliffya/git/LangShared/Source/Map/OwnedStringMap.nll"
			m_pMap->Remove(xKey);
		}

	};
}

