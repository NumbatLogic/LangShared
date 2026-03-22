#pragma once

#include <map>
#include <cstring>

namespace NumbatLogic
{
	template <class TValue>
	class StringMap
	{
		public:
			StringMap()
			{
				m_pMap = new std::map<const char*, TValue, Cmp>();
			}

			~StringMap()
			{
				delete m_pMap;
			}

			void Set(const char* xKey, TValue xValue)
			{
				(*m_pMap)[xKey] = xValue;
			}

			const char* GetAnyKey()
			{
				if (m_pMap->empty())
					return 0;
				return m_pMap->begin()->first;
			}

			TValue Get(const char* xKey)
			{
				typename std::map<const char*, TValue, Cmp>::iterator it = m_pMap->find(xKey);
				if (it != m_pMap->end())
				{
					return it->second;
				}
				return TValue();
			}

			bool Contains(const char* xKey)
			{
				return m_pMap->find(xKey) != m_pMap->end();
			}

			void Remove(const char* xKey)
			{
				m_pMap->erase(xKey);
			}

			void Clear()
			{
				m_pMap->clear();
			}

			int GetSize()
			{
				return (int)m_pMap->size();
			}

		protected:
			struct Cmp
			{
				bool operator()(const char* a, const char* b) const
				{
					if (a == b) return false;
					if (!a) return true;
					if (!b) return false;
					return std::strcmp(a, b) < 0;
				}
			};

			std::map<const char*, TValue, Cmp>* m_pMap;
	};
}

