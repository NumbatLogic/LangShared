#pragma once

#include "../../Vector/CPP/Vector.hpp"

namespace NumbatLogic
{
	template <class T>
	class Vector;
}
#line 1 "../LangShared/Transpiled/Vector/OwnedVector.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/Vector/OwnedVector.nll"
	template <class T>
	class OwnedVector
	{
#line 6 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		protected: Vector<T>* m_pVector;
#line 8 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: OwnedVector()
		{
			m_pVector = 0;
#line 10 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			m_pVector = new Vector<T>();
		}

#line 13 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: virtual ~OwnedVector()
		{
#line 15 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			Clear();
			if (m_pVector) delete m_pVector;
		}

#line 18 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: T PushFront(T xObject)
		{
#line 20 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			m_pVector->PushFront(xObject);
#line 21 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			return m_pVector->Get(0);
		}

#line 24 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: T PushBack(T xObject)
		{
#line 26 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			m_pVector->PushBack(xObject);
#line 27 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			return m_pVector->Get(m_pVector->GetSize() - 1);
		}

#line 30 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: int GetSize()
		{
#line 32 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			return m_pVector->GetSize();
		}

#line 35 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: T Get(int nIndex)
		{
#line 37 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			return m_pVector->Get(nIndex);
		}

#line 40 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: void Set(int nIndex, T pObject)
		{
			T pTemp = m_pVector->Get(nIndex);
#line 43 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			if (pTemp != 0)
#line 44 "../LangShared/Transpiled/Vector/OwnedVector.nll"
				{
					delete pTemp;
					pTemp = 0;
				}
#line 45 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			m_pVector->Set(nIndex, pObject);
		}

#line 48 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: void Clear()
		{
#line 50 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			while (m_pVector->GetSize() > 0)
			{
				T pTemp = m_pVector->PopBack();
#line 54 "../LangShared/Transpiled/Vector/OwnedVector.nll"
				if (pTemp != 0)
#line 55 "../LangShared/Transpiled/Vector/OwnedVector.nll"
					{
						delete pTemp;
						pTemp = 0;
					}
			}
		}

#line 59 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: void Insert(int nIndex, T pObject)
		{
#line 61 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			m_pVector->Insert(nIndex, pObject);
		}

#line 64 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: T Remove(int nIndex)
		{
			T pTemp = m_pVector->Get(nIndex);
#line 67 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			m_pVector->Erase(nIndex);
#line 68 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			return pTemp;
		}

#line 71 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: void Erase(int nIndex)
		{
#line 73 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			{
				delete m_pVector->Get(nIndex);
			}
#line 74 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			m_pVector->Erase(nIndex);
		}

#line 77 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: void Swap(int nIndexA, int nIndexB)
		{
#line 79 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			m_pVector->Swap(nIndexA, nIndexB);
		}

#line 82 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: T PopBack()
		{
#line 84 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			return m_pVector->PopBack();
		}

#line 87 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: T PopFront()
		{
#line 89 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			return m_pVector->PopFront();
		}

	};
}

