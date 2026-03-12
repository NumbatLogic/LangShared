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
#line 0 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
	class gsServer
	{
		public: gsServer(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath);
#line 18 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: virtual ~gsServer();
#line 23 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: void Update();
#line 79 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: bool Pending();
#line 84 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: virtual gsServerClient* OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
#line 89 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: virtual gsServerRoom* OnCreateRoom(unsigned int nRoomId, unsigned int nRoomType, gsBlob* pCreateBlob);
#line 95 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: virtual void Auth(gsBlob* pAuthBlob, gsClientSocket* pClientSocket);
#line 103 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: InternalString* __sAddress;
		public: unsigned short __nPort;
		public: unsigned short __nVersion;
#line 107 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: gsServerSocket* __pServerSocket;
		public: OwnedVector<gsServerClient*>* __pClientVector;
		public: OwnedVector<gsServerRoom*>* __pRoomVector;
#line 111 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: unsigned int __nLastClientId;
		public: unsigned int __nLastRoomId;
#line 115 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: void __ClientJoin(gsServerClient* pClient, gsServerRoom* pRoom);
#line 130 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public: gsServerRoom* __CreateRoom(const char* sxRoomType, gsBlob* pCreateBlob);
	};
}

