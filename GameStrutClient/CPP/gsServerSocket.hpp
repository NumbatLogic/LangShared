#pragma once

#include "../../Vector/CPP/Vector.hpp"
#include "gsSocket.hpp"

namespace NumbatLogic
{
    class gsClientSocket;
	class gsServerSocket : gsSocket
	{
		public:
			gsServerSocket();
			virtual ~gsServerSocket();
			
		    void Start(int port);
            void Stop();
            void Update();
            bool Pending();
            gsClientSocket* Accept();

            void Send(gsBlob* pBlob, unsigned int clientSocketId);

        protected:
            using gsSocket::Send;
            int m_nSocket;
			int m_nPort;
            unsigned int m_nNextClientId;

            Vector<gsClientSocket*>* m_pClientSocketVector;
	};
}