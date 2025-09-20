#pragma once
#include "gsSocket.hpp"
#include "../../InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
    class gsClientSocket : public gsSocket
    {
        public:
            gsClientSocket();
            virtual ~gsClientSocket();
            
            void Connect(const char* host, int port);
            void Disconnect();
            void Update();
            bool Pending();
            bool GetConnected();

            virtual bool Send(gsBlob* pBlob) override;
            virtual gsBlob* Receive() override;

            void SetAcceptedSocket(int socket);
            unsigned int GetClientSocketId() const { return m_nClientSocketId; }
            void SetClientSocketId(unsigned int clientSocketId) { m_nClientSocketId = clientSocketId; }

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