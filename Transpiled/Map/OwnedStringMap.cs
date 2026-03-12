#line 1 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
namespace NumbatLogic
{
#line 3 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
	class OwnedStringMap<TValue> where TValue : class
	{
#line 5 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		protected StringMap<TValue> m_pMap;
#line 7 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public OwnedStringMap()
		{
#line 9 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			m_pMap = new StringMap<TValue>();
		}

#line 12 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		~OwnedStringMap()
		{
#line 14 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			Clear();
		}

#line 17 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public TValue Set(string xKey, TValue pObject)
		{
#line 19 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			if (m_pMap.Contains(xKey))
			{
#line 21 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
				TValue pOld = m_pMap.Get(xKey);
#line 22 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
				if (pOld != null)
#line 23 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
					{
						pOld = null;
					}
			}
#line 26 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			m_pMap.Set(xKey, pObject);
#line 27 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			return m_pMap.Get(xKey);
		}

#line 30 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public int GetSize()
		{
#line 32 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			return m_pMap.GetSize();
		}

#line 35 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public TValue Get(string xKey)
		{
#line 37 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			return m_pMap.Get(xKey);
		}

#line 40 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public bool Contains(string xKey)
		{
#line 42 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			return m_pMap.Contains(xKey);
		}

#line 45 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public void Clear()
		{
#line 47 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			while (m_pMap.GetSize() > 0)
			{
#line 49 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
				string xKey = m_pMap.GetAnyKey();
#line 50 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
				if (xKey == null)
#line 51 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
					break;
#line 53 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
				{
				}
#line 54 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
				m_pMap.Remove(xKey);
			}
		}

#line 58 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public TValue Remove(string xKey)
		{
#line 60 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			if (!m_pMap.Contains(xKey))
#line 61 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
				return null;
#line 63 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			TValue pTemp = m_pMap.Get(xKey);
#line 64 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			m_pMap.Remove(xKey);
#line 65 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			return pTemp;
		}

#line 68 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
		public void Erase(string xKey)
		{
#line 70 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			if (!m_pMap.Contains(xKey))
#line 71 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
				return;
#line 73 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			{
			}
#line 74 "../../../../LangShared/Transpiled/Map/OwnedStringMap.nll"
			m_pMap.Remove(xKey);
		}

	}
}

