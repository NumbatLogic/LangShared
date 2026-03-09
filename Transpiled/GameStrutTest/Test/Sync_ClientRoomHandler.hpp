#pragma once

#include "../../GameStrutServer/gsServer.hpp"
#include "../../GameStrutServer/gsServerClient.hpp"
#include "../../GameStrutClient/gsClientRoom.hpp"
#include "../../GameStrutClient/gsClient.hpp"

namespace NumbatLogic
{
	class gsServerClient;
	class gsClientSocket;
	class gsServer;
	class gsServerRoom;
	class gsBlob;
	class gsClient;
	class gsClientRoom;
}
#line 1 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	class Sync_ClientRoomHandler_Server : public gsServer
	{
#line 6 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public: Sync_ClientRoomHandler_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath);
#line 10 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public: virtual gsServerClient* OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
	};
#line 16 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	class Sync_ClientRoomHandler_ServerClient : public gsServerClient
	{
#line 18 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public: Sync_ClientRoomHandler_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
#line 22 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public: virtual void OnInitialJoin();
	};
#line 35 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	class Sync_ClientRoomHandler_ClientRoom : public gsClientRoom
	{
#line 37 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public: static const char* ROOM_TYPE;
#line 38 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public: static const unsigned int ROOM_TYPE_HASH = 3638174234;
#line 40 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public: unsigned int m_nTestValue;
#line 42 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public: Sync_ClientRoomHandler_ClientRoom(unsigned int nRoomId, bool bPrimary, gsBlob* pJoinBlob, gsClient* pClient);
#line 47 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		protected: static void OnRoomTest(gsClient* pClient, gsClientRoom* pRoom, unsigned int nSyncId, gsBlob* pMessageBlob);
	};
#line 55 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	class Sync_ClientRoomHandler_Client : public gsClient
	{
#line 57 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public: Sync_ClientRoomHandler_Client(const char* sxAddress, unsigned short nPort, unsigned short nVersion);
#line 61 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public: virtual gsClientRoom* OnRoomJoin(unsigned int nRoomId, unsigned int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob);
	};
#line 69 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	class Sync_ClientRoomHandler
	{
#line 71 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public: static void Run();
	};
}

