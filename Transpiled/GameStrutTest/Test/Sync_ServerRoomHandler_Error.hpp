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
#line 1 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	class Sync_ServerRoomHandler_Error_Server : public gsServer
	{
#line 6 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public: Sync_ServerRoomHandler_Error_Server(const char* sxAddress, unsigned short nPort, unsigned short nVersion, const char* sxDatabasePath);
#line 10 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public: virtual gsServerClient* OnCreateServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
	};
#line 16 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	class Sync_ServerRoomHandler_Error_ServerClient : public gsServerClient
	{
#line 18 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public: Sync_ServerRoomHandler_Error_ServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer);
#line 22 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public: virtual void OnInitialJoin();
	};
#line 31 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	class Sync_ServerRoomHandler_Error_ClientRoom : public gsClientRoom
	{
#line 33 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public: static const char* ROOM_TYPE;
#line 34 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public: static const unsigned int ROOM_TYPE_HASH = 3685084777;
#line 36 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public: Sync_ServerRoomHandler_Error_ClientRoom(unsigned int nRoomId, bool bPrimary, gsBlob* pJoinBlob, gsClient* pClient);
	};
#line 41 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	class Sync_ServerRoomHandler_Error_Client : public gsClient
	{
#line 43 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public: gsSync* __pDummySync;
#line 45 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public: Sync_ServerRoomHandler_Error_Client(const char* sxAddress, unsigned short nPort, unsigned short nVersion);
#line 50 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public: virtual gsClientRoom* OnRoomJoin(unsigned int nRoomId, unsigned int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob);
#line 41 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public: virtual ~Sync_ServerRoomHandler_Error_Client();
	};
#line 64 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	class Sync_ServerRoomHandler_Error
	{
#line 66 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public: static void Run();
	};
}

