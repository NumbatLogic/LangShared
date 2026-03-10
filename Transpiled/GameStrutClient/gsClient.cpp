#include "gsClient.hpp"
#include "gsClientRoom.hpp"
#include "../Vector/OwnedVector.hpp"
#include "../../GameStrutClient/CPP/gsClientSocket.hpp"
#include "gsSync.hpp"
#include "../../InternalString/CPP/InternalString.hpp"
#include "../../Blob/CPP/Blob.hpp"
#include "../../Assert/CPP/Assert.hpp"
#include "../../Console/CPP/Console.hpp"

namespace NumbatLogic
{
	class gsClient;
	class gsClientRoom;
	template <class T>
	class OwnedVector;
	class gsClientSocket;
	class gsSyncInner;
	class gsClient_SyncHandler;
	class gsBlob;
	class InternalString;
	class Assert;
	class Console;
	class gsSync;
	class gsClientRoom_SyncHandler;
}
#line 0 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
#line 10 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	gsClient_SyncHandler::gsClient_SyncHandler(unsigned int nHash, SyncHandler* pHandler)
	{
		__nHash = 0;
		__pHandler = 0;
#line 12 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__nHash = nHash;
#line 13 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__pHandler = pHandler;
	}

#line 17 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
#line 27 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	gsClient::gsClient(const char* sxAddress, unsigned short nPort, unsigned short nVersion)
	{
		__pRoomVector = 0;
		__pClientSocket = 0;
		__nVersion = 0;
		__nClientId = 0;
		__nLastSyncId = 0;
		__pSyncInnerVector = 0;
		__pSyncHandlerVector = 0;
		__eState = State::CONNECT;
		__sErrorMessage = 0;
#line 29 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__pRoomVector = new OwnedVector<gsClientRoom*>();
#line 31 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__pClientSocket = new gsClientSocket();
#line 32 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__pClientSocket->Connect(sxAddress, nPort);
#line 33 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__nVersion = nVersion;
#line 34 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__eState = State::CONNECT;
#line 35 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__pSyncInnerVector = new OwnedVector<gsSyncInner*>();
#line 36 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__pSyncHandlerVector = new OwnedVector<gsClient_SyncHandler*>();
#line 38 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		RegisterHandler(__ROOM_JOIN_HASH, __OnRoomJoin);
#line 39 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		RegisterHandler(__ROOM_LEAVE_HASH, __OnRoomLeave);
	}

#line 42 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	gsClient::~gsClient()
	{
#line 44 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__pClientSocket->Disconnect();
		if (__pRoomVector) delete __pRoomVector;
		if (__pClientSocket) delete __pClientSocket;
		if (__pSyncInnerVector) delete __pSyncInnerVector;
		if (__pSyncHandlerVector) delete __pSyncHandlerVector;
		if (__sErrorMessage) delete __sErrorMessage;
	}

