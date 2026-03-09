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
#line 1 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
	class gsServerClient
	{
#line 6 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: void Send(gsServerRoom* pRoom, unsigned int nMessageTypeHash, gsBlob* pBlob);
#line 24 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: virtual void OnInitialJoin();
#line 31 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: gsServerRoom* GetRoomByRoomId(unsigned int nRoomId);
#line 44 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: void SyncRespond(unsigned int nSyncId, unsigned char nResult, gsSync::Response eResponse, gsBlob* pBlob);
#line 88 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: unsigned int __nClientId;
#line 89 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: gsServer* __pServer;
#line 90 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: gsClientSocket* __pClientSocket;
#line 91 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: gsClient::State __eState;
#line 92 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: Vector<gsServerRoom*>* __pRoomVector;
#line 94 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: unsigned int __nLastSyncId;
#line 96 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: gsServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
#line 105 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: void __Update();
#line 231 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: void ErrorDisconnect(const char* sxErrorMessage);
#line 4 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		public: virtual ~gsServerClient();
	};
}

