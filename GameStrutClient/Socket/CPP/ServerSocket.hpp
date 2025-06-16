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

            virtual bool Send(Blob* pBlob);
			virtual Blob* Receive();

        protected:
            int m_nSocket;
			int m_nPort;

            Vector<ClientSocket*>* m_pClientSocketVector;
	};
}