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
	class gsSync;
	class gsClientRoom;
}
#line 0 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	class Sync_ServerRoomHandler_Error_Server : public gsServer
	{
		public: Sync_ServerRoomHandler_Error_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath);
#line 9 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public: virtual gsServerClient* OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
	};
#line 15 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	class Sync_ServerRoomHandler_Error_ServerClient : public gsServerClient
	{
		public: Sync_ServerRoomHandler_Error_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
#line 21 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public: virtual void OnInitialJoin();
	};
#line 30 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	class Sync_ServerRoomHandler_Error_ClientRoom : public gsClientRoom
	{
		public: static const char* ROOM_TYPE;
		public: static const unsigned int ROOM_TYPE_HASH = 3685084777;
#line 35 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public: Sync_ServerRoomHandler_Error_ClientRoom(unsigned int nRoomId, bool bPrimary, gsBlob* pJoinBlob, gsClient* pClient);
	};
#line 40 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	class Sync_ServerRoomHandler_Error_Client : public gsClient
	{
		public: gsSync* __pDummySync;
#line 44 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public: Sync_ServerRoomHandler_Error_Client(const char* sxAddress, unsigned short nPort, unsigned short nVersion);
#line 49 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public: virtual gsClientRoom* OnRoomJoin(unsigned int nRoomId, unsigned int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob);
#line 40 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public: virtual ~Sync_ServerRoomHandler_Error_Client();
	};
#line 63 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	class Sync_ServerRoomHandler_Error
	{
		public: static void Run();
	};
}

