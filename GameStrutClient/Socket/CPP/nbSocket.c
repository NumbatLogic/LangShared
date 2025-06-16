#include <nbPlatformDefine/nbPlatformDefine.h>
#ifdef NB_WINDOWS
	#include <winsock2.h>
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

#define NB_SOCKET_SECRET
#include "nbSocket.h"

#include <nbAssert/nbAssert.h>
#include <nbMemoryManager/nbMemoryManager.h>
#include <string.h>

#ifdef NB_WINDOWS
	int s_nWsaCount = 0;
#endif

#ifdef NB_SOCKET_SERVER
	// **************
	// nbServerSocket
	// **************
	nbServerSocket* nbServerSocket_Create(Uint16 nPort)
	{
		nbServerSocket* pServerSocket;

		#ifdef NB_WINDOWS
			if (s_nWsaCount == 0)
			{
				WSADATA wsaData;
				int nResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
				nbAssert(nResult == 0);
			}
			s_nWsaCount++;
		#endif

		//nbAssert(nb_pSocketManager);

		pServerSocket = (nbServerSocket*)nbMalloc(sizeof(nbServerSocket));
		pServerSocket->nSocket = -1;

		pServerSocket->pClientSocketVector = nbVector_Create();

		//Bool nbServerSocket_Bind(nbServerSocket* pServerSocket, Uint16 nPort)
		{
			struct sockaddr_in address;
			int yes = 1;

			nbAssert(pServerSocket->nSocket == -1);

			//pServerSocket->nPort = nPort;

			pServerSocket->nSocket = (Int32)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (pServerSocket->nSocket < 0)
				return TEH_FALSE;

			memset(&address, 0, sizeof(address));

			address.sin_family = AF_INET;
			address.sin_addr.s_addr = INADDR_ANY;
			address.sin_port = htons(nPort);

			// lose the pesky "Address already in use" error message (beacuse of TIME_WAIT)
			if (setsockopt(pServerSocket->nSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&yes, sizeof(int)) == -1)
				nbAssert(TEH_FALSE);		// todo: cleanup

			if (bind(pServerSocket->nSocket, (struct sockaddr*) &address, sizeof(address)) < 0)
				nbAssert(TEH_FALSE);		// todo: cleanup

			listen(pServerSocket->nSocket, 5);

			//#ifdef _WIN32
			//	// If iMode!=0, non-blocking mode is enabled.
			//	u_long iMode=1;
			//	ioctlsocket(m_nSocket,FIONBIO,&iMode);
			//#else
			//	// probably wrong
			//	int iMode=1;
			//	ioctl(m_nSocket,FIONBIO,&iMode);
			//#endif
			
			//	return TEH_TRUE;
		}
		
		//nbVector_PushBack(nb_pSocketManager->pServerSocketVector, pServerSocket);

		return pServerSocket;
	}

	void nbServerSocket_Destroy(nbServerSocket* pServerSocket)
	{
		nbAssert(pServerSocket);

		nbAssert(nbVector_GetSize(pServerSocket->pClientSocketVector) == 0);
		nbVector_Destroy(pServerSocket->pClientSocketVector);

		if (pServerSocket->nSocket >= 0)
		{
			#ifdef NB_WINDOWS
				shutdown(pServerSocket->nSocket, SD_BOTH);
				closesocket(pServerSocket->nSocket);
			#else
				//shutdown(pClientSocket->nSocket, SHUT_RDWR);
				close(pServerSocket->nSocket);
			#endif
		}

		nbFree(pServerSocket);

		#ifdef NB_WINDOWS
			nbAssert(s_nWsaCount > 0);
			s_nWsaCount--;
			if (s_nWsaCount == 0)
				WSACleanup();
		#endif
	}

	void nbServerSocket_Update(nbServerSocket* pServerSocket)
	{
		Uint32 i;
		for (i = 0; i < nbVector_GetSize(pServerSocket->pClientSocketVector); i++)
		{
			nbClientSocket* pClientSocket = (nbClientSocket*)nbVector_Get(pServerSocket->pClientSocketVector, i);
			nbClientSocket_Update(pClientSocket);
		}
	}

	Bool nbServerSocket_Pending(nbServerSocket* pServerSocket)
	{
		Uint32 i;
		for (i = 0; i < nbVector_GetSize(pServerSocket->pClientSocketVector); i++)
		{
			nbClientSocket* pClientSocket = (nbClientSocket*)nbVector_Get(pServerSocket->pClientSocketVector, i);
			if (nbClientSocket_Pending(pClientSocket))
				return TEH_TRUE;
		}

		return TEH_FALSE;
	}

	nbClientSocket* nbServerSocket_Accept(nbServerSocket* pServerSocket)
	{
		fd_set readSet;
		struct timeval timeout;
		FD_ZERO(&readSet);
		FD_SET(pServerSocket->nSocket, &readSet);
		memset(&timeout, 0, sizeof(timeout));

		if (select(pServerSocket->nSocket + 1, &readSet, NULL, NULL, &timeout) == 1)
		{
			struct sockaddr_in address;
			#ifdef NB_WINDOWS
				int clilen = sizeof(address);
			#else
				socklen_t clilen = sizeof(address);
			#endif

			nbClientSocket* pClientSocket = nbClientSocket_SubCreate();

			pClientSocket->nSocket = (Int32)accept(pServerSocket->nSocket, (struct sockaddr*) &address, &clilen);
			nbAssert(pClientSocket->nSocket >= 0);
			
			pClientSocket->pServerSocket = pServerSocket;

			nbVector_PushBack(pServerSocket->pClientSocketVector, pClientSocket);

			return pClientSocket;
		}

		return NULL;
	}

