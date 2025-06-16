#pragma once

#if defined __cplusplus
	extern "C" {
#endif

#include <nbBlob/nbBlob.h>
#include <nbPlatformDefine/nbPlatformDefine.h>
#include <nbType/nbType.h>

#ifndef NB_EMSCRIPTEN
	#define NB_SOCKET_SERVER

	// hax disable ssl on cliffypda for now
	#ifndef PROJECT_APPHOME
		#define NB_SOCKET_SSL
	#endif
#endif

typedef struct nbClientSocket nbClientSocket;

#ifdef NB_SOCKET_SERVER
	// Server
	typedef struct nbServerSocket nbServerSocket;
	extern nbServerSocket* nbServerSocket_Create(Uint16 nPort);
	extern void nbServerSocket_Destroy(nbServerSocket* pServerSocket);
	extern void nbServerSocket_Update(nbServerSocket* pServerSocket);
	extern Bool nbServerSocket_Pending(nbServerSocket* pServerSocket);
	extern nbClientSocket* nbServerSocket_Accept(nbServerSocket* pServerSocket);
#endif

// Client
extern nbClientSocket* nbClientSocket_Create(const char* szAddress, Uint16 nPort);
extern void nbClientSocket_Destroy(nbClientSocket* pClientSocket);
extern void nbClientSocket_Update(nbClientSocket* pClientSocket);
extern Bool nbClientSocket_Pending(nbClientSocket* pClientSocket);
extern void nbClientSocket_Write(nbClientSocket* pClientSocket, const Uint8* pData, Uint32 nSize);
extern Uint32 nbClientSocket_Read(nbClientSocket* pClientSocket, Uint8* pData, Uint32 nSize);
extern Uint32 nbClientSocket_GetReadDataSize(nbClientSocket* pClientSocket);
extern void nbClientSocket_WriteBlob(nbClientSocket* pClientSocket, const nbBlob* pBlob);
extern Bool nbClientSocket_ReadBlob(nbClientSocket* pClientSocket, nbBlob* pBlob);
extern Bool nbClientSocket_GetConnected(nbClientSocket* pClientSocket);
extern Bool nbClientSocket_GetClosed(nbClientSocket* pClientSocket);
extern void nbClientSocket_Close(nbClientSocket* pClientSocket);
extern void nbClientSocket_WriteFlush(nbClientSocket* pClientSocket);
extern void nbClientSocket_ReadFlush(nbClientSocket* pClientSocket);

#ifdef NB_SOCKET_SECRET

	#ifdef NB_SOCKET_SSL
		#include "mbedtls/certs.h"
		#include "mbedtls/ctr_drbg.h"
		#include "mbedtls/debug.h"
		#include "mbedtls/entropy.h"
		#include "mbedtls/error.h"
		#include "mbedtls/net_sockets.h"
		#include "mbedtls/ssl.h"
		#include "mbedtls/ssl_cache.h"
		#include "mbedtls/x509.h"

		#include <mbedtls/config.h>
	#endif

	#include <nbVector/nbVector.h>

	#ifdef NB_SOCKET_SERVER
		// nbServerSocket
		struct nbServerSocket
		{
			Int32 nSocket;
			Uint16 nPort;

			nbVector* pClientSocketVector;
		};
	#endif

	// nbClientSocket
	#define NB_CLIENT_SOCKET_STATE_CONNECT 0
	#define NB_CLIENT_SOCKET_STATE_SSL_HANDSHAKE 1
	#define NB_CLIENT_SOCKET_STATE_WEBSOCKET_HANDSHAKE 2
	#define NB_CLIENT_SOCKET_STATE_CONNECTED 3
	#define NB_CLIENT_SOCKET_STATE_CLOSED 4

	#define NB_CLIENT_SOCKET_INITIAL_BUFFER_SIZE 1024
	struct nbClientSocket
	{
		#ifdef NB_SOCKET_SERVER
			nbServerSocket* pServerSocket;
		#endif
		
		Int32 nState;

		#ifdef NB_SOCKET_SSL
			mbedtls_ssl_config conf;
			mbedtls_entropy_context entropy;
			mbedtls_ctr_drbg_context ctr_drbg;
			mbedtls_x509_crt srvcert;
			mbedtls_pk_context pkey;
			mbedtls_ssl_cache_context cache;
			mbedtls_ssl_context ssl;
			
			mbedtls_x509_crt cacert;			// client only
		#endif

		Int32 nSocket;

		Uint32 nWriteDataSize;
		Uint32 nWriteBufferSize;
		Uint8* pWriteBuffer;

		Uint32 nReadDataSize;
		Uint32 nReadBufferSize;
		Uint8* pReadBuffer;

		Uint32 nEncryptedWriteDataSize;
		Uint32 nEncryptedWriteBufferSize;
		Uint8* pEncryptedWriteBuffer;

		Uint32 nEncryptedReadDataSize;
		Uint32 nEncryptedReadBufferSize;
		Uint8* pEncryptedReadBuffer;
	};

	extern nbClientSocket* nbClientSocket_SubCreate(void);
	extern void nbClientSocket_SubDestroy(nbClientSocket* pClientSocket);

	#ifdef NB_SOCKET_SSL
		extern int nbClientSocket_SslWrite(void* pPointer, const unsigned char*pBuffer, size_t nLength);
		extern int nbClientSocket_SslRead(void* pPointer, unsigned char*pBuffer, size_t nLength);
	#endif

	extern Uint32 nbClientSocket_BufferRead(Uint32* pDataSize, Uint32* pBufferSize, Uint8** pBuffer, Uint8* pReadBuffer, Uint32 nReadBufferSize);
	extern Uint32 nbClientSocket_BufferWrite(Uint32* pDataSize, Uint32* pBufferSize, Uint8** pBuffer, const Uint8* pWriteBuffer, Uint32 nWriteBufferSize);

#endif

/* *INDENT-OFF* */
#ifdef __cplusplus
}
#endif
/* *INDENT-ON* */
