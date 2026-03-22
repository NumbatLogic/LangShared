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
#line 0 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	class Sync_ClientRoomHandler_Server : public gsServer
	{
		public: Sync_ClientRoomHandler_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath);
#line 9 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public: virtual gsServerClient* OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
	};
#line 15 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	class Sync_ClientRoomHandler_ServerClient : public gsServerClient
	{
		public: Sync_ClientRoomHandler_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
#line 21 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public: virtual void OnInitialJoin();
	};
#line 34 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	class Sync_ClientRoomHandler_ClientRoom : public gsClientRoom
	{
		public: static const char* ROOM_TYPE;
		public: static const unsigned int ROOM_TYPE_HASH = 3638174234;
#line 39 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public: unsigned int m_nTestValue;
#line 41 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public: Sync_ClientRoomHandler_ClientRoom(unsigned int nRoomId, bool bPrimary, gsBlob* pJoinBlob, gsClient* pClient);
#line 46 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		protected: static void OnRoomTest(gsClient* pClient, gsClientRoom* pRoom, unsigned int nSyncId, gsBlob* pMessageBlob);
	};
#line 54 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	class Sync_ClientRoomHandler_Client : public gsClient
	{
		public: Sync_ClientRoomHandler_Client(const char* sxAddress, unsigned short nPort, unsigned short nVersion);
#line 60 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public: virtual gsClientRoom* OnRoomJoin(unsigned int nRoomId, unsigned int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob);
	};
#line 68 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	class Sync_ClientRoomHandler
	{
		public: static void Run();
	};
}

