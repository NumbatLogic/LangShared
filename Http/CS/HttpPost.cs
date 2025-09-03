using System;
using System.Collections.Generic;
using System.Net.Http;
using System.Threading.Tasks;

namespace NumbatLogic
{
    class HttpPost
    {
        private string m_sUrl;
        private Dictionary<string, string> m_headers;
        private string m_sBody;
        private static readonly HttpClient m_httpClient = new HttpClient();

        public HttpPost(string sUrl)
        {
            m_sUrl = sUrl;
            m_headers = new Dictionary<string, string>();
            m_sBody = "";
        }

        public void AddHeader(string sName, string sValue)
        {
            if (!string.IsNullOrEmpty(sName) && !string.IsNullOrEmpty(sValue))
            {
                m_headers[sName] = sValue;
            }
        }

        public void SetBody(string sBody)
        {
            m_sBody = sBody ?? "";
        }

        public string Execute()
        {
            try
            {
                // Create content from body
                var content = new StringContent(m_sBody);
                
                // Create a new request message
                var request = new HttpRequestMessage(HttpMethod.Post, m_sUrl)
                {
                    Content = content
                };
                
                // Add all headers
                foreach (var header in m_headers)
                {
                    if (header.Key.ToLower() == "content-type")
                    {
                        // Content-Type header needs to be set on the content
                        content.Headers.ContentType = new System.Net.Http.Headers.MediaTypeHeaderValue(header.Value);
                    }
                    else
                    {
                        request.Headers.Add(header.Key, header.Value);
                    }
                }

                // Make the request synchronously
                var response = m_httpClient.SendAsync(request).GetAwaiter().GetResult();
                
                if (response.IsSuccessStatusCode)
                {
                    var responseContent = response.Content.ReadAsStringAsync().GetAwaiter().GetResult();
                    return responseContent;
                }
                
                return null;
            }
            catch
            {
                return null;
            }
        }
    }
} 