#endif

// **************
// nbClientSocket
// **************
nbClientSocket* nbClientSocket_Create(const char* szAddress, Uint16 nPort)
{
	nbClientSocket* pClientSocket;

	#ifdef NB_WINDOWS
		if (s_nWsaCount == 0)
		{
			WSADATA wsaData;
			int nResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
			nbAssert(nResult == 0);
		}
		s_nWsaCount++;
	#endif

	pClientSocket = nbClientSocket_SubCreate();


	{
		struct hostent* pHostInfo;
		struct sockaddr_in address;
		int nResult;

		//printf("SOCKET %ld\n", pClientSocket->nSocket);
		nbAssert(pClientSocket->nSocket == -1);

		//m_bDisconnected = false;

		pClientSocket->nSocket = (Int32)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (pClientSocket->nSocket < 0)
		{
			//printf("Socket phail A\n");
			//m_bDisconnected = true;
			nbAssert(TEH_FALSE);	// todo: cleanup
		}

		pHostInfo = gethostbyname(szAddress);
		if (!pHostInfo)
		{
			//printf("Socket phail B\n");
			//m_bDisconnected = true;
			nbAssert(TEH_FALSE);	// todo: cleanup
		}

		//sockaddr_in address;
		memset(&address, 0, sizeof(address));

		address.sin_family = AF_INET;
		memcpy(&address.sin_addr.s_addr, pHostInfo->h_addr, pHostInfo->h_length);
		address.sin_port = htons(nPort);

		nResult = connect(pClientSocket->nSocket, (struct sockaddr*)&address, sizeof(address));
		//x	m_bConnecting = true;
		if (nResult == -1)
		{
			#ifdef NB_WINDOWS
				//nbClientSocket_SubDestroy(pClientSocket);

				shutdown(pClientSocket->nSocket, SD_BOTH);
				closesocket(pClientSocket->nSocket);
			#else

				shutdown(pClientSocket->nSocket, SHUT_RDWR);
				close(pClientSocket->nSocket);
				/*

				   //printf("%d\n", errno);
				   if (errno == EINPROGRESS)
				   {
					//x m_bConnecting = true;
				   }
				   else
				   {
					//printf("Socket phail D\n");
					//m_bDisconnected = true;
					nbAssert(TEH_FALSE); // todo: cleanup
				   }*/
			#endif

			pClientSocket->nSocket = -1;
			pClientSocket->nState = NB_CLIENT_SOCKET_STATE_CLOSED;
		}

		/*#ifdef _WIN32
			// If iMode!=0, non-blocking mode is enabled.
			u_long iMode=1;
			ioctlsocket(m_nSocket,FIONBIO,&iMode);
		 #else
			// probably wrong
			int iMode=1;
			ioctl(m_nSocket,FIONBIO,&iMode);
		 #endif*/
	}

	//pClientSocket->pUpdateCallback = nbApplication_CallbackRegister_Update(&nbClientSocket_Update, pClientSocket);
	//nbVector_PushBack(nb_pSocketManager->pClientSocketVector, pClientSocket);
	return pClientSocket;
}

