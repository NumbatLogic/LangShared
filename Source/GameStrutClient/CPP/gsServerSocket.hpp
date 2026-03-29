#pragma once
#include "../../Vector/CPP/Vector.hpp"

namespace NumbatLogic
{
	class gsBlob;
	class gsClientSocket;
	class gsServerSocket
	{
		public:
			gsServerSocket();
			virtual ~gsServerSocket();
			
			void Start(int port);
			void Stop();
			void Update();
			bool Pending();
			int GetNumClient();
			gsClientSocket* Accept();

			bool Broadcast(gsBlob* pBlob);

		protected:
			bool ReadyToAcceptListen();
			void DrainIncomingConnections();

			int m_nSocket;
			int m_nPort;
			unsigned int m_nNextClientId;

			Vector<gsClientSocket*>* m_pClientSocketVector;
			Vector<gsClientSocket*>* m_pAcceptReturnQueue;
	};
}