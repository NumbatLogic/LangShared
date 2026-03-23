using System;
using System.Text;
using System.Text.Json;
using System.Text.Json.Nodes;

namespace NumbatLogic
{
	public class Json
	{
		private JsonNode m_pOwnedNode;
		private JsonNode m_pNode;

		private Json m_pPrevious;
		private Json m_pNext;
		private Json m_pChild;

		private string m_sName;

		public Json()
		{
			Cleanup();
		}

		private Json(JsonNode pNode, Json pPrevious, string sName)
		{
			m_pOwnedNode = null;
			m_pNode = pNode;
			m_pPrevious = pPrevious;
			m_pNext = null;
			m_pChild = null;
			m_sName = sName;

			RecursiveCreate();
		}

		public bool LoadFromExternalString(string sxIn)
		{
			Cleanup();

			if (sxIn == null)
				return false;

			try
			{
				JsonNode pNode = JsonNode.Parse(sxIn);
				if (pNode == null)
					return false;

				m_pOwnedNode = pNode;
				m_pNode = pNode;
				m_sName = null;

				RecursiveCreate();
				return true;
			}
			catch (Exception)
			{
				return false;
			}
		}

		public bool LoadFromPath(string sxPath)
		{
			bool bSuccess = false;
			gsBlob pBlob = new gsBlob();

			if (!pBlob.Load(sxPath))
				goto CleanupLabel;

			pBlob.SetOffset(0);
			if (!LoadFromBlob(pBlob))
				goto CleanupLabel;

			bSuccess = true;

		CleanupLabel:
			pBlob = null;
			return bSuccess;
		}

		public bool LoadFromBlob(gsBlob pBlob)
		{
			if (pBlob == null || pBlob.__pBuffer == null)
				return false;

			int nOffset = pBlob.GetOffset();
			int nSizeAvailable = pBlob.GetSize() - nOffset;
			if (nSizeAvailable <= 0)
				return false;

			string sxIn = Encoding.UTF8.GetString(pBlob.__pBuffer, nOffset, nSizeAvailable);
			return LoadFromExternalString(sxIn);
		}

		public Json GetNext()
		{
			return m_pNext;
		}

		public Json GetChild()
		{
			return m_pChild;
		}

		public bool IsString()
		{
			if (m_pNode is JsonValue jsonValue)
			{
				string s;
				return jsonValue.TryGetValue<string>(out s);
			}
			return false;
		}

		public bool IsNumber()
		{
			if (m_pNode is JsonValue jsonValue)
			{
				double d;
				return jsonValue.TryGetValue<double>(out d);
			}
			return false;
		}

		public bool IsBool()
		{
			if (m_pNode is JsonValue jsonValue)
			{
				bool b;
				return jsonValue.TryGetValue<bool>(out b);
			}
			return false;
		}

		public bool IsObject()
		{
			return m_pNode is JsonObject;
		}

		public bool IsArray()
		{
			return m_pNode is JsonArray;
		}

		public string GetString()
		{
			if (m_pNode is JsonValue jsonValue)
			{
				string s;
				if (jsonValue.TryGetValue<string>(out s))
					return s;
			}
			return null;
		}

		public double GetNumber()
		{
			if (m_pNode is JsonValue jsonValue)
			{
				double d;
				if (jsonValue.TryGetValue<double>(out d))
					return d;
			}
			return 0.0;
		}

		public bool GetBool()
		{
			if (m_pNode is JsonValue jsonValue)
			{
				bool b;
				if (jsonValue.TryGetValue<bool>(out b))
					return b;
			}
			return false;
		}

		public Json GetField(string sxName)
		{
			if (!IsObject() || sxName == null)
				return null;

			Json pJson = m_pChild;
			while (pJson != null)
			{
				if (ExternalString.Equal(pJson.m_sName, sxName))
					return pJson;
				pJson = pJson.m_pNext;
			}
			return null;
		}

		private bool RecursiveCreate()
		{
			if (m_pNode == null)
				return false;

			Json firstChild = null;
			Json previousChild = null;

			if (m_pNode is JsonObject jsonObject)
			{
				foreach (var kvp in jsonObject)
				{
					Json child = new Json(kvp.Value, previousChild, kvp.Key);
					if (firstChild == null)
						firstChild = child;

					if (previousChild != null)
						previousChild.m_pNext = child;

					previousChild = child;
				}
			}
			else if (m_pNode is JsonArray jsonArray)
			{
				for (int i = 0; i < jsonArray.Count; i++)
				{
					Json child = new Json(jsonArray[i], previousChild, null);
					if (firstChild == null)
						firstChild = child;

					if (previousChild != null)
						previousChild.m_pNext = child;

					previousChild = child;
				}
			}

			m_pChild = firstChild;
			return true;
		}

		private void Cleanup()
		{
			m_pOwnedNode = null;
			m_pNode = null;
			m_pPrevious = null;
			m_pNext = null;
			m_pChild = null;
			m_sName = null;
		}
	}
}

