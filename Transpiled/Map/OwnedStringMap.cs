namespace NumbatLogic
{
	class OwnedStringMap<TValue> where TValue : class
	{
		protected StringMap<TValue> m_pMap;
		public OwnedStringMap()
		{
			m_pMap = new StringMap<TValue>();
		}

		~OwnedStringMap()
		{
			Clear();
		}

		public TValue Set(string xKey, TValue pObject)
		{
			if (m_pMap.Contains(xKey))
			{
				TValue pOld = m_pMap.Get(xKey);
				if (pOld != null)
					{
						pOld = null;
					}
			}
			m_pMap.Set(xKey, pObject);
			return m_pMap.Get(xKey);
		}

		public int GetSize()
		{
			return m_pMap.GetSize();
		}

		public TValue Get(string xKey)
		{
			return m_pMap.Get(xKey);
		}

		public bool Contains(string xKey)
		{
			return m_pMap.Contains(xKey);
		}

		public void Clear()
		{
			while (m_pMap.GetSize() > 0)
			{
				string xKey = m_pMap.GetAnyKey();
				if (xKey == null)
					break;
				{
				}
				m_pMap.Remove(xKey);
			}
		}

		public TValue Remove(string xKey)
		{
			if (!m_pMap.Contains(xKey))
				return null;
			TValue pTemp = m_pMap.Get(xKey);
			m_pMap.Remove(xKey);
			return pTemp;
		}

		public void Erase(string xKey)
		{
			if (!m_pMap.Contains(xKey))
				return;
			{
			}
			m_pMap.Remove(xKey);
		}

	}
}

