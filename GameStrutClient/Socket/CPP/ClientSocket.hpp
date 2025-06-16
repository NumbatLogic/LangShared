#pragma once
#include "Socket.hpp"
#include "../../../InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
    class ClientSocket : public Socket
    {
        public:
            ClientSocket();
            virtual ~ClientSocket();
            
            void Connect(const char* host, int port);
            void Disconnect();
            void Update();
            bool Pending();

            virtual bool Send(Blob* pBlob) override;
            virtual Blob* Receive() override;

            void SetAcceptedSocket(int socket);

        protected:
            int m_nSocket;
            InternalString* m_pHost;
            int m_nPort;
            bool m_bConnected;

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