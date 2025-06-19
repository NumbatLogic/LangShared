#include "ServerSocket.hpp"
#include "../../../Assert/CPP/Assert.hpp"
#include "../../../Blob/CPP/Blob.hpp"
#include "ClientSocket.hpp"

#include <cstring>

#ifdef NB_WINDOWS
	#include <winsock2.h>
#else
	#include <arpa/inet.h>
	#include <errno.h>
	#include <fcntl.h>
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
	ServerSocket::ServerSocket()
	{
		m_nSocket = -1;
		m_nPort = -1;
		m_nNextClientId = 1;  // Start client IDs at 1 (0 is reserved for broadcast)
		m_pClientSocketVector = new Vector<ClientSocket*>();
	}

	ServerSocket::~ServerSocket()
	{
		Assert::Plz(m_nSocket == -1);
		Assert::Plz(m_nPort == -1);
		// Clean up client connections if any remain
		for (unsigned int i = 0; i < m_pClientSocketVector->GetSize(); ++i)
		{
			ClientSocket* pClientSocket = m_pClientSocketVector->Get(i);
			if (pClientSocket)
			{
				pClientSocket->Disconnect();
				delete pClientSocket;
			}
		}
		m_pClientSocketVector->Clear();
		Assert::Plz(m_pClientSocketVector->GetSize() == 0);
	}

	void ServerSocket::Start(int port)
	{
		Assert::Plz(m_nSocket == -1);
		Assert::Plz(m_nPort == -1);
		Assert::Plz(m_pClientSocketVector->GetSize() == 0);

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

		
		{
			struct sockaddr_in address;
			int yes = 1;

			Assert::Plz(m_nSocket == -1);

			//m_nPort = nPort;

			m_nSocket = (int)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (m_nSocket < 0)
			{
				//return false;
				Assert::Plz(false);
			}

			memset(&address, 0, sizeof(address));

			address.sin_family = AF_INET;
			address.sin_addr.s_addr = INADDR_ANY;
			address.sin_port = htons(m_nPort);

			// lose the pesky "Address already in use" error message (beacuse of TIME_WAIT)
			if (setsockopt(m_nSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&yes, sizeof(int)) == -1)
				Assert::Plz(false);		// todo: cleanup

			if (bind(m_nSocket, (struct sockaddr*) &address, sizeof(address)) < 0)
				Assert::Plz(false);		// todo: cleanup

			listen(m_nSocket, 5);
		}
	}

	void ServerSocket::Stop()
	{
		Assert::Plz(m_nPort != -1);
		Assert::Plz(m_nSocket != -1);

		close(m_nSocket);
		m_nSocket = -1;  // Reset to initial state
		m_nPort = -1;    // Reset to initial state

		// Clean up client connections
		for (unsigned int i = 0; i < m_pClientSocketVector->GetSize(); ++i)
		{
			ClientSocket* pClientSocket = m_pClientSocketVector->Get(i);
			if (pClientSocket)
			{
				pClientSocket->Disconnect();
				delete pClientSocket;
			}
		}
		m_pClientSocketVector->Clear();
	}

	void ServerSocket::Update()
	{
		if (m_nSocket == -1)
			return;

		// Process all client connections
		for (unsigned int i = 0; i < m_pClientSocketVector->GetSize(); ++i)
		{
			ClientSocket* pClientSocket = m_pClientSocketVector->Get(i);
			if (pClientSocket)
			{
				// Update client socket to process any pending data
				pClientSocket->Update();
			}
		}
	}

	bool ServerSocket::Pending()
	{
		if (m_nSocket == -1)
			return false;

		// Check all clients for pending data
		for (unsigned int i = 0; i < m_pClientSocketVector->GetSize(); i++)
		{
			ClientSocket* pClientSocket = m_pClientSocketVector->Get(i);
			if (pClientSocket)
			{
				// Check if client has pending data to receive or send
				if (pClientSocket->Pending())
				{
					return true;
				}
			}
		}
		return false;
	}

	ClientSocket* ServerSocket::Accept()
	{
		Assert::Plz(m_nSocket != -1);

		struct sockaddr_in clientAddr;
		socklen_t clientLen = sizeof(clientAddr);
		
		int clientSocket = accept(m_nSocket, (struct sockaddr*)&clientAddr, &clientLen);
		if (clientSocket < 0)
		{
			// No pending connection or error
			return NULL;
		}

		// Create new client socket
		ClientSocket* pNewClient = new ClientSocket();
		Assert::Plz(pNewClient != NULL);
		pNewClient->SetAcceptedSocket(clientSocket);
		pNewClient->SetClientSocketId(m_nNextClientId++);  // Assign and increment client socket ID
		
		// Set non-blocking mode
		#ifdef NB_WINDOWS
			u_long mode = 1;
			ioctlsocket(clientSocket, FIONBIO, &mode);
		#else
			int flags = fcntl(clientSocket, F_GETFL, 0);
			if (flags != -1)
			{
				fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK);
			}
		#endif
		// Add to client vector
		m_pClientSocketVector->PushBack(pNewClient);

		return pNewClient;
	}

	void ServerSocket::Send(Blob* pBlob, unsigned int clientSocketId)
	{
		Assert::Plz(pBlob != NULL);
		Assert::Plz(m_nSocket != -1);

		Blob* pClientBlob = new Blob(false);
		pClientBlob->Resize(pBlob->GetSize(), false);
		pClientBlob->PackData(pBlob->GetData(), 0, pBlob->GetSize());
		
		if (clientSocketId == 0)
		{
			for (unsigned int i = 0; i < m_pClientSocketVector->GetSize(); i++)
			{
				ClientSocket* pClientSocket = m_pClientSocketVector->Get(i);
				if (pClientSocket)
				{
					if (!pClientSocket->Send(pClientBlob))
					{
						Assert::Plz(false);
					}
				}
			}
			delete pClientBlob;
			return;
		}
		else
		{
			for (unsigned int i = 0; i < m_pClientSocketVector->GetSize(); i++)
			{
				ClientSocket* pClientSocket = m_pClientSocketVector->Get(i);
				if (pClientSocket && pClientSocket->GetClientSocketId() == clientSocketId)
				{
					pClientSocket->Send(pClientBlob);
					delete pClientBlob;
					return;
				}
			}
		}

		delete pClientBlob;
		Assert::Plz(false);
	}
}