void nbClientSocket_Destroy(nbClientSocket* pClientSocket)
{
	//nbAssert(nb_pSocketManager);
	nbAssert(pClientSocket);

	#ifdef NB_SOCKET_SERVER
		if (pClientSocket->pServerSocket)
		{
			Uint32 i;
			nbServerSocket* pServerSocket = pClientSocket->pServerSocket;
			for (i = 0; i < nbVector_GetSize(pServerSocket->pClientSocketVector); i++)
			{
				nbClientSocket* pTestClientSocket = (nbClientSocket*)nbVector_Get(pServerSocket->pClientSocketVector, i);

				if (pTestClientSocket == pClientSocket)
				{
					nbClientSocket_SubDestroy(pClientSocket);
					nbVector_Erase(pServerSocket->pClientSocketVector, i);
					return;
				}
			}
		}
		else
	#endif
	{
		nbClientSocket_SubDestroy(pClientSocket);
	}
	
	#ifdef NB_WINDOWS
		nbAssert(s_nWsaCount > 0);
		s_nWsaCount--;
		if (s_nWsaCount == 0)
			WSACleanup();
	#endif
}

void nbClientSocket_Write(nbClientSocket* pClientSocket, const Uint8* pData, Uint32 nSize)
{
	nbClientSocket_BufferWrite(&pClientSocket->nWriteDataSize, &pClientSocket->nWriteBufferSize, &pClientSocket->pWriteBuffer, pData, nSize);
	//nbClientSocket_Update(pClientSocket);
}

Uint32 nbClientSocket_Read(nbClientSocket* pClientSocket, Uint8* pData, Uint32 nSize)
{
	//nbClientSocket_Update(pClientSocket);
	return nbClientSocket_BufferRead(&pClientSocket->nReadDataSize, &pClientSocket->nReadBufferSize, &pClientSocket->pReadBuffer, pData, nSize);
}

Uint32 nbClientSocket_GetReadDataSize(nbClientSocket* pClientSocket)
{
	return pClientSocket->nReadDataSize;
}

void nbClientSocket_WriteBlob(nbClientSocket* pClientSocket, const nbBlob* pBlob)
{
	/*if (m_bWebSocket)
	   {
		Uint32 payload_len = sizeof(Uint32) + pBlob->GetDataSize();
		Uint32 nBufferSize = sizeof(Uint16) + payload_len;
		if (payload_len > 125)
		{
			nBufferSize += sizeof(Uint16);
			payload_len = 126;
		}

		SendBuffer sendBuffer;
		sendBuffer.nDataSize = nBufferSize;
		sendBuffer.pData = new Uint8[sendBuffer.nDataSize];
		Uint8* p = sendBuffer.pData;

	 * p = 0x1 << 7; // fin
	 * p |= 0x2 << 0; // opcode
		p++;

	 * p = (Uint8)payload_len;
		p++;

		if (payload_len == 126)
		{
			Uint8 nTemp[2];
	 *(Uint16*)nTemp = (Uint16)(sizeof(Uint32) + pBlob->GetDataSize());
	 * p++ = nTemp[1];
	 * p++ = nTemp[0];
		}

	 *(Uint32*)p = pBlob->GetDataSize();
		p += sizeof(Uint32);

		memcpy(p, pBlob->GetData(), pBlob->GetDataSize());

		m_sendBuffer.push_back(sendBuffer);

		//printf("Send WA %d\n", nBufferSize);
	   }
	   else*/
	{
		Uint32 nSize;
		nSize = nbBlob_GetSize(pBlob);

		nbClientSocket_BufferWrite(&pClientSocket->nWriteDataSize, &pClientSocket->nWriteBufferSize, &pClientSocket->pWriteBuffer, (Uint8*)&nSize, sizeof(Uint32));
		nbClientSocket_BufferWrite(&pClientSocket->nWriteDataSize, &pClientSocket->nWriteBufferSize, &pClientSocket->pWriteBuffer, nbBlob_GetData(pBlob), nbBlob_GetSize(pBlob));
		//nbClientSocket_Update(pClientSocket);
	}
}

