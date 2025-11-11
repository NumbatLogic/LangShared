#pragma once
#include "../../InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class gsBlob;
	class gsClientSocket
	{
		public:
			gsClientSocket();
			virtual ~gsClientSocket();
			
			void Connect(const char* host, int port);
			void Disconnect();
			void Update();
			bool Pending();
			bool GetConnected();

			bool Send(gsBlob* pBlob);
			gsBlob* Receive();

			void SetServerClientSocket(int nSocket, unsigned int nClientSocketId);
			unsigned int GetClientSocketId() const { return m_nClientSocketId; }

		protected:
			int m_nSocket;
			InternalString* m_pHost;
			int m_nPort;
			bool m_bConnected;
			unsigned int m_nClientSocketId;  // Unique identifier for this client socket

			// Buffer management
			static const int INITIAL_BUFFER_SIZE = 1024;
			unsigned int m_nWriteDataSize;
			unsigned int m_nWriteBufferSize;
			unsigned char* m_pWriteBuffer;

			unsigned int m_nReadDataSize;
			unsigned int m_nReadBufferSize;
			unsigned char* m_pReadBuffer;
	};
} 