#line 47 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	void gsClient::Update()
	{
#line 49 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__pClientSocket->Update();
#line 51 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		switch (__eState)
		{
			case State::CONNECT:
			{
#line 55 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (!__pClientSocket->Pending())
				{
#line 57 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					__eState = State::HANDSHAKE;
					gsBlob* pSendBlob = new gsBlob();
#line 60 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					pSendBlob->PackUint16(MAGIC_WORD);
#line 61 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					pSendBlob->PackUint16(__nVersion);
#line 63 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					pSendBlob->PackUint8(0);
					InternalString* sName = new InternalString("cliffya");
#line 66 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					pSendBlob->PackInternalString(sName);
					InternalString* sPassword = new InternalString("password");
#line 69 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					pSendBlob->PackInternalString(sPassword);
#line 71 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					__pClientSocket->Send(pSendBlob);
					if (pSendBlob) delete pSendBlob;
					if (sName) delete sName;
					if (sPassword) delete sPassword;
				}
#line 73 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				break;
			}

			case State::HANDSHAKE:
			{
				gsBlob* pReceiveBlob = __pClientSocket->Receive();
#line 78 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (pReceiveBlob != 0)
				{
					const int INITIAL_SIZE = 2 + 2 + 1 + 4;
#line 82 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					if (pReceiveBlob->GetSize() == INITIAL_SIZE)
					{
						unsigned short nMagic = 0;
						unsigned short nVersion = 0;
						bool bSuccess = false;
#line 88 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (pReceiveBlob->UnpackUint16(nMagic) && pReceiveBlob->UnpackUint16(nVersion) && pReceiveBlob->UnpackBool(bSuccess))
						{
#line 90 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (nMagic == gsClient::MAGIC_WORD && bSuccess)
							{
#line 92 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								if (!pReceiveBlob->UnpackUint32(__nClientId))
#line 93 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
									Assert::Plz(false);
#line 94 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								__eState = State::CONNECTED;
								if (pReceiveBlob) delete pReceiveBlob;
#line 95 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								break;
							}
						}
					}
#line 101 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					Console::Log("bad handshake?");
#line 102 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					Assert::Plz(false);
				}
				if (pReceiveBlob) delete pReceiveBlob;
#line 104 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				break;
			}

			case State::CONNECTED:
			{
				gsBlob* pReceiveBlob = __pClientSocket->Receive();
#line 109 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (pReceiveBlob != 0)
				{
					bool bSyncResponse = false;
					unsigned int nSyncId = 0;
#line 114 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					if (!pReceiveBlob->UnpackBool(bSyncResponse) || !pReceiveBlob->UnpackUint32(nSyncId))
					{
#line 116 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						Console::Log("bad blob?");
#line 117 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						Assert::Plz(false);
					}
#line 120 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					if (bSyncResponse)
					{
						gsSyncInner* pSyncInner = GetSyncInnerBySyncId(nSyncId);
#line 123 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						Assert::Plz(pSyncInner != 0);
						unsigned char nResult = 0;
#line 126 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (!pReceiveBlob->UnpackUint8(nResult))
#line 127 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							Assert::Plz(false);
						unsigned char nResponseRaw = 0;
#line 130 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (!pReceiveBlob->UnpackUint8(nResponseRaw))
#line 131 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							Assert::Plz(false);
						gsSync::Response eResponse = (gsSync::Response)(nResponseRaw);
#line 134 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (nResult == gsSync::RESULT_SUCCESS && eResponse != pSyncInner->__eResponse)
						{
#line 136 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							ErrorDisconnect("Response expectation mismatch");
							if (pReceiveBlob) delete pReceiveBlob;
#line 137 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							return;
						}
						bool bHasBlob = false;
#line 141 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (!pReceiveBlob->UnpackBool(bHasBlob))
#line 142 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							Assert::Plz(false);
						gsBlob* pSyncBlob = 0;
#line 145 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (bHasBlob)
						{
#line 147 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							pSyncBlob = new gsBlob();
#line 148 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (!pReceiveBlob->UnpackBlob(pSyncBlob))
#line 149 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								Assert::Plz(false);
						}
#line 152 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (eResponse != gsSync::Response::EXPECT_ROOM_CHANGE)
#line 153 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							pSyncInner->__bComplete = true;
#line 155 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						pSyncInner->__nResult = nResult;
#line 156 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (nResult == gsSync::RESULT_SUCCESS && pSyncInner->__pSync != 0)
#line 157 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							pSyncInner->__pSync->OnComplete(nResult, pSyncBlob);
						if (pSyncBlob) delete pSyncBlob;
					}
					else
					{
						unsigned int nRoomId = 0;
						unsigned int nMessageType = 0;
#line 164 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (!pReceiveBlob->UnpackUint32(nRoomId) || !pReceiveBlob->UnpackUint32(nMessageType))
#line 165 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							Assert::Plz(false);
						gsBlob* pMessageBlob = new gsBlob();
#line 168 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (!pReceiveBlob->UnpackBlob(pMessageBlob))
#line 169 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							Assert::Plz(false);
#line 171 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (nRoomId == 0)
						{
							gsClient_SyncHandler* pHandler = __GetSyncHandler(nMessageType);
#line 174 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (pHandler == 0)
							{
#line 176 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								ErrorDisconnect("No handler registered for sync message");
								if (pMessageBlob) delete pMessageBlob;
								if (pReceiveBlob) delete pReceiveBlob;
#line 177 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								return;
							}
#line 179 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							pHandler->__pHandler(this, nSyncId, pMessageBlob);
						}
						else
						{
							gsClientRoom* pRoom = GetRoomByRoomId(nRoomId);
#line 184 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (pRoom == 0)
							{
#line 186 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								ErrorDisconnect("Bad room id");
								if (pMessageBlob) delete pMessageBlob;
								if (pReceiveBlob) delete pReceiveBlob;
#line 187 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								return;
							}
							gsClientRoom_SyncHandler* pHandler = pRoom->__GetSyncHandler(nMessageType);
#line 190 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (pHandler == 0)
							{
#line 192 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								ErrorDisconnect("No handler registered for room sync message");
								if (pMessageBlob) delete pMessageBlob;
								if (pReceiveBlob) delete pReceiveBlob;
#line 193 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								return;
							}
#line 195 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							pHandler->__pHandler(this, pRoom, nSyncId, pMessageBlob);
						}
						if (pMessageBlob) delete pMessageBlob;
					}
				}
				int i = 0;
#line 201 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				while (i < __pSyncInnerVector->GetSize())
				{
					gsSyncInner* pSyncInner = __pSyncInnerVector->Get(i);
#line 204 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					if (pSyncInner->__eResponse == gsSync::Response::EXPECT_ROOM_CHANGE && !pSyncInner->__bComplete)
					{
						int j = 0;
#line 207 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						for (j = 0; j < __pRoomVector->GetSize(); j++)
						{
							gsClientRoom* pRoom = __pRoomVector->Get(j);
#line 210 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (pRoom->__nRoomId == pSyncInner->__nRoomId)
#line 211 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								break;
						}
#line 214 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (j == __pRoomVector->GetSize())
						{
#line 216 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							pSyncInner->__eResponse = gsSync::Response::NO_RESPONSE;
#line 217 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							pSyncInner->__bComplete = true;
						}
					}
#line 221 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					if (pSyncInner->__bComplete && pSyncInner->__pSync == 0)
					{
#line 223 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						__pSyncInnerVector->Erase(i);
#line 224 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						continue;
					}
#line 226 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					i++;
				}
				if (pReceiveBlob) delete pReceiveBlob;
#line 230 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				break;
			}

			case State::DISCONNECTED:
			{
#line 234 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				break;
			}

			case State::ERRORED:
			{
#line 238 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				break;
			}

			default:
			{
#line 242 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				Assert::Plz(false);
#line 243 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				break;
			}

		}
	}