Bool nbClientSocket_ReadBlob(nbClientSocket* pClientSocket, nbBlob* pBlob)
{
	//Update();
	//if (m_bInitialRead)
	//{
	//	if (m_nDataSize > 2)
	//	{
	//		if (m_pBuffer[0] == 'G' && m_pBuffer[1] == 'E' && m_pBuffer[2] == 'T')
	//		{
	//			if (m_pBuffer[m_nDataSize-4] == '\r' && m_pBuffer[m_nDataSize-3] == '\n' && m_pBuffer[m_nDataSize-2] == '\r' && m_pBuffer[m_nDataSize-1] == '\n')
	//			{
	//				m_pBuffer[m_nDataSize-1] = '\0';

	//				char* p = strstr((char*)m_pBuffer, "Sec-WebSocket-Key: ");
	//				p += strlen("Sec-WebSocket-Key: ");

	//				std::string sKey;
	//				while (*p != '\n' && *p != '\r')
	//					sKey += *p++;
	//				//sKey = "dGhlIHNhbXBsZSBub25jZQ==";
	//				sKey += "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

	//				SHA1Context sha;
	//				SHA1Reset(&sha);
	//				SHA1Input(&sha, (Uint8*)sKey.c_str(), (unsigned int)sKey.length());
	//				SHA1Result(&sha);

	//				// SHA or base64 is broken, i shoudn't be fixing endianess!
	//				Uint8* pShaA = (Uint8*)sha.Message_Digest;
	//				Uint8 pShaB[20];
	//				for (Uint8 i = 0; i < 20; i++)
	//				{
	//					Uint8 nIndex = i/4*4 + 3 - i%4;
	//					pShaB[nIndex] = pShaA[i];
	//				}

	//				int nLength = 0;
	//				char* szAccept = base64(pShaB, sizeof(pShaB), &nLength);

	//				String sReturnData =
	//					ToString("HTTP/1.1 101 Switching Protocols\r\n") +
	//					ToString("Upgrade: websocket\r\n") +
	//					ToString("Connection: Upgrade\r\n") +
	//					ToString("Sec-WebSocket-Accept: ") + ToString(szAccept) + ToString("\r\n") +
	//					ToString("Sec-WebSocket-Protocol: binary\r\n\r\n");

	//				free(szAccept);

	//				/*
	//				 Concretely, if as in the example above, the |Sec-WebSocket-Key|
	// header field had the value "dGhlIHNhbXBsZSBub25jZQ==", the server
	// would concatenate the string "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"
	// to form the string "dGhlIHNhbXBsZSBub25jZQ==258EAFA5-E914-47DA-95CA-
	// C5AB0DC85B11".  The server would then take the SHA-1 hash of this,
	// giving the value 0xb3 0x7a 0x4f 0x2c 0xc0 0x62 0x4f 0x16 0x90 0xf6
	// 0x46 0x06 0xcf 0x38 0x59 0x45 0xb2 0xbe 0xc4 0xea.  This value is
	// then base64-encoded (see Section 4 of [RFC4648]), to give the value
	// "s3pPLMBiTxaQ9kYGzzhZRbK+xOo=".  This value would then be echoed in
	// the |Sec-WebSocket-Accept| header field.*/

	//				send(m_nSocket, sReturnData.c_str(), (int)sReturnData.length(), 0);
	//
	//				m_nDataSize = 0;
	//				m_bInitialRead = false;
	//				m_bWebSocket = true;

	//				printf("Websocket is go!\n");
	//			}
	//		}
	//		else
	//		{
	//			m_bInitialRead = false;
	//		}
	//	}
	//}

	//if (!m_bInitialRead)
	//{
	//	if (m_bWebSocket)
	//	{
	//		if (m_nDataSize < sizeof(Uint16))
	//			return false;
	//
	//		Uint8* p = m_pBuffer;
	//		Uint32 nReadOffset = 0;

	//		//Uint16 nBitmask = *(Uint16*)p;
	//
	//		Uint8 nByte0 = m_pBuffer[0];
	//		Uint8 nByte1 = m_pBuffer[1];

	//			// reverse endians!
	//			Uint8 fin = Uint8((nByte0 >> 7) & 0x1);
	//			Uint8 rsv1 = Uint8((nByte0 >> 6) & 0x1);
	//			Uint8 rsv2 = Uint8((nByte0 >> 5) & 0x1);
	//			Uint8 rsv3 = Uint8((nByte0 >> 4) & 0x1);
	//			Uint8 opcode = Uint8((nByte0 >> 0) & 0xF);
	//
	//			Uint8 mask = Uint8((nByte1 >> 7) & 0x1);
	//			Uint32 payload_len = Uint8((nByte1 >> 0) & 0x7F);

	//		p += sizeof(Uint16);
	//		nReadOffset += sizeof(Uint16);

	//		POW2_ASSERT(payload_len != 127);

	//		if (payload_len == 126)
	//		{
	//			Uint8 nTemp[2];
	//			nTemp[0] = p[1];
	//			nTemp[1] = p[0];
	//			payload_len = *(Uint16*)nTemp;

	//			p += sizeof(Uint16);
	//			nReadOffset += sizeof(Uint16);
	//		}

	//		const Uint32 MASK_SIZE = 4;
	//		Uint8 masking_key[MASK_SIZE];
	//		if (mask)
	//		{
	//			if (m_nDataSize < nReadOffset + sizeof(Uint8)*MASK_SIZE)
	//				return false;
	//			for (Uint32 i = 0; i < MASK_SIZE; i++)
	//				masking_key[i] = *p++;
	//			nReadOffset += sizeof(Uint8)*MASK_SIZE;
	//		}

	//		if (m_nDataSize < nReadOffset + payload_len)
	//			return false;

	//		Uint8* pPayload = p;
	//		for (Uint32 i = 0; i < payload_len; i++)
	//			*p++ ^= masking_key[i % MASK_SIZE];
	//		nReadOffset += payload_len;

	//		if (opcode == 0x2)
	//		{
	//			Uint32 nBlobSize = *(Uint32*)pPayload;
	//			POW2_ASSERT(nBlobSize == payload_len - sizeof(Uint32));
	//			pTempBlob->Clear();
	//			pTempBlob->PackData(pPayload + sizeof(Uint32), nBlobSize);
	//			pTempBlob->SetOffset(0);
	//		}

	//		Uint32 nRemainingData = m_nDataSize - nReadOffset;
	//		if (nRemainingData > 0)
	//			memmove(m_pBuffer, m_pBuffer + nReadOffset, nRemainingData);
	//		m_nDataSize = nRemainingData;

	//		if (opcode == 0x2)
	//			return true;
	//		else
	//			return false;
	//	}
	//	else
	//	{

	/*Uint32 nSize = nbBlob_GetSize(pBlob);
	   nbClientSocket_Send(pClientSocket, &nSize, sizeof(Uint32));
	   nbClientSocket_Send(pClientSocket, nbBlob_GetData(pBlob), nbBlob_GetSize(pBlob));*/

	if (pClientSocket->nReadDataSize > sizeof(Uint32))
	{
		Uint32 nBlobSize = *(Uint32*)pClientSocket->pReadBuffer;
		if (pClientSocket->nReadDataSize >= nBlobSize + sizeof(Uint32))
		{
			Uint32 nRemainingData;

			nbBlob_Clear(pBlob);
			nbBlob_PackData(pBlob, pClientSocket->pReadBuffer + sizeof(Uint32), nBlobSize);
			nbBlob_SetOffset(pBlob, 0);

			nRemainingData = pClientSocket->nReadDataSize - (nBlobSize + sizeof(Uint32));
			if (nRemainingData > 0)
				memmove(pClientSocket->pReadBuffer, pClientSocket->pReadBuffer + nBlobSize + sizeof(Uint32), nRemainingData);
			pClientSocket->nReadDataSize = nRemainingData;
			return TEH_TRUE;
		}
	}
	/*	}
	   }
	   return false;*/
	return TEH_FALSE;
}

