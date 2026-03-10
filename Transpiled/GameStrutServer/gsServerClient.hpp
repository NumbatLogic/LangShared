#pragma once

#include "../GameStrutClient/gsSync.hpp"
#include "../GameStrutClient/gsClient.hpp"
#include "../../Vector/CPP/Vector.hpp"
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
#line 0 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
	class gsServerClient
	{
#line 5 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: void Send(gsServerRoom* pRoom, unsigned int nMessageTypeHash, gsBlob* pBlob);
#line 23 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: virtual void OnInitialJoin();
#line 30 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: gsServerRoom* GetRoomByRoomId(unsigned int nRoomId);
#line 43 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: void SyncRespond(unsigned int nSyncId, unsigned char nResult, gsSync::Response eResponse, gsBlob* pBlob);
#line 87 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: unsigned int __nClientId;
#line 88 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: gsServer* __pServer;
#line 89 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: gsClientSocket* __pClientSocket;
#line 90 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: gsClient::State __eState;
#line 91 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: Vector<gsServerRoom*>* __pRoomVector;
#line 93 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: unsigned int __nLastSyncId;
#line 95 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: gsServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
#line 104 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: void __Update();
#line 230 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: void ErrorDisconnect(const char* sxErrorMessage);
#line 3 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: virtual ~gsServerClient();
	};
}

