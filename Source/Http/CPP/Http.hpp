#pragma once

#include <string>
#include <vector>
#include <utility>



namespace NumbatLogic
{
	class InternalString;
	class HttpClient
	{
		public:
			HttpClient();
			~HttpClient();

			void* GetHandle() const;

		private:
			void* m_pHandle;
	};

	class HttpGet
	{
		public:
			HttpGet(const char* sxUrl);
			~HttpGet();
			
			void AddHeader(const char* sxName, const char* sxValue);
			const char* Execute();
			const char* Execute(HttpClient* pClient);
			int GetLastStatusCode() const;

		private:
			std::string m_sUrl;
			std::vector<std::pair<std::string, std::string>> m_headers;
			long m_nLastStatusCode;
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
			const char* Execute(HttpClient* pClient);
			int GetLastStatusCode() const;

		private:
			std::string m_sUrl;
			std::vector<std::pair<std::string, std::string>> m_headers;
			std::string m_sBody;
			long m_nLastStatusCode;

			InternalString* m_sUsername;
			InternalString* m_sPassword;

			InternalString* m_sTemp;
	};

	class HttpPostMultipart
	{
		public:
			HttpPostMultipart(const char* sxUrl);
			~HttpPostMultipart();

			void AddHeader(const char* sxName, const char* sxValue);
			void AddField(const char* sxName, const char* sxValue);
			void AddFile(const char* sxName, const char* sxPath, const char* sxContentType);

			const char* Execute();
			const char* Execute(HttpClient* pClient);
			int GetLastStatusCode() const;

		private:
			std::string m_sUrl;
			std::vector<std::pair<std::string, std::string>> m_headers;
			std::vector<std::pair<std::string, std::string>> m_fields;

			struct FilePart
			{
				std::string name;
				std::string path;
				std::string contentType;
			};
			std::vector<FilePart> m_files;

			long m_nLastStatusCode;
			InternalString* m_sTemp;
	};
} 