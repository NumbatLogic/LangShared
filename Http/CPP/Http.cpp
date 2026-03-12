#include "Http.hpp"

#include "../../InternalString/CPP/InternalString.hpp"
#include "../../Assert/CPP/Assert.hpp"

#include <curl/curl.h>
#include <cstring>
#include <iostream>

namespace NumbatLogic
{
	// Static callback function for libcurl
	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp)
	{
		userp->append((char*)contents, size * nmemb);
		return size * nmemb;
	}

	// HttpGet implementation
	HttpGet::HttpGet(const char* sUrl)
	{
		m_sUrl = sUrl ? sUrl : "";
		m_nLastStatusCode = 0;
	}

	HttpGet::~HttpGet()
	{
	}

	void HttpGet::AddHeader(const char* sName, const char* sValue)
	{
		if (sName && sValue)
		{
			m_headers.push_back(std::make_pair(std::string(sName), std::string(sValue)));
		}
	}

	const char* HttpGet::Execute()
	{
		CURL* curl = curl_easy_init();
		if (!curl)
		{
			m_nLastStatusCode = 0;
			return nullptr;
		}

		std::string response;
		struct curl_slist* headers = nullptr;

		// Add custom headers
		for (const auto& header : m_headers)
		{
			std::string headerLine = header.first + ": " + header.second;
			headers = curl_slist_append(headers, headerLine.c_str());
		}

		curl_easy_setopt(curl, CURLOPT_URL, m_sUrl.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L); // 30 second timeout
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Follow redirects

		CURLcode res = curl_easy_perform(curl);
		
		long http_code = 0;
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
		m_nLastStatusCode = http_code;

		curl_slist_free_all(headers);
		curl_easy_cleanup(curl);

		// Always return the response body (if any). Caller can inspect status code.

		// Return a copy of the response (caller is responsible for freeing)
		char* result = new char[response.length() + 1];
		strcpy(result, response.c_str());
		return result;
	}

	int HttpGet::GetLastStatusCode() const
	{
		return (int)m_nLastStatusCode;
	}

	// HttpPost implementation
	HttpPost::HttpPost(const char* sUrl)
	{
		m_sUrl = sUrl ? sUrl : "";
		m_sBody = "";
		m_nLastStatusCode = 0;
		m_sUsername = 0;
		m_sPassword = 0;
		m_sTemp = 0;
	}

	HttpPost::~HttpPost()
	{
		if (m_sUsername)
			delete m_sUsername;
		if (m_sPassword)
			delete m_sPassword;
		if (m_sTemp)
			delete m_sTemp;
	}

	void HttpPost::AddHeader(const char* sName, const char* sValue)
	{
		if (sName && sValue)
		{
			m_headers.push_back(std::make_pair(std::string(sName), std::string(sValue)));
		}
	}

	void HttpPost::SetBody(const char* sBody)
	{
		m_sBody = sBody ? sBody : "";
	}

	void HttpPost::SetUsername(const char* sxUsername)
	{
		if (sxUsername)
		{
			if (m_sUsername)
			{
				m_sUsername->Set(sxUsername);
			}
			else
			{
				m_sUsername = new InternalString(sxUsername);
			}
		}
	}

	void HttpPost::SetPassword(const char* sxPassword)
	{
		if (sxPassword)
		{
			if (m_sPassword)
			{
				m_sPassword->Set(sxPassword);
			}
			else
			{
				m_sPassword = new InternalString(sxPassword);
			}
		}
	}

	void SetPassword(const char* sxPassword)
	{

	}

	const char* HttpPost::Execute()
	{
		CURL* curl = curl_easy_init();
		if (!curl)
		{
			m_nLastStatusCode = 0;
			return nullptr;
		}

		std::string response;
		struct curl_slist* headers = nullptr;

		// Add custom headers
		for (const auto& header : m_headers)
		{
			std::string headerLine = header.first + ": " + header.second;
			headers = curl_slist_append(headers, headerLine.c_str());
		}

		curl_easy_setopt(curl, CURLOPT_URL, m_sUrl.c_str());
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, m_sBody.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L); // 30 second timeout
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Follow redirects

		if (m_sUsername)
			curl_easy_setopt(curl, CURLOPT_USERNAME, m_sUsername->GetExternalString());
		if (m_sPassword)
    		curl_easy_setopt(curl, CURLOPT_PASSWORD, m_sPassword->GetExternalString());

		CURLcode res = curl_easy_perform(curl);
		
		long http_code = 0;
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
		m_nLastStatusCode = http_code;

		curl_slist_free_all(headers);
		curl_easy_cleanup(curl);

		// Always keep response (even on non-2xx) so caller can debug.
		// Return nullptr only when curl itself fails hard and we have no body.
		if (res != CURLE_OK && response.length() == 0)
			return nullptr;

		Assert::Plz(!m_sTemp);
		m_sTemp = new InternalString(response.c_str());
		return m_sTemp->GetExternalString();
	}

	int HttpPost::GetLastStatusCode() const
	{
		return (int)m_nLastStatusCode;
	}

	// HttpPostMultipart implementation
	HttpPostMultipart::HttpPostMultipart(const char* sxUrl)
	{
		m_sUrl = sxUrl ? sxUrl : "";
		m_nLastStatusCode = 0;
		m_sTemp = 0;
	}

	HttpPostMultipart::~HttpPostMultipart()
	{
		if (m_sTemp)
			delete m_sTemp;
	}

	void HttpPostMultipart::AddHeader(const char* sxName, const char* sxValue)
	{
		if (sxName && sxValue)
			m_headers.push_back(std::make_pair(std::string(sxName), std::string(sxValue)));
	}

	void HttpPostMultipart::AddField(const char* sxName, const char* sxValue)
	{
		if (sxName && sxValue)
			m_fields.push_back(std::make_pair(std::string(sxName), std::string(sxValue)));
	}

	void HttpPostMultipart::AddFile(const char* sxName, const char* sxPath, const char* sxContentType)
	{
		if (!sxName || !sxPath)
			return;
		FilePart p;
		p.name = sxName;
		p.path = sxPath;
		p.contentType = sxContentType ? sxContentType : "";
		m_files.push_back(p);
	}

	const char* HttpPostMultipart::Execute()
	{
		CURL* curl = curl_easy_init();
		if (!curl)
		{
			m_nLastStatusCode = 0;
			return nullptr;
		}

		std::string response;
		struct curl_slist* headers = nullptr;

		for (const auto& header : m_headers)
		{
			std::string headerLine = header.first + ": " + header.second;
			headers = curl_slist_append(headers, headerLine.c_str());
		}

		curl_mime* mime = curl_mime_init(curl);

		for (const auto& field : m_fields)
		{
			curl_mimepart* part = curl_mime_addpart(mime);
			curl_mime_name(part, field.first.c_str());
			curl_mime_data(part, field.second.c_str(), CURL_ZERO_TERMINATED);
		}

		for (const auto& file : m_files)
		{
			curl_mimepart* part = curl_mime_addpart(mime);
			curl_mime_name(part, file.name.c_str());
			curl_mime_filedata(part, file.path.c_str());
			if (!file.contentType.empty())
				curl_mime_type(part, file.contentType.c_str());
		}

		curl_easy_setopt(curl, CURLOPT_URL, m_sUrl.c_str());
		curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60L);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		CURLcode res = curl_easy_perform(curl);

		long http_code = 0;
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
		m_nLastStatusCode = http_code;

		curl_slist_free_all(headers);
		curl_mime_free(mime);
		curl_easy_cleanup(curl);

		if (res != CURLE_OK && response.length() == 0)
			return nullptr;

		Assert::Plz(!m_sTemp);
		m_sTemp = new InternalString(response.c_str());
		return m_sTemp->GetExternalString();
	}

	int HttpPostMultipart::GetLastStatusCode() const
	{
		return (int)m_nLastStatusCode;
	}
} 