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
#line 0 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
	class gsClient_SyncHandler
	{
		public: typedef void (SyncHandler)(gsClient* pClient, unsigned int nSyncId, gsBlob* pMessageBlob);
#line 7 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: unsigned int __nHash;
		public: SyncHandler* __pHandler;
#line 10 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: gsClient_SyncHandler(unsigned int nHash, SyncHandler* pHandler);
	};
#line 17 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
	class gsClient
	{
		public: enum State
		{
			CONNECT,
			HANDSHAKE,
			CONNECTED,
			DISCONNECTED,
			ERRORED,
		};

#line 27 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: gsClient(const char* sxAddress, unsigned short nPort, unsigned short nVersion);
#line 42 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: virtual ~gsClient();
#line 47 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: void Update();
#line 248 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: static void __OnRoomJoin(gsClient* pClient, unsigned int nSyncId, gsBlob* pMessageBlob);
#line 269 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: static void __OnRoomLeave(gsClient* pClient, unsigned int nSyncId, gsBlob* pMessageBlob);
#line 287 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: void RegisterHandler(unsigned int nMessageType, gsClient_SyncHandler::SyncHandler* pHandler);
#line 297 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: gsClient_SyncHandler* __GetSyncHandler(unsigned int nMessageType);
#line 308 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: void SyncSend(gsSync* pSync, const char* sxSyncType, gsBlob* pBlob, gsSync::Response eResponse, gsClientRoom* pRoom);
#line 336 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: bool GetPending();
#line 357 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: bool HasActiveSync();
#line 368 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: bool HasActiveSyncByRoom(gsClientRoom* pRoom);
#line 379 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: bool HasRoomChangeSyncInFlight(gsClientRoom* pRoom);
#line 391 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: virtual gsClientRoom* OnRoomJoin(unsigned int nRoomId, unsigned int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob);
#line 399 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: static const unsigned short MAGIC_WORD = 619;
#line 401 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: OwnedVector<gsClientRoom*>* __pRoomVector;
#line 404 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: gsClientSocket* __pClientSocket;
		public: unsigned short __nVersion;
#line 407 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: unsigned int __nClientId;
#line 409 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: unsigned int __nLastSyncId;
		public: OwnedVector<gsSyncInner*>* __pSyncInnerVector;
		public: OwnedVector<gsClient_SyncHandler*>* __pSyncHandlerVector;
#line 414 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: State __eState;
		public: InternalString* __sErrorMessage;
#line 417 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: static unsigned int __ROOM_JOIN_HASH;
		public: static unsigned int __ROOM_LEAVE_HASH;
#line 422 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: gsClientRoom* GetRoomByRoomId(unsigned int nRoomId);
#line 433 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: void ErrorDisconnect(const char* sxErrorMessage);
#line 442 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: const char* GetErrorMessage();
#line 448 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		public: gsSyncInner* GetSyncInnerBySyncId(unsigned int nSyncId);
	};
}

