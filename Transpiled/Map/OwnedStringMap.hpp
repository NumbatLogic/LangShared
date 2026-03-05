#pragma once

#include "../../Map/CPP/StringMap.hpp"

namespace NumbatLogic
{
	template <class TValue>
	class StringMap;
}
namespace NumbatLogic
{
	template <class TValue>
	class OwnedStringMap
	{
		protected: StringMap<TValue>* m_pMap;
		public: OwnedStringMap()
		{
			m_pMap = 0;
			m_pMap = new StringMap<TValue>();
		}

		public: virtual ~OwnedStringMap()
		{
			Clear();
			if (m_pMap) delete m_pMap;
		}

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
				{
					delete m_pMap->Get(xKey);
				}
				m_pMap->Remove(xKey);
			}
		}

		public: TValue Remove(const char* xKey)
		{
			if (!m_pMap->Contains(xKey))
				return 0;
			TValue pTemp = m_pMap->Get(xKey);
			m_pMap->Remove(xKey);
			return pTemp;
		}

		public: void Erase(const char* xKey)
		{
			if (!m_pMap->Contains(xKey))
				return;
			{
				delete m_pMap->Get(xKey);
			}
			m_pMap->Remove(xKey);
		}

	};
}