#line 248 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	void gsClient::__OnRoomJoin(gsClient* pClient, unsigned int nSyncId, gsBlob* pMessageBlob)
	{
		unsigned int nRoomId = 0;
		unsigned int nRoomType = 0;
		bool bPrimary = false;
#line 253 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		if (pMessageBlob->UnpackUint32(nRoomId) && pMessageBlob->UnpackUint32(nRoomType) && pMessageBlob->UnpackBool(bPrimary))
		{
			gsBlob* pJoinBlob = new gsBlob();
#line 256 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (pMessageBlob->UnpackBlob(pJoinBlob))
			{
				gsClientRoom* pRoom = pClient->OnRoomJoin(nRoomId, nRoomType, bPrimary, pJoinBlob);
#line 259 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (pRoom != 0)
				{
					NumbatLogic::gsClientRoom* __3933567650 = pRoom;
#line 261 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					pRoom = 0;
#line 261 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					pClient->__pRoomVector->PushBack(__3933567650);
					if (pRoom) delete pRoom;
					if (pJoinBlob) delete pJoinBlob;
#line 262 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					return;
				}
				if (pRoom) delete pRoom;
			}
			if (pJoinBlob) delete pJoinBlob;
		}
#line 266 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		pClient->ErrorDisconnect("Room join failed");
	}

