#pragma once

#include <vector>

namespace NumbatLogic
{
	template <class T>
	class Vector
	{
		public:
			Vector() {
				m_pVector = new std::vector<T>();
			}

			~Vector()
			{
				delete m_pVector;
			}

			void PushFront(T xObject)
			{
				m_pVector->insert(m_pVector->begin(), xObject);
			}

			void PushBack(T xObject)
			{
				m_pVector->push_back(xObject);
			}

			T PopBack()
			{
				T xBack = m_pVector->back();
				m_pVector->pop_back();
				return xBack;
			}

			T PopFront()
			{
				T xFront = (*m_pVector)[0];
				m_pVector->erase(m_pVector->begin());
				return xFront;
			}

			int GetSize()
			{
				return (int)m_pVector->size();
			}

			T Get(int nIndex)
			{
				return (*m_pVector)[nIndex];
			}

			T GetBack()
			{
				return m_pVector->back();
			}

			void Set(int nIndex, T xObject)
			{
				(*m_pVector)[nIndex] = xObject;
			}

			void Insert(int nIndex, T xObject)
			{
				m_pVector->insert(m_pVector->begin() + nIndex, xObject);
			}

			void Clear()
			{
				m_pVector->clear();
			}

			void Erase(int nIndex)
			{
				m_pVector->erase(m_pVector->begin() + nIndex);
			}

		protected:
			std::vector<T>* m_pVector;		
	};
}