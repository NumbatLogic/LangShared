namespace NumbatLogic
{
	class Vector<T>
	{
		private System.Collections.Generic.List<T> m_pList;


		public Vector()
		{
			Clear();
		}

		public void PushFront(T xObject)
		{
			m_pList.Insert(0, xObject);
		}

		public void PushBack(T xObject)
		{
			m_pList.Add(xObject);
		}

		public int GetSize()
		{
			return m_pList.Count;
		}

		public T Get(int nIndex)
		{
			return m_pList[nIndex];
		}

		public void Clear()
		{
			m_pList = new System.Collections.Generic.List<T>();
		}

		public void Set(int nIndex, T xObject)
		{
			m_pList[nIndex] = xObject;
		}

		public void Insert(int nIndex, T xObject)
		{
			m_pList.Insert(nIndex, xObject);
		}

		public void Erase(int nIndex)
		{
			m_pList.RemoveAt(nIndex);
		}

		public void Swap(int nIndexA, int nIndexB)
		{
			T xTemp = m_pList[nIndexA];
			m_pList[nIndexA] = m_pList[nIndexB];
			m_pList[nIndexB] = xTemp;
		}

		public T PopBack()
		{
			int nIndex = m_pList.Count - 1;
			T xBack = m_pList[nIndex];
			m_pList.RemoveAt(nIndex);
			return xBack;
		}

		public T PopFront()
		{
			T xFront = m_pList[0];
			m_pList.RemoveAt(0);
			return xFront;
		}
	}
}