#line 269 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	void gsClient::__OnRoomLeave(gsClient* pClient, unsigned int nSyncId, gsBlob* pMessageBlob)
	{
		unsigned int nLeaveRoomId = 0;
		unsigned int nLeaveRoomType = 0;
#line 273 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		if (pMessageBlob->UnpackUint32(nLeaveRoomId) && pMessageBlob->UnpackUint32(nLeaveRoomType))
		{
#line 275 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			for (int i = 0; i < pClient->__pRoomVector->GetSize(); i++)
			{
#line 277 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (pClient->__pRoomVector->Get(i)->__nRoomId == nLeaveRoomId)
				{
#line 279 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					pClient->__pRoomVector->Erase(i);
#line 280 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					return;
				}
			}
		}
#line 284 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		pClient->ErrorDisconnect("Room leave failed");
	}

#line 287 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	void gsClient::RegisterHandler(unsigned int nMessageType, gsClient_SyncHandler::SyncHandler* pHandler)
	{
#line 289 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		if (__GetSyncHandler(nMessageType) != 0)
		{
#line 291 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			Console::Log("Sync handler hash already registered!");
#line 292 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			Assert::Plz(false);
		}
#line 294 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__pSyncHandlerVector->PushBack(new gsClient_SyncHandler(nMessageType, pHandler));
	}

#line 297 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	gsClient_SyncHandler* gsClient::__GetSyncHandler(unsigned int nMessageType)
	{
#line 299 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		for (int i = 0; i < __pSyncHandlerVector->GetSize(); i++)
		{
			gsClient_SyncHandler* pInfo = __pSyncHandlerVector->Get(i);
#line 302 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (pInfo->__nHash == nMessageType)
#line 303 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				return pInfo;
		}
#line 305 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		return 0;
	}

#line 308 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	void gsClient::SyncSend(gsSync* pSync, const char* sxSyncType, gsBlob* pBlob, gsSync::Response eResponse, gsClientRoom* pRoom)
	{
#line 310 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		if (eResponse == gsSync::Response::EXPECT_ROOM_CHANGE)
#line 311 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			Assert::Plz(!HasRoomChangeSyncInFlight(pRoom));
		gsSyncInner* pSyncInner = new gsSyncInner(pSync, ++__nLastSyncId, sxSyncType, pRoom, this);
#line 314 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		pSyncInner->__eResponse = eResponse;
		gsBlob* pSendBlob = new gsBlob();
#line 317 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		pSendBlob->PackUint32(pSyncInner->__nSyncId);
#line 318 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		pSendBlob->PackUint32(0);
#line 319 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		if (pRoom != 0)
#line 320 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			pSendBlob->PackUint32(pRoom->__nRoomId);
		else
#line 322 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			pSendBlob->PackUint32(0);
#line 323 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		pSendBlob->PackUint32(pSyncInner->__nSyncType);
#line 324 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		pSendBlob->PackBlob(pBlob);
#line 326 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__pClientSocket->Send(pSendBlob);
#line 328 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		pSyncInner->__pSync->__pSyncInner = pSyncInner;
#line 330 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		if (pSyncInner->__eResponse == gsSync::Response::NO_RESPONSE)
#line 331 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			pSyncInner->__bComplete = true;
		NumbatLogic::gsSyncInner* __3139231656 = pSyncInner;
#line 333 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		pSyncInner = 0;
#line 333 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__pSyncInnerVector->PushBack(__3139231656);
		if (pSyncInner) delete pSyncInner;
		if (pSendBlob) delete pSendBlob;
	}

