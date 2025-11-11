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
			gsClientSocket* Accept();

			bool Broadcast(gsBlob* pBlob);

		protected:
			int m_nSocket;
			int m_nPort;
			unsigned int m_nNextClientId;

			Vector<gsClientSocket*>* m_pClientSocketVector;
	};
}