#pragma once

#include <string>
#include <vector>
#include <utility>



namespace NumbatLogic
{
	class InternalString;

	class HttpGet
	{
		public:
			HttpGet(const char* sxUrl);
			~HttpGet();
			
			void AddHeader(const char* sxName, const char* sxValue);
			const char* Execute();

		private:
			std::string m_sUrl;
			std::vector<std::pair<std::string, std::string>> m_headers;
	};

	class HttpPost
	{
		public:
			HttpPost(const char* sxUrl);
			~HttpPost();
			
			void AddHeader(const char* sxName, const char* sxValue);
			void SetBody(const char* sxBody);
			void SetUsername(const char* sxUsername);
			void SetPassword(const char* sxPassword);

			const char* Execute();

		private:
			std::string m_sUrl;
			std::vector<std::pair<std::string, std::string>> m_headers;
			std::string m_sBody;

			InternalString* m_sUsername;
			InternalString* m_sPassword;
	};
} 