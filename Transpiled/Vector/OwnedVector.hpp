#pragma once

#include "../../Vector/CPP/Vector.hpp"

namespace NumbatLogic
{
	template <class T>
	class Vector;
}
namespace NumbatLogic
{
	template <class T>
	class OwnedVector
	{
		protected: Vector<T>* m_pVector;
		public: OwnedVector()
		{
			m_pVector = 0;
			m_pVector = new Vector<T>();
		}

		public: virtual ~OwnedVector()
		{
			Clear();
			if (m_pVector) delete m_pVector;
		}

		public: T PushFront(T xObject)
		{
			m_pVector->PushFront(xObject);
			return m_pVector->Get(0);
		}

		public: T PushBack(T xObject)
		{
			m_pVector->PushBack(xObject);
			return m_pVector->Get(m_pVector->GetSize() - 1);
		}

		public: int GetSize()
		{
			return m_pVector->GetSize();
		}

		public: T Get(int nIndex)
		{
			return m_pVector->Get(nIndex);
		}

		public: void Set(int nIndex, T pObject)
		{
			T pTemp = m_pVector->Get(nIndex);
			if (pTemp != 0)
				{
					delete pTemp;
					pTemp = 0;
				}
			m_pVector->Set(nIndex, pObject);
		}

		public: void Clear()
		{
			while (m_pVector->GetSize() > 0)
			{
				T pTemp = m_pVector->PopBack();
				if (pTemp != 0)
					{
						delete pTemp;
						pTemp = 0;
					}
			}
		}

		public: void Insert(int nIndex, T pObject)
		{
			m_pVector->Insert(nIndex, pObject);
		}

		public: T Remove(int nIndex)
		{
			T pTemp = m_pVector->Get(nIndex);
			m_pVector->Erase(nIndex);
			return pTemp;
		}

		public: void Erase(int nIndex)
		{
			{
				delete m_pVector->Get(nIndex);
			}
			m_pVector->Erase(nIndex);
		}

		public: void Swap(int nIndexA, int nIndexB)
		{
			m_pVector->Swap(nIndexA, nIndexB);
		}

		public: T PopBack()
		{
			return m_pVector->PopBack();
		}

		public: T PopFront()
		{
			return m_pVector->PopFront();
		}

	};
}

