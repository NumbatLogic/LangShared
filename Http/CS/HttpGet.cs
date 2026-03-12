using System;
using System.Collections.Generic;
using System.Net.Http;
using System.Threading.Tasks;

namespace NumbatLogic
{
    class HttpGet
    {
        private string m_sUrl;
        private Dictionary<string, string> m_headers;
        private int m_nLastStatusCode;
        private static readonly HttpClient m_httpClient = new HttpClient();

        public HttpGet(string sUrl)
        {
            m_sUrl = sUrl;
            m_headers = new Dictionary<string, string>();
            m_nLastStatusCode = 0;
        }

        public void AddHeader(string sName, string sValue)
        {
            if (!string.IsNullOrEmpty(sName) && !string.IsNullOrEmpty(sValue))
            {
                m_headers[sName] = sValue;
            }
        }

        public string Execute()
        {
            try
            {
                // Create a new request message
                var request = new HttpRequestMessage(HttpMethod.Get, m_sUrl);
                
                // Add all headers
                foreach (var header in m_headers)
                {
                    request.Headers.Add(header.Key, header.Value);
                }

                // Make the request synchronously
                var response = m_httpClient.SendAsync(request).GetAwaiter().GetResult();
                m_nLastStatusCode = (int)response.StatusCode;
                
                if (response.IsSuccessStatusCode)
                {
                    var content = response.Content.ReadAsStringAsync().GetAwaiter().GetResult();
                    return content;
                }
                
                // Return body even on non-2xx to aid debugging
                return response.Content.ReadAsStringAsync().GetAwaiter().GetResult();
            }
            catch
            {
                m_nLastStatusCode = 0;
                return null;
            }
        }

        public int GetLastStatusCode()
        {
            return m_nLastStatusCode;
        }
    }
} 