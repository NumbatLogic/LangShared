#include "../../Assert/CPP/Assert.hpp"
#include "../../InternalString/CPP/InternalString.hpp"
#include "../../ExternalString/CPP/ExternalString.hpp"
#include "../../Blob/CPP/Blob.hpp"
#include "Json.hpp"

#include <cstdio>

namespace NumbatLogic
{
	Json::Json()
	{
		m_pOwnedJson = NULL;
		m_pJson = NULL;
		m_pNext = NULL;
		m_pPrevious = NULL;
		m_pChild = NULL;
	}

	Json::Json(cJSON* pJson, Json* pPrevious)
	{
		Assert::Plz(pJson);

		m_pOwnedJson = NULL;
		m_pJson = pJson;
		m_pPrevious = pPrevious;
		m_pNext = NULL;
		m_pChild = NULL;

		RecursiveCreate();
	}

	Json::~Json()
	{
		Cleanup();
	}

	bool Json::LoadFromExternalString(const char* szIn)
	{
		Cleanup();

		if (szIn != 0)
		{
			m_pOwnedJson = cJSON_Parse(szIn);
			m_pJson = m_pOwnedJson;

			if (RecursiveCreate())
				return true;
		}

		return false;
	}

	bool Json::LoadFromPath(const char* sxPath)
	{
		bool bSuccess = false;
		gsBlob* pBlob = new gsBlob();
		
		if (!pBlob->Load(sxPath))
			goto Cleanup;
		pBlob->SetOffset(pBlob->GetSize());
		pBlob->PackUint8('\0');
		if (!LoadFromExternalString((const char*)pBlob->GetData()))
			goto Cleanup;

		bSuccess = true;
		goto Cleanup;
		
		Cleanup:
			delete pBlob;
			return bSuccess;
	}

	bool Json::LoadFromBlob(gsBlob* pBlob)
	{
		if (!pBlob)
			return false;
		return LoadFromExternalString((const char*)pBlob->GetData());
	}

	Json* Json::GetNext()
	{
		return m_pNext;
	}

	Json* Json::GetChild()
	{
		return m_pChild;
	}

	bool Json::IsString() { return cJSON_IsString(m_pJson); }
	bool Json::IsNumber() { return cJSON_IsNumber(m_pJson); }
	bool Json::IsBool() { return cJSON_IsBool(m_pJson); }
	bool Json::IsObject() { return cJSON_IsObject(m_pJson); }
	bool Json::IsArray() { return cJSON_IsArray(m_pJson); }

	const char* Json::GetString() { return cJSON_GetStringValue(m_pJson); }
	double Json::GetNumber() { return cJSON_GetNumberValue(m_pJson); }
	bool Json::GetBool() { return cJSON_IsTrue(m_pJson); }

	Json* Json::GetField(const char* szName)
	{
		if (IsObject())
		{
			Json* pJson = m_pChild;
			while (pJson)
			{
				if (ExternalString::Equal(pJson->m_pJson->string, szName))
					return pJson;
				pJson = pJson->m_pNext;
			}
		}
		return NULL;
	}

	bool Json::RecursiveCreate()
	{
		if (!m_pJson)
			return false;

		if (m_pJson->next)
			m_pNext = new Json(m_pJson->next, this);
		
		if (m_pJson->child)
			m_pChild = new Json(m_pJson->child, NULL);

		return true;
	}
	
	void Json::Cleanup()
	{
		if (m_pOwnedJson)
			cJSON_Delete(m_pOwnedJson);
		m_pOwnedJson = NULL;
		m_pJson = NULL;
		if (m_pNext)
			delete m_pNext;
		m_pNext = NULL;
		m_pPrevious = NULL;

		if (m_pChild)
			delete m_pChild;
		m_pChild = NULL;
	}
}
