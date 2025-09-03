#include "Http.hpp"
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

		curl_slist_free_all(headers);
		curl_easy_cleanup(curl);

		if (res != CURLE_OK || http_code < 200 || http_code >= 300)
		{
			return nullptr;
		}

		// Return a copy of the response (caller is responsible for freeing)
		char* result = new char[response.length() + 1];
		strcpy(result, response.c_str());
		return result;
	}

	// HttpPost implementation
	HttpPost::HttpPost(const char* sUrl)
	{
		m_sUrl = sUrl ? sUrl : "";
		m_sBody = "";
	}

	HttpPost::~HttpPost()
	{
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

	const char* HttpPost::Execute()
	{
		CURL* curl = curl_easy_init();
		if (!curl)
		{
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

		CURLcode res = curl_easy_perform(curl);
		
		long http_code = 0;
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

		curl_slist_free_all(headers);
		curl_easy_cleanup(curl);

		if (res != CURLE_OK || http_code < 200 || http_code >= 300)
		{
			return nullptr;
		}

		// Return a copy of the response (caller is responsible for freeing)
		char* result = new char[response.length() + 1];
		strcpy(result, response.c_str());
		return result;
	}
} 