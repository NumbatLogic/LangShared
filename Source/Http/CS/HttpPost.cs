using System;
using System.Collections.Generic;
using System.Net.Http;
using System.Threading.Tasks;

namespace NumbatLogic
{
	public class HttpPost
	{
		private string m_sUrl;
		private Dictionary<string, string> m_headers;
		private string m_sBody;
		private string m_sUsername;
		private string m_sPassword;
		private int m_nLastStatusCode;
		private static readonly HttpClient m_httpClient = new HttpClient();

		public HttpPost(string sUrl)
		{
			m_sUrl = sUrl;
			m_headers = new Dictionary<string, string>();
			m_sBody = "";
			m_sUsername = null;
			m_sPassword = null;
			m_nLastStatusCode = 0;
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

		public void SetUsername(string sxUsername)
		{
			m_sUsername = sxUsername;
		}

		public void SetPassword(string sxPassword)
		{
			m_sPassword = sxPassword;
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

				if (!string.IsNullOrEmpty(m_sUsername) || !string.IsNullOrEmpty(m_sPassword))
				{
					string user = m_sUsername ?? "";
					string pass = m_sPassword ?? "";
					string raw = $"{user}:{pass}";
					string token = Convert.ToBase64String(System.Text.Encoding.UTF8.GetBytes(raw));
					request.Headers.Authorization = new System.Net.Http.Headers.AuthenticationHeaderValue("Basic", token);
				}

				// Make the request synchronously
				var response = m_httpClient.SendAsync(request).GetAwaiter().GetResult();
				m_nLastStatusCode = (int)response.StatusCode;
				
				if (response.IsSuccessStatusCode)
				{
					var responseContent = response.Content.ReadAsStringAsync().GetAwaiter().GetResult();
					return responseContent;
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

	// Minimal Multipart helper (CS backend). Included for completeness.
	public class HttpPostMultipart
	{
		private string m_sUrl;
		private Dictionary<string, string> m_headers;
		private Dictionary<string, string> m_fields;
		private List<(string Name, string Path, string ContentType)> m_files;
		private int m_nLastStatusCode;
		private static readonly HttpClient m_httpClient = new HttpClient();

		public HttpPostMultipart(string sUrl)
		{
			m_sUrl = sUrl;
			m_headers = new Dictionary<string, string>();
			m_fields = new Dictionary<string, string>();
			m_files = new List<(string, string, string)>();
			m_nLastStatusCode = 0;
		}

		public void AddHeader(string sName, string sValue)
		{
			if (!string.IsNullOrEmpty(sName) && !string.IsNullOrEmpty(sValue))
				m_headers[sName] = sValue;
		}

		public void AddField(string sName, string sValue)
		{
			if (!string.IsNullOrEmpty(sName))
				m_fields[sName] = sValue ?? "";
		}

		public void AddFile(string sName, string sPath, string sContentType)
		{
			if (!string.IsNullOrEmpty(sName) && !string.IsNullOrEmpty(sPath))
				m_files.Add((sName, sPath, sContentType ?? ""));
		}

		public string Execute()
		{
			try
			{
				var content = new MultipartFormDataContent();
				foreach (var field in m_fields)
					content.Add(new StringContent(field.Value), field.Key);

				foreach (var file in m_files)
				{
					var bytes = System.IO.File.ReadAllBytes(file.Path);
					var fileContent = new ByteArrayContent(bytes);
					if (!string.IsNullOrEmpty(file.ContentType))
						fileContent.Headers.ContentType = new System.Net.Http.Headers.MediaTypeHeaderValue(file.ContentType);
					content.Add(fileContent, file.Name, System.IO.Path.GetFileName(file.Path));
				}

				var request = new HttpRequestMessage(HttpMethod.Post, m_sUrl) { Content = content };
				foreach (var header in m_headers)
					request.Headers.Add(header.Key, header.Value);

				var response = m_httpClient.SendAsync(request).GetAwaiter().GetResult();
				m_nLastStatusCode = (int)response.StatusCode;
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