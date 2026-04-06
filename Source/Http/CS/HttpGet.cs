using System;
using System.Collections.Generic;
using System.Net.Http;
using System.Threading.Tasks;

namespace NumbatLogic
{
    public class HttpClient
    {
        internal System.Net.Http.HttpClient m_httpClient;

        public HttpClient()
        {
            m_httpClient = new System.Net.Http.HttpClient();
        }
    }

    public class HttpGet
    {
        private string m_sUrl;
        private Dictionary<string, string> m_headers;
        private int m_nLastStatusCode;

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
            return Execute(null);
        }

        public string Execute(HttpClient pClient)
        {
            var pLocalClient = pClient ?? new HttpClient();
            var client = pLocalClient.m_httpClient;
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
                var response = client.SendAsync(request).GetAwaiter().GetResult();
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
            finally
            {
                if (pClient == null)
                    client.Dispose();
            }
        }

        public int GetLastStatusCode()
        {
            return m_nLastStatusCode;
        }
    }
} 