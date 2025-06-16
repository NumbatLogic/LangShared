#pragma once
#include "../../../Vector/CPP/Vector.hpp"
#include "Socket.hpp"
//#include "ClientSocket.hpp"

namespace NumbatLogic
{
    class ClientSocket;
	class ServerSocket : Socket
	{
		public:
			ServerSocket();
			virtual ~ServerSocket();
			
		    void Start(int port);
            void Stop();
            void Update();
            bool Pending();
            ClientSocket* Accept();

            void Send(Blob* pBlob, unsigned int clientSocketId);

        protected:
            int m_nSocket;
			int m_nPort;
            unsigned int m_nNextClientId;

            Vector<ClientSocket*>* m_pClientSocketVector;
	};
}