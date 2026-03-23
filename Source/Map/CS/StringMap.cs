namespace NumbatLogic
{
	public class StringMap<TValue>
	{
		private System.Collections.Generic.Dictionary<string, TValue> m_pDict;

		public StringMap()
		{
			Clear();
		}

		public void Set(string xKey, TValue xValue)
		{
			m_pDict[xKey] = xValue;
		}

		public TValue Get(string xKey)
		{
			return m_pDict[xKey];
		}

		public string GetAnyKey()
		{
			foreach (var kv in m_pDict)
			{
				return kv.Key;
			}
			return null;
		}

		public bool Contains(string xKey)
		{
			return m_pDict.ContainsKey(xKey);
		}

		public void Remove(string xKey)
		{
			m_pDict.Remove(xKey);
		}

		public void Clear()
		{
			m_pDict = new System.Collections.Generic.Dictionary<string, TValue>();
		}

		public int GetSize()
		{
			return m_pDict.Count;
		}
	}
}

