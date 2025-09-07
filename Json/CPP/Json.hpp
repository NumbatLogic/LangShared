#pragma once

#include "cJSON/cJSON.h"

namespace NumbatLogic
{
	class Json
	{
		public:
			Json();
			Json(cJSON* pJson, Json* pPrevious);
			~Json();

			bool LoadFromExternalString(const char* szIn);
		
			Json* GetNext();
			Json* GetChild();

			bool IsString();
			bool IsNumber();
			bool IsBool();
			bool IsObject();
			bool IsArray();

			const char* GetString();
			double GetNumber();
			bool GetBool();

			Json* GetField(const char* szName);

		protected:
			bool RecursiveCreate();
			void Cleanup();

			cJSON* m_pOwnedJson;
			cJSON* m_pJson;

			Json* m_pPrevious;
			Json* m_pNext;
			Json* m_pChild;
	};
}
