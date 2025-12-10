#pragma once

#include "../GameStrutClient/gsClient.hpp"
#include "../../Vector/CPP/Vector.hpp"
#include "gsServerRoom.hpp"

namespace NumbatLogic
{
	class gsServerRoom;
	class gsBlob;
	class gsServer;
	class gsClientSocket;
	class gsClient;
	template <class T>
	class Vector;
}
namespace NumbatLogic
{
	class gsServerClient
	{
		public: void Send(gsServerRoom* pRoom, unsigned int nMessageTypeHash, gsBlob* pBlob);
		public: virtual void OnInitialJoin();
		public: gsServerRoom* GetRoomByRoomId(unsigned int nRoomId);
		public: void SyncRespond(unsigned int nSyncId, gsBlob* pBlob);
		public: unsigned int __nClientId;
		public: gsServer* __pServer;
		public: gsClientSocket* __pClientSocket;
		public: gsClient::State __eState;
		public: Vector<gsServerRoom*>* __pRoomVector;
		public: unsigned int __nLastSyncId;
		public: gsServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
		public: void __Update();
		public: void ErrorDisconnect(const char* sxErrorMessage);
		public: virtual ~gsServerClient();
	};
}