Bool nbClientSocket_GetConnected(nbClientSocket* pClientSocket)
{
	return pClientSocket->nState == NB_CLIENT_SOCKET_STATE_CONNECTED;
}

Bool nbClientSocket_GetClosed(nbClientSocket* pClientSocket)
{
	return pClientSocket->nState == NB_CLIENT_SOCKET_STATE_CLOSED;
}

Bool nbClientSocket_Pending(nbClientSocket* pClientSocket)
{
	if (pClientSocket->nState != NB_CLIENT_SOCKET_STATE_CONNECTED && pClientSocket->nState != NB_CLIENT_SOCKET_STATE_CLOSED)
		return TEH_TRUE;

	if (pClientSocket->nWriteDataSize > 0 || /*pClientSocket->nReadDataSize > 0 ||*/ pClientSocket->nEncryptedWriteDataSize > 0 || pClientSocket->nEncryptedReadDataSize > 0)
		return TEH_TRUE;
	return TEH_FALSE;
}

nbClientSocket* nbClientSocket_SubCreate(void)
{
	nbClientSocket* pClientSocket = (nbClientSocket*)nbMalloc(sizeof(nbClientSocket));

	pClientSocket->nSocket = -1;

	pClientSocket->nWriteBufferSize = NB_CLIENT_SOCKET_INITIAL_BUFFER_SIZE;
	pClientSocket->pWriteBuffer = (Uint8*)nbMalloc(pClientSocket->nWriteBufferSize);

	pClientSocket->nReadBufferSize = NB_CLIENT_SOCKET_INITIAL_BUFFER_SIZE;
	pClientSocket->pReadBuffer = (Uint8*)nbMalloc(pClientSocket->nReadBufferSize);

	pClientSocket->nEncryptedWriteBufferSize = NB_CLIENT_SOCKET_INITIAL_BUFFER_SIZE;
	pClientSocket->pEncryptedWriteBuffer = (Uint8*)nbMalloc(pClientSocket->nEncryptedWriteBufferSize);

	pClientSocket->nEncryptedReadBufferSize = NB_CLIENT_SOCKET_INITIAL_BUFFER_SIZE;
	pClientSocket->pEncryptedReadBuffer = (Uint8*)nbMalloc(pClientSocket->nEncryptedReadBufferSize);

	return pClientSocket;
}

