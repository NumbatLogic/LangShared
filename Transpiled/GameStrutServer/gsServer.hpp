#pragma once

#include "../Vector/OwnedVector.hpp"
#include "gsServerClient.hpp"
#include "gsServerRoom.hpp"

namespace NumbatLogic
{
	class gsServerRoom;
	class gsServerClient;
	class gsClientSocket;
	class gsServer;
	class gsBlob;
	class InternalString;
	class gsServerSocket;
	template <class T>
	class OwnedVector;
}
#line 1 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
	class gsServer
	{
#line 6 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: gsServer(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath);
#line 19 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: virtual ~gsServer();
#line 24 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: void Update();
#line 80 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: bool Pending();
#line 85 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: virtual gsServerClient* OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
#line 90 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: virtual gsServerRoom* OnCreateRoom(unsigned int nRoomId, unsigned int nRoomType, gsBlob* pCreateBlob);
#line 96 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: virtual void Auth(gsBlob* pAuthBlob, gsClientSocket* pClientSocket);
#line 104 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: InternalString* __sAddress;
#line 105 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: unsigned short __nPort;
#line 106 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: unsigned short __nVersion;
#line 108 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: gsServerSocket* __pServerSocket;
#line 109 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: OwnedVector<gsServerClient*>* __pClientVector;
#line 110 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: OwnedVector<gsServerRoom*>* __pRoomVector;
#line 112 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: unsigned int __nLastClientId;
#line 113 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: unsigned int __nLastRoomId;
#line 116 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: void __ClientJoin(gsServerClient* pClient, gsServerRoom* pRoom);
#line 131 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: gsServerRoom* __CreateRoom(const char* sxRoomType, gsBlob* pCreateBlob);
	};
}

