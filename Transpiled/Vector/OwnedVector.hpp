#pragma once

#include "../../Vector/CPP/Vector.hpp"

namespace NumbatLogic
{
	template <class T>
	class Vector;
}
#line 0 "../LangShared/Transpiled/Vector/OwnedVector.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/Vector/OwnedVector.nll"
	template <class T>
	class OwnedVector
	{
#line 5 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		protected: Vector<T>* m_pVector;
#line 7 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: OwnedVector()
		{
			m_pVector = 0;
#line 9 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			m_pVector = new Vector<T>();
		}

#line 12 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: virtual ~OwnedVector()
		{
#line 14 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			Clear();
			if (m_pVector) delete m_pVector;
		}

#line 17 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: T PushFront(T xObject)
		{
#line 19 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			m_pVector->PushFront(xObject);
#line 20 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			return m_pVector->Get(0);
		}

#line 23 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: T PushBack(T xObject)
		{
#line 25 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			m_pVector->PushBack(xObject);
#line 26 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			return m_pVector->Get(m_pVector->GetSize() - 1);
		}

#line 29 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: int GetSize()
		{
#line 31 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			return m_pVector->GetSize();
		}

#line 34 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: T Get(int nIndex)
		{
#line 36 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			return m_pVector->Get(nIndex);
		}

#line 39 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: void Set(int nIndex, T pObject)
		{
#line 41 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			T pTemp = m_pVector->Get(nIndex);
#line 42 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			if (pTemp != 0)
#line 43 "../LangShared/Transpiled/Vector/OwnedVector.nll"
				{
					delete pTemp;
					pTemp = 0;
				}
#line 44 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			m_pVector->Set(nIndex, pObject);
		}

#line 47 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: void Clear()
		{
#line 49 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			while (m_pVector->GetSize() > 0)
			{
#line 52 "../LangShared/Transpiled/Vector/OwnedVector.nll"
				T pTemp = m_pVector->PopBack();
#line 53 "../LangShared/Transpiled/Vector/OwnedVector.nll"
				if (pTemp != 0)
#line 54 "../LangShared/Transpiled/Vector/OwnedVector.nll"
					{
						delete pTemp;
						pTemp = 0;
					}
			}
		}

#line 58 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: void Insert(int nIndex, T pObject)
		{
#line 60 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			m_pVector->Insert(nIndex, pObject);
		}

#line 63 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: T Remove(int nIndex)
		{
#line 65 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			T pTemp = m_pVector->Get(nIndex);
#line 66 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			m_pVector->Erase(nIndex);
#line 67 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			return pTemp;
		}

#line 70 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: void Erase(int nIndex)
		{
#line 72 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			{
				delete m_pVector->Get(nIndex);
			}
#line 73 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			m_pVector->Erase(nIndex);
		}

#line 76 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: void Swap(int nIndexA, int nIndexB)
		{
#line 78 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			m_pVector->Swap(nIndexA, nIndexB);
		}

#line 81 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: T PopBack()
		{
#line 83 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			return m_pVector->PopBack();
		}

#line 86 "../LangShared/Transpiled/Vector/OwnedVector.nll"
		public: T PopFront()
		{
#line 88 "../LangShared/Transpiled/Vector/OwnedVector.nll"
			return m_pVector->PopFront();
		}

	};
}

