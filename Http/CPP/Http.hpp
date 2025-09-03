#pragma once

#include <string>
#include <vector>
#include <utility>

namespace NumbatLogic
{
	class HttpGet
	{
		public:
			HttpGet(const char* sUrl);
			~HttpGet();
			
			void AddHeader(const char* sName, const char* sValue);
			const char* Execute();

		private:
			std::string m_sUrl;
			std::vector<std::pair<std::string, std::string>> m_headers;
	};

	class HttpPost
	{
		public:
			HttpPost(const char* sUrl);
			~HttpPost();
			
			void AddHeader(const char* sName, const char* sValue);
			void SetBody(const char* sBody);
			const char* Execute();

		private:
			std::string m_sUrl;
			std::vector<std::pair<std::string, std::string>> m_headers;
			std::string m_sBody;
	};
} 