void nbClientSocket_SubDestroy(nbClientSocket* pClientSocket)
{
	if (pClientSocket->nSocket >= 0)
	{
		#ifdef NB_WINDOWS
			shutdown(pClientSocket->nSocket, SD_BOTH);
			closesocket(pClientSocket->nSocket);
		#else
			//shutdown(pClientSocket->nSocket, SHUT_RDWR);
			close(pClientSocket->nSocket);
		#endif
	}

	nbFree(pClientSocket->pWriteBuffer);
	nbFree(pClientSocket->pReadBuffer);
	nbFree(pClientSocket->pEncryptedWriteBuffer);
	nbFree(pClientSocket->pEncryptedReadBuffer);

	nbFree(pClientSocket);
}

void nbClientSocket_Update(nbClientSocket* pClientSocket)
{
	if (pClientSocket->nSocket >= 0)
	{
		switch (pClientSocket->nState)
		{
			case NB_CLIENT_SOCKET_STATE_CONNECT:
			{
				fd_set writeSet;
				struct timeval timeout;
				FD_ZERO(&writeSet);
				FD_SET(pClientSocket->nSocket, &writeSet);
				memset(&timeout, 0, sizeof(timeout));

				if (select(pClientSocket->nSocket + 1, NULL, &writeSet, NULL, &timeout) != -1)
				{
					if (FD_ISSET(pClientSocket->nSocket, &writeSet))
					{
						pClientSocket->nState = NB_CLIENT_SOCKET_STATE_SSL_HANDSHAKE;
					}
				}
				break;
			}
			case NB_CLIENT_SOCKET_STATE_SSL_HANDSHAKE:
			{
				#ifdef NB_SOCKET_SSL
					int ret;
					if ((ret = mbedtls_ssl_handshake( &pClientSocket->ssl )) != 0 )
					{
						if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE )
						{
							nbAssert(TEH_FALSE);
							//mbedtls_printf( " failed\n  ! mbedtls_ssl_handshake returned -0x%x\n\n", -ret );
							//goto exit;
						}
						break;
					}
				#endif

				// handshake complete
				pClientSocket->nState = NB_CLIENT_SOCKET_STATE_CONNECTED;
			}
			default:
			{
			}
		}
	}

	nbClientSocket_WriteFlush(pClientSocket);
	nbClientSocket_ReadFlush(pClientSocket);
}

