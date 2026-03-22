#pragma once

#include "../GameStrutClient/gsSync.hpp"
#include "../GameStrutClient/gsClient.hpp"
#include "../../Source/Vector/CPP/Vector.hpp"
#include "gsServerRoom.hpp"

namespace NumbatLogic
{
	class gsServerRoom;
	class gsBlob;
	class gsSync;
	class gsServer;
	class gsClientSocket;
	class gsClient;
	template <class T>
	class Vector;
}
#line 0 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
	class gsServerClient
	{
		public: void Send(gsServerRoom* pRoom, unsigned int nMessageTypeHash, gsBlob* pBlob);
#line 23 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
		public: virtual void OnInitialJoin();
#line 30 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
		public: gsServerRoom* GetRoomByRoomId(unsigned int nRoomId);
#line 43 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
		public: void SyncRespond(unsigned int nSyncId, unsigned char nResult, gsSync::Response eResponse, gsBlob* pBlob);
#line 87 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
		public: unsigned int __nClientId;
		public: gsServer* __pServer;
		public: gsClientSocket* __pClientSocket;
		public: gsClient::State __eState;
		public: Vector<gsServerRoom*>* __pRoomVector;
#line 93 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
		public: unsigned int __nLastSyncId;
#line 95 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
		public: gsServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
#line 104 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
		public: void __Update();
#line 230 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
		public: void ErrorDisconnect(const char* sxErrorMessage);
#line 3 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServerClient.nll"
		public: virtual ~gsServerClient();
	};
}