#line 336 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	bool gsClient::GetPending()
	{
#line 338 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		if (__eState == State::ERRORED)
#line 339 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			return false;
#line 341 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		if (__pClientSocket->Pending())
#line 342 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			return true;
#line 344 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		if (!__pClientSocket->GetConnected())
#line 345 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			return false;
#line 347 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		for (int i = 0; i < __pSyncInnerVector->GetSize(); i++)
		{
			gsSyncInner* pSyncInner = __pSyncInnerVector->Get(i);
#line 350 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (!pSyncInner->__bComplete)
#line 351 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				return true;
		}
#line 354 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		return false;
	}

#line 357 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	bool gsClient::HasActiveSync()
	{
#line 359 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		for (int i = 0; i < __pSyncInnerVector->GetSize(); i++)
		{
			gsSyncInner* pSyncInner = __pSyncInnerVector->Get(i);
#line 362 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (!pSyncInner->__bComplete)
#line 363 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				return true;
		}
#line 365 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		return false;
	}

#line 368 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	bool gsClient::HasActiveSyncByRoom(gsClientRoom* pRoom)
	{
#line 370 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		for (int i = 0; i < __pSyncInnerVector->GetSize(); i++)
		{
			gsSyncInner* pSyncInner = __pSyncInnerVector->Get(i);
#line 373 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (pSyncInner->__nRoomId == pRoom->__nRoomId && !pSyncInner->__bComplete)
#line 374 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				return true;
		}
#line 376 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		return false;
	}

#line 379 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	bool gsClient::HasRoomChangeSyncInFlight(gsClientRoom* pRoom)
	{
		unsigned int nRoomId = pRoom != 0 ? pRoom->__nRoomId : 0;
#line 382 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		for (int i = 0; i < __pSyncInnerVector->GetSize(); i++)
		{
			gsSyncInner* pSyncInner = __pSyncInnerVector->Get(i);
#line 385 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (pSyncInner->__eResponse == gsSync::Response::EXPECT_ROOM_CHANGE && !pSyncInner->__bComplete && pSyncInner->__nRoomId == nRoomId)
#line 386 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				return true;
		}
#line 388 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		return false;
	}

#line 391 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	gsClientRoom* gsClient::OnRoomJoin(unsigned int nRoomId, unsigned int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob)
	{
#line 393 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		return new gsClientRoom(nRoomId, 0, nRoomTypeHash, bPrimary, this);
	}

#line 417 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	unsigned int gsClient::__ROOM_JOIN_HASH = 1895086341;
#line 418 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	unsigned int gsClient::__ROOM_LEAVE_HASH = 938124572;
#line 422 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	gsClientRoom* gsClient::GetRoomByRoomId(unsigned int nRoomId)
	{
#line 424 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		for (int i = 0; i < __pRoomVector->GetSize(); i++)
		{
			gsClientRoom* pRoom = __pRoomVector->Get(i);
#line 427 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (pRoom->__nRoomId == nRoomId)
#line 428 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				return pRoom;
		}
#line 430 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		return 0;
	}

#line 433 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	void gsClient::ErrorDisconnect(const char* sxErrorMessage)
	{
#line 435 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		Console::Log("Error disconnect");
#line 436 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		Console::Log(sxErrorMessage);
#line 437 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__sErrorMessage = new InternalString(sxErrorMessage);
#line 438 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__eState = State::ERRORED;
#line 439 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__pClientSocket->Disconnect();
	}

#line 442 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	const char* gsClient::GetErrorMessage()
	{
#line 444 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		Assert::Plz(__eState == State::ERRORED);
#line 445 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		return __sErrorMessage->GetExternalString();
	}

#line 448 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	gsSyncInner* gsClient::GetSyncInnerBySyncId(unsigned int nSyncId)
	{
#line 450 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		for (int i = 0; i < __pSyncInnerVector->GetSize(); i++)
		{
			gsSyncInner* pSyncInner = __pSyncInnerVector->Get(i);
#line 453 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (nSyncId == pSyncInner->__nSyncId)
#line 454 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				return pSyncInner;
		}
#line 456 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		return 0;
	}

}

