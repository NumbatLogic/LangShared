#pragma once

#include "gsClient.hpp"
#include "gsSync.hpp"
#include "../Vector/OwnedVector.hpp"
#include "gsClientRoom.hpp"

namespace NumbatLogic
{
	class gsClient;
	class gsBlob;
	class gsClientRoom;
	class gsSyncInner;
	class gsClient_SyncHandler;
	class gsSync;
	template <class T>
	class OwnedVector;
	class gsClientSocket;
	class InternalString;
}
#line 1 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	class gsClient_SyncHandler
	{
		public: typedef void (SyncHandler)(gsClient* pClient, unsigned int nSyncId, gsBlob* pMessageBlob);
#line 8 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: unsigned int __nHash;
#line 9 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: SyncHandler* __pHandler;
#line 11 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: gsClient_SyncHandler(unsigned int nHash, SyncHandler* pHandler);
	};
#line 18 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	class gsClient
	{
#line 20 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: enum State
		{
			CONNECT,
			HANDSHAKE,
			CONNECTED,
			DISCONNECTED,
			ERRORED,
		};

#line 28 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: gsClient(const char* sxAddress, unsigned short nPort, unsigned short nVersion);
#line 43 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: virtual ~gsClient();
#line 48 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: void Update();
#line 249 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: static void __OnRoomJoin(gsClient* pClient, unsigned int nSyncId, gsBlob* pMessageBlob);
#line 270 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: static void __OnRoomLeave(gsClient* pClient, unsigned int nSyncId, gsBlob* pMessageBlob);
#line 288 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: void RegisterHandler(unsigned int nMessageType, gsClient_SyncHandler::SyncHandler* pHandler);
#line 298 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: gsClient_SyncHandler* __GetSyncHandler(unsigned int nMessageType);
#line 309 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: void SyncSend(gsSync* pSync, const char* sxSyncType, gsBlob* pBlob, gsSync::Response eResponse, gsClientRoom* pRoom);
#line 337 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: bool GetPending();
#line 358 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: bool HasActiveSync();
#line 369 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: bool HasActiveSyncByRoom(gsClientRoom* pRoom);
#line 380 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: bool HasRoomChangeSyncInFlight(gsClientRoom* pRoom);
#line 392 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: virtual gsClientRoom* OnRoomJoin(unsigned int nRoomId, unsigned int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob);
#line 400 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: static const unsigned short MAGIC_WORD = 619;
#line 402 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: OwnedVector<gsClientRoom*>* __pRoomVector;
#line 405 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: gsClientSocket* __pClientSocket;
#line 406 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: unsigned short __nVersion;
#line 408 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: unsigned int __nClientId;
#line 410 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: unsigned int __nLastSyncId;
#line 411 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: OwnedVector<gsSyncInner*>* __pSyncInnerVector;
#line 412 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: OwnedVector<gsClient_SyncHandler*>* __pSyncHandlerVector;
#line 415 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: State __eState;
#line 416 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: InternalString* __sErrorMessage;
#line 418 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: static unsigned int __ROOM_JOIN_HASH;
#line 419 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: static unsigned int __ROOM_LEAVE_HASH;
#line 423 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: gsClientRoom* GetRoomByRoomId(unsigned int nRoomId);
#line 434 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: void ErrorDisconnect(const char* sxErrorMessage);
#line 443 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: const char* GetErrorMessage();
#line 449 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		public: gsSyncInner* GetSyncInnerBySyncId(unsigned int nSyncId);
	};
}