void nbClientSocket_WriteFlush(nbClientSocket* pClientSocket)
{
	if (pClientSocket->nSocket >= 0)
	{
		if (pClientSocket->nState != NB_CLIENT_SOCKET_STATE_CONNECT && pClientSocket->nState != NB_CLIENT_SOCKET_STATE_CLOSED)
		{
			if (pClientSocket->nWriteDataSize > 0)
			{
				#ifdef NB_SOCKET_SSL
					int ret;
					ret = mbedtls_ssl_write( &pClientSocket->ssl, pClientSocket->pWriteBuffer, pClientSocket->nWriteDataSize);
					nbAssert(ret >= 0 && (Uint32)ret == pClientSocket->nWriteDataSize);
				#else
					nbClientSocket_BufferWrite(&pClientSocket->nEncryptedWriteDataSize, &pClientSocket->nEncryptedWriteBufferSize, &pClientSocket->pEncryptedWriteBuffer, pClientSocket->pWriteBuffer, pClientSocket->nWriteDataSize);
				#endif
				pClientSocket->nWriteDataSize = 0;
			}

			if (pClientSocket->nEncryptedWriteDataSize > 0)
			{
				fd_set writeSet;
				struct timeval timeout;
				FD_ZERO(&writeSet);
				FD_SET(pClientSocket->nSocket, &writeSet);
				memset(&timeout, 0, sizeof(timeout));

				if (select(pClientSocket->nSocket + 1, NULL, &writeSet, NULL, &timeout) != -1)
				{
					if (FD_ISSET(pClientSocket->nSocket, &writeSet))
					{
						int nSendSize = send(pClientSocket->nSocket, (char*)pClientSocket->pEncryptedWriteBuffer, pClientSocket->nEncryptedWriteDataSize, 0);
						nbAssert(nSendSize >= 0);
						nbAssert((Uint32)nSendSize <= pClientSocket->nEncryptedWriteDataSize);

						if ((Uint32)nSendSize < pClientSocket->nEncryptedWriteDataSize)
							memmove(pClientSocket->pEncryptedWriteBuffer, pClientSocket->pEncryptedWriteBuffer + nSendSize, pClientSocket->nEncryptedWriteDataSize - (Uint32)nSendSize);

						pClientSocket->nEncryptedWriteDataSize = pClientSocket->nEncryptedWriteDataSize - nSendSize;
					}
				}
			}
		}
	}
}

void nbClientSocket_ReadFlush(nbClientSocket* pClientSocket)
{
	if (pClientSocket->nSocket >= 0)
	{
		while (TEH_TRUE)
		{
			if (pClientSocket->nState == NB_CLIENT_SOCKET_STATE_CONNECT || pClientSocket->nState == NB_CLIENT_SOCKET_STATE_CLOSED)
				break;
			{
				fd_set readSet;
				struct timeval timeout;

				FD_ZERO(&readSet);
				FD_SET(pClientSocket->nSocket, &readSet);
				memset(&timeout, 0, sizeof(timeout));

				if (select(pClientSocket->nSocket + 1, &readSet, NULL, NULL, &timeout) != -1)
				{
					if (FD_ISSET(pClientSocket->nSocket, &readSet))
					{
						Int32 nReadSize;

						if (pClientSocket->nEncryptedReadBufferSize == pClientSocket->nEncryptedReadDataSize)
						{
							Uint8* pNewBuffer;
							pClientSocket->nEncryptedReadBufferSize <<= 1;
							pNewBuffer = (Uint8*)nbMalloc(pClientSocket->nEncryptedReadBufferSize);
							memcpy(pNewBuffer, pClientSocket->pEncryptedReadBuffer, pClientSocket->nEncryptedReadDataSize);
							nbFree(pClientSocket->pEncryptedReadBuffer);
							pClientSocket->pEncryptedReadBuffer = pNewBuffer;
						}

						nReadSize = (Int32)recv(pClientSocket->nSocket, (char*)pClientSocket->pEncryptedReadBuffer + pClientSocket->nEncryptedReadDataSize, pClientSocket->nEncryptedReadBufferSize - pClientSocket->nEncryptedReadDataSize, 0);
						if (nReadSize <= 0)
						{
							nbClientSocket_Close(pClientSocket);
							//	return;
						}
						else
						{
							pClientSocket->nEncryptedReadDataSize += nReadSize;
						}
						continue;
					}
				}
				break;
			}
		}
	}

	// data waiting for ssl decrypt
	if (pClientSocket->nEncryptedReadBufferSize > 0)
	{
		// buffer is full, expand
		if (pClientSocket->nReadDataSize == pClientSocket->nReadBufferSize)
		{
			Uint8* pOldBuffer = pClientSocket->pReadBuffer;
			pClientSocket->nReadBufferSize <<= 1;

			pClientSocket->pReadBuffer = nbMalloc(pClientSocket->nReadBufferSize);
			memcpy(pClientSocket->pReadBuffer, pOldBuffer, pClientSocket->nReadDataSize);
			nbFree(pOldBuffer);
		}

		{
			#ifdef NB_SOCKET_SSL
				int ret;
				ret = mbedtls_ssl_read( &pClientSocket->ssl, pClientSocket->pReadBuffer + pClientSocket->nReadDataSize, pClientSocket->nReadBufferSize - pClientSocket->nReadDataSize);

				nbAssert(ret >= 0 || ret == MBEDTLS_ERR_SSL_WANT_READ || ret == MBEDTLS_ERR_SSL_WANT_WRITE);

				if (ret >= 0)
					pClientSocket->nReadDataSize += ret;
			#else
				pClientSocket->nReadDataSize += nbClientSocket_BufferRead(&pClientSocket->nEncryptedReadDataSize, &pClientSocket->nEncryptedReadBufferSize, &pClientSocket->pEncryptedReadBuffer, pClientSocket->pReadBuffer + pClientSocket->nReadDataSize, pClientSocket->nReadBufferSize - pClientSocket->nReadDataSize);
			#endif
		}
	}
}

