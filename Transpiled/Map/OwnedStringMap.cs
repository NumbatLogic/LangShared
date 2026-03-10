#line 1 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
namespace NumbatLogic
{
#line 4 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
	class OwnedStringMap<TValue> where TValue : class
	{
#line 6 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		protected StringMap<TValue> m_pMap;
#line 8 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public OwnedStringMap()
		{
#line 10 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			m_pMap = new StringMap<TValue>();
		}

#line 13 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		~OwnedStringMap()
		{
#line 15 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			Clear();
		}

#line 18 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public TValue Set(string xKey, TValue pObject)
		{
#line 20 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			if (m_pMap.Contains(xKey))
			{
				TValue pOld = m_pMap.Get(xKey);
#line 23 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
				if (pOld != null)
#line 24 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
					{
						pOld = null;
					}
			}
#line 27 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			m_pMap.Set(xKey, pObject);
#line 28 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			return m_pMap.Get(xKey);
		}

#line 31 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public int GetSize()
		{
#line 33 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			return m_pMap.GetSize();
		}

#line 36 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public TValue Get(string xKey)
		{
#line 38 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			return m_pMap.Get(xKey);
		}

#line 41 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public bool Contains(string xKey)
		{
#line 43 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			return m_pMap.Contains(xKey);
		}

#line 46 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public void Clear()
		{
#line 48 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			while (m_pMap.GetSize() > 0)
			{
				string xKey = m_pMap.GetAnyKey();
#line 51 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
				if (xKey == null)
#line 52 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
					break;
#line 54 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
				{
				}
#line 55 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
				m_pMap.Remove(xKey);
			}
		}

#line 59 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public TValue Remove(string xKey)
		{
#line 61 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			if (!m_pMap.Contains(xKey))
#line 62 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
				return null;
			TValue pTemp = m_pMap.Get(xKey);
#line 65 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			m_pMap.Remove(xKey);
#line 66 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			return pTemp;
		}

#line 69 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public void Erase(string xKey)
		{
#line 71 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			if (!m_pMap.Contains(xKey))
#line 72 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
				return;
#line 74 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			{
			}
#line 75 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			m_pMap.Remove(xKey);
		}

	}
}

