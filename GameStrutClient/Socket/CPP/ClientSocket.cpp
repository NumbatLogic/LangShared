#include "ClientSocket.hpp"
#include "../../../Assert/CPP/Assert.hpp"
#include "../../../Blob/CPP/Blob.hpp"

#include <cstring>
#include <string>

#ifdef NB_WINDOWS
	#include <winsock2.h>
	#include <ws2tcpip.h>
#else
	#include <arpa/inet.h>
	#include <errno.h>
	#include <netdb.h>
	#include <netinet/in.h>
	#include <sys/ioctl.h>
	#include <sys/socket.h>
	#include <sys/time.h>
	#include <unistd.h>
#endif

#ifdef NB_WINDOWS
	int s_nWsaCount = 0;
#endif

namespace NumbatLogic
{
	ClientSocket::ClientSocket()
	{
		m_nSocket = -1;
		m_nPort = -1;
		m_bConnected = false;
		m_pHost = NULL;
		m_nClientSocketId = 0;  // Initialize client socket ID to 0

		// Initialize buffers
		m_nWriteDataSize = 0;
		m_nWriteBufferSize = INITIAL_BUFFER_SIZE;
		m_pWriteBuffer = new unsigned char[m_nWriteBufferSize];

		m_nReadDataSize = 0;
		m_nReadBufferSize = INITIAL_BUFFER_SIZE;
		m_pReadBuffer = new unsigned char[m_nReadBufferSize];
	}

	ClientSocket::~ClientSocket()
	{
		Assert::Plz(m_nSocket == -1);
		Assert::Plz(!m_bConnected);

		delete m_pHost;
		delete[] m_pWriteBuffer;
		delete[] m_pReadBuffer;
	}

	void ClientSocket::Connect(const char* host, int port)
	{
		Assert::Plz(m_nSocket == -1);
		Assert::Plz(!m_bConnected);

		if (m_pHost)
			delete m_pHost;
		m_pHost = new InternalString(host);
		m_nPort = port;

		#ifdef NB_WINDOWS
			if (s_nWsaCount == 0)
			{
				WSADATA wsaData;
				int nResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
				Assert::Plz(nResult == 0);
			}
			s_nWsaCount++;
		#endif

		struct addrinfo hints;
		struct addrinfo* result = NULL;
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		int status = getaddrinfo(host, std::to_string(port).c_str(), &hints, &result);
		Assert::Plz(status == 0);

		m_nSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		Assert::Plz(m_nSocket >= 0);

		status = connect(m_nSocket, result->ai_addr, (int)result->ai_addrlen);
		Assert::Plz(status == 0);

		freeaddrinfo(result);
		m_bConnected = true;
	}

	void ClientSocket::Disconnect()
	{
		if (!m_bConnected)
			return;

		if (m_nSocket >= 0)
		{
			#ifdef NB_WINDOWS
				shutdown(m_nSocket, SD_BOTH);
				closesocket(m_nSocket);
			#else
				close(m_nSocket);
			#endif
			m_nSocket = -1;
		}

		m_bConnected = false;
		m_nPort = -1;
		delete m_pHost;
		m_pHost = NULL;

		#ifdef NB_WINDOWS
			Assert::Plz(s_nWsaCount > 0);
			s_nWsaCount--;
			if (s_nWsaCount == 0)
				WSACleanup();
		#endif
	}