#ifdef NB_SOCKET_SSL
	int nbClientSocket_SslWrite(void* pPointer, const unsigned char*pBuffer, size_t nLength)
	{
		nbClientSocket* pClientSocket = (nbClientSocket*)pPointer;
		nbClientSocket_BufferWrite(&pClientSocket->nEncryptedWriteDataSize, &pClientSocket->nEncryptedWriteBufferSize, &pClientSocket->pEncryptedWriteBuffer, pBuffer, nLength);
		return nLength;
	}

	int nbClientSocket_SslRead(void* pPointer, unsigned char*pBuffer, size_t nLength)
	{
		Uint32 nReadSize;
		nbClientSocket* pClientSocket = (nbClientSocket*)pPointer;
		nReadSize = nbClientSocket_BufferRead(&pClientSocket->nEncryptedReadDataSize, &pClientSocket->nEncryptedReadBufferSize, &pClientSocket->pEncryptedReadBuffer, pBuffer, nLength);
		if (nReadSize == 0)
			return MBEDTLS_ERR_SSL_WANT_READ;
		return nReadSize;
	}

#endif

Uint32 nbClientSocket_BufferRead(Uint32* pDataSize, Uint32* pBufferSize, Uint8** pBuffer, Uint8* pReadBuffer, Uint32 nReadBufferSize)
{
	Uint32 nReadSize;
	Uint32 nNewSize;

	nReadSize = (*pDataSize);
	if (nReadSize > nReadBufferSize)
		nReadSize = nReadBufferSize;

	memcpy(pReadBuffer, (*pBuffer), nReadSize);

	nNewSize = (*pDataSize) - nReadSize;
	if (nNewSize > 0)
		memmove((*pBuffer), (*pBuffer) + nReadSize, nNewSize);

	(*pDataSize) = nNewSize;

	return nReadSize;
}

Uint32 nbClientSocket_BufferWrite(Uint32* pDataSize, Uint32* pBufferSize, Uint8** pBuffer, const Uint8* pWriteBuffer, Uint32 nWriteBufferSize)
{
	if ((*pDataSize) + nWriteBufferSize > (*pBufferSize))
	{
		Uint8* pOldBuffer = (*pBuffer);
		while ((*pDataSize) + nWriteBufferSize > (*pBufferSize))
			(*pBufferSize) <<= 1;

		(*pBuffer) = (Uint8*)nbMalloc((*pBufferSize));
		memcpy((*pBuffer), pOldBuffer, (*pDataSize));
		nbFree(pOldBuffer);
	}

	memcpy((*pBuffer) + (*pDataSize), pWriteBuffer, nWriteBufferSize);
	(*pDataSize) += nWriteBufferSize;

	return nWriteBufferSize;
}

void nbClientSocket_Close(nbClientSocket* pClientSocket)
{
	nbClientSocket_WriteFlush(pClientSocket);

	//xxxpClientSocket->bDisconnected = TEH_TRUE;
	#ifdef NB_WINDOWS
		shutdown(pClientSocket->nSocket, SD_BOTH);
		closesocket(pClientSocket->nSocket);
	#else
		//shutdown(pClientSocket->nSocket, SHUT_RDWR);
		close(pClientSocket->nSocket);
	#endif
	pClientSocket->nSocket = -1;

	pClientSocket->nState = NB_CLIENT_SOCKET_STATE_CLOSED;
}
