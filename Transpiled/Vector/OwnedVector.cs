namespace NumbatLogic
{
	class OwnedVector<T> where T : class
	{
		protected Vector<T> m_pVector;
		public OwnedVector()
		{
			m_pVector = new Vector<T>();
		}

		~OwnedVector()
		{
			Clear();
		}

		public T PushFront(T xObject)
		{
			m_pVector.PushFront(xObject);
			return m_pVector.Get(0);
		}

		public T PushBack(T xObject)
		{
			m_pVector.PushBack(xObject);
			return m_pVector.Get(m_pVector.GetSize() - 1);
		}

		public int GetSize()
		{
			return m_pVector.GetSize();
		}

		public T Get(int nIndex)
		{
			return m_pVector.Get(nIndex);
		}

		public void Clear()
		{
			while (m_pVector.GetSize() > 0)
			{
				T pTemp = m_pVector.PopBack();
				if (pTemp != null)
					{
						pTemp = null;
					}
			}
		}

		public void Insert(int nIndex, T pObject)
		{
			m_pVector.Insert(nIndex, pObject);
		}

		public T Remove(int nIndex)
		{
			T pTemp = m_pVector.Get(nIndex);
			m_pVector.Erase(nIndex);
			return pTemp;
		}

		public void Erase(int nIndex)
		{
			{
			}
			m_pVector.Erase(nIndex);
		}

		public T PopBack()
		{
			return m_pVector.PopBack();
		}

		public T PopFront()
		{
			return m_pVector.PopFront();
		}

	}
}