	void ClientSocket::Update()
	{
		if (!m_bConnected || m_nSocket < 0)
			return;

		// Process write buffer
		if (m_nWriteDataSize > 0)
		{
			int bytesSent = send(m_nSocket, (const char*)m_pWriteBuffer, m_nWriteDataSize, 0);
			if (bytesSent > 0)
			{
				// Move remaining data to start of buffer
				if (bytesSent < m_nWriteDataSize)
				{
					memmove(m_pWriteBuffer, m_pWriteBuffer + bytesSent, m_nWriteDataSize - bytesSent);
				}
				m_nWriteDataSize -= bytesSent;
			}
		}

		// Process read buffer
		int bytesAvailable = 0;
		#ifdef NB_WINDOWS
			ioctlsocket(m_nSocket, FIONREAD, (u_long*)&bytesAvailable);
		#else
			ioctl(m_nSocket, FIONREAD, &bytesAvailable);
		#endif

		if (bytesAvailable > 0)
		{
			// Ensure buffer is large enough
			if (m_nReadDataSize + bytesAvailable > m_nReadBufferSize)
			{
				unsigned int newSize = m_nReadBufferSize * 2;
				while (newSize < m_nReadDataSize + bytesAvailable)
					newSize *= 2;

				unsigned char* newBuffer = new unsigned char[newSize];
				memcpy(newBuffer, m_pReadBuffer, m_nReadDataSize);
				delete[] m_pReadBuffer;
				m_pReadBuffer = newBuffer;
				m_nReadBufferSize = newSize;
			}

			int bytesRead = recv(m_nSocket, (char*)m_pReadBuffer + m_nReadDataSize, bytesAvailable, 0);
			if (bytesRead > 0)
			{
				m_nReadDataSize += bytesRead;
			}
		}
	}

	bool ClientSocket::Pending()
	{
		if (!m_bConnected || m_nSocket < 0)
			return false;

		return m_nWriteDataSize > 0; // || m_nReadDataSize > 0;
	}

	bool ClientSocket::GetConnected()
	{
		return m_bConnected && m_nSocket > 0;
	}

	bool ClientSocket::Send(Blob* pBlob)
	{
		if (!m_bConnected || m_nSocket < 0 || !pBlob)
			return false;

		// Ensure write buffer is large enough
		if (m_nWriteDataSize + sizeof(unsigned short) + pBlob->GetSize() > m_nWriteBufferSize)
		{
			unsigned int newSize = m_nWriteBufferSize * 2;
			while (newSize < m_nWriteDataSize + sizeof(unsigned short) + pBlob->GetSize())
				newSize *= 2;

			unsigned char* newBuffer = new unsigned char[newSize];
			memcpy(newBuffer, m_pWriteBuffer, m_nWriteDataSize);
			delete[] m_pWriteBuffer;
			m_pWriteBuffer = newBuffer;
			m_nWriteBufferSize = newSize;
		}
		
		*((unsigned short*)(m_pWriteBuffer + m_nWriteDataSize)) = pBlob->GetSize();
		m_nWriteDataSize += sizeof(unsigned short);
		memcpy(m_pWriteBuffer + m_nWriteDataSize, pBlob->GetData(), pBlob->GetSize());
		m_nWriteDataSize += pBlob->GetSize();

		// Try to send immediately
		Update();
		return true;
	}

	Blob* ClientSocket::Receive()
	{
		if (!m_bConnected || m_nSocket < 0)
			return NULL;

		// Process any pending data
		Update();

		if (m_nReadDataSize < sizeof(unsigned short))
			return NULL;

		unsigned short nSize = *((unsigned short*)m_pReadBuffer);

		if (nSize > m_nReadDataSize + sizeof(unsigned short))
			return NULL;

		// Create new blob with available data
		Blob* pBlob = new Blob(false);
		pBlob->Resize(nSize, false);
		pBlob->PackData(m_pReadBuffer + sizeof(unsigned short), 0, nSize);

		m_nReadDataSize -= nSize + sizeof(unsigned short);
		if (m_nReadDataSize > 0)
			memmove(m_pReadBuffer, m_pReadBuffer + nSize + sizeof(unsigned short), m_nReadDataSize);
		
		//m_nReadDataSize = 0;  // Clear the read buffer
		return pBlob;
	}

	void ClientSocket::SetAcceptedSocket(int socket)
	{
		m_nSocket = socket;
		m_bConnected = true;
	}
} 