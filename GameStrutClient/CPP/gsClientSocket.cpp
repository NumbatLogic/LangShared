#include "gsClientSocket.hpp"
#include "../../Assert/CPP/Assert.hpp"
#include "../../Blob/CPP/Blob.hpp"

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
	#include <fcntl.h>
#endif

#ifdef NB_WINDOWS
	int s_nWsaCount = 0;
#endif

namespace NumbatLogic
{
	gsClientSocket::gsClientSocket()
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

	gsClientSocket::~gsClientSocket()
	{
		Assert::Plz(m_nSocket == -1);
		Assert::Plz(!m_bConnected);

		delete m_pHost;
		delete[] m_pWriteBuffer;
		delete[] m_pReadBuffer;
	}

	void gsClientSocket::Connect(const char* host, int port)
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

		// Set socket to non-blocking mode
		#ifdef NB_WINDOWS
			u_long mode = 1; // 1 to enable non-blocking socket
			int result_ioctl = ioctlsocket(m_nSocket, FIONBIO, &mode);
			if (result_ioctl != NO_ERROR) {
				printf("Unable to set socket non blocking\n");
				Assert::Plz(false);
			}
		#else
			int flags = fcntl(m_nSocket, F_GETFL);
			if (fcntl(m_nSocket, F_SETFL, flags | O_NONBLOCK) == -1) {
				printf("Unable to set socket non blocking\n");
				Assert::Plz(false);
			}
		#endif

		status = connect(m_nSocket, result->ai_addr, (int)result->ai_addrlen);
		
		#ifdef NB_WINDOWS
			if (status == SOCKET_ERROR) {
				int error = WSAGetLastError();
				if (error != WSAEWOULDBLOCK) {
					printf("Connect failed with error: %d\n", error);
					Assert::Plz(false);
				}
			}
		#else
			if (status < 0) {
				if (errno != EINPROGRESS) {
					printf("Connect failed with error: %s\n", strerror(errno));
					Assert::Plz(false);
				}
			}
		#endif
		
		freeaddrinfo(result);
		m_bConnected = true;
	}

	void gsClientSocket::Disconnect()
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

	void gsClientSocket::Update()
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
			else if (bytesSent < 0)
			{
				#ifdef NB_WINDOWS
					int error = WSAGetLastError();
					if (error != WSAEWOULDBLOCK) {
						printf("Send error: %d\n", error);
						// Handle send error appropriately
					}
				#else
					if (errno != EAGAIN && errno != EWOULDBLOCK) {
						printf("Send error: %s\n", strerror(errno));
						// Handle send error appropriately
					}
				#endif
			}
		}

		// Process read buffer
		/*int bytesAvailable = 0;
		#ifdef NB_WINDOWS
			ioctlsocket(m_nSocket, FIONREAD, (u_long*)&bytesAvailable);
		#else
			int x = ioctl(m_nSocket, FIONREAD, &bytesAvailable);
			if (x < 0)
			{
				if (errno != EAGAIN && errno != EWOULDBLOCK) {
					printf("ioctl error %d - %d - %s\n", m_nSocket, errno, strerror(errno));
				}
			}
		#endif
*/

int bytesAvailable = 200;
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
			else if (bytesRead < 0)
			{
				#ifdef NB_WINDOWS
					int error = WSAGetLastError();
					if (error != WSAEWOULDBLOCK) {
						printf("Recv error: %d\n", error);
						// Handle recv error appropriately
					}
				#else
					if (errno != EAGAIN && errno != EWOULDBLOCK) {
						printf("Recv error: %s\n", strerror(errno));
						// Handle recv error appropriately
					}
				#endif
			}
		}
	}

	bool gsClientSocket::Pending()
	{
		if (!m_bConnected || m_nSocket < 0)
			return false;

		return m_nWriteDataSize > 0; // || m_nReadDataSize > 0;
	}

	bool gsClientSocket::GetConnected()
	{
		return m_bConnected && m_nSocket > 0;
	}

	bool gsClientSocket::Send(gsBlob* pBlob)
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
		pBlob->SetOffset(0);
		pBlob->UnpackData(m_pWriteBuffer + m_nWriteDataSize, pBlob->GetSize());
		m_nWriteDataSize += pBlob->GetSize();

		// Try to send immediately
		Update();
		return true;
	}

	gsBlob* gsClientSocket::Receive()
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
		gsBlob* pBlob = new gsBlob();
		pBlob->PackData(m_pReadBuffer + sizeof(unsigned short), nSize);

		m_nReadDataSize -= nSize + sizeof(unsigned short);
		if (m_nReadDataSize > 0)
			memmove(m_pReadBuffer, m_pReadBuffer + nSize + sizeof(unsigned short), m_nReadDataSize);
		
		pBlob->SetOffset(0);
		return pBlob;
	}

	void gsClientSocket::SetServerClientSocket(int nSocket, unsigned int nClientSocketId)
	{
		m_nSocket = nSocket;
		m_bConnected = true;
		m_nClientSocketId = nClientSocketId;
	}
}
