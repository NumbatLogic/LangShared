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
#line 1 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
#line 11 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	gsClient_SyncHandler::gsClient_SyncHandler(unsigned int nHash, SyncHandler* pHandler)
	{
		__nHash = 0;
		__pHandler = 0;
#line 13 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__nHash = nHash;
#line 14 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__pHandler = pHandler;
	}

#line 18 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
#line 28 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
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
#line 30 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__pRoomVector = new OwnedVector<gsClientRoom*>();
#line 32 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__pClientSocket = new gsClientSocket();
#line 33 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__pClientSocket->Connect(sxAddress, nPort);
#line 34 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__nVersion = nVersion;
#line 35 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__eState = State::CONNECT;
#line 36 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__pSyncInnerVector = new OwnedVector<gsSyncInner*>();
#line 37 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__pSyncHandlerVector = new OwnedVector<gsClient_SyncHandler*>();
#line 39 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		RegisterHandler(__ROOM_JOIN_HASH, __OnRoomJoin);
#line 40 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		RegisterHandler(__ROOM_LEAVE_HASH, __OnRoomLeave);
	}

#line 43 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	gsClient::~gsClient()
	{
#line 45 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__pClientSocket->Disconnect();
		if (__pRoomVector) delete __pRoomVector;
		if (__pClientSocket) delete __pClientSocket;
		if (__pSyncInnerVector) delete __pSyncInnerVector;
		if (__pSyncHandlerVector) delete __pSyncHandlerVector;
		if (__sErrorMessage) delete __sErrorMessage;
	}

#line 48 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	void gsClient::Update()
	{
#line 50 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__pClientSocket->Update();
#line 52 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		switch (__eState)
		{
			case State::CONNECT:
			{
#line 56 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (!__pClientSocket->Pending())
				{
#line 58 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					__eState = State::HANDSHAKE;
					gsBlob* pSendBlob = new gsBlob();
#line 61 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					pSendBlob->PackUint16(MAGIC_WORD);
#line 62 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					pSendBlob->PackUint16(__nVersion);
#line 64 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					pSendBlob->PackUint8(0);
					InternalString* sName = new InternalString("cliffya");
#line 67 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					pSendBlob->PackInternalString(sName);
					InternalString* sPassword = new InternalString("password");
#line 70 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					pSendBlob->PackInternalString(sPassword);
#line 72 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					__pClientSocket->Send(pSendBlob);
					if (pSendBlob) delete pSendBlob;
					if (sName) delete sName;
					if (sPassword) delete sPassword;
				}
#line 74 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				break;
			}

			case State::HANDSHAKE:
			{
				gsBlob* pReceiveBlob = __pClientSocket->Receive();
#line 79 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (pReceiveBlob != 0)
				{
					const int INITIAL_SIZE = 2 + 2 + 1 + 4;
#line 83 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					if (pReceiveBlob->GetSize() == INITIAL_SIZE)
					{
						unsigned short nMagic = 0;
						unsigned short nVersion = 0;
						bool bSuccess = false;
#line 89 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (pReceiveBlob->UnpackUint16(nMagic) && pReceiveBlob->UnpackUint16(nVersion) && pReceiveBlob->UnpackBool(bSuccess))
						{
#line 91 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (nMagic == gsClient::MAGIC_WORD && bSuccess)
							{
#line 93 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								if (!pReceiveBlob->UnpackUint32(__nClientId))
#line 94 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
									Assert::Plz(false);
#line 95 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								__eState = State::CONNECTED;
								if (pReceiveBlob) delete pReceiveBlob;
#line 96 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								break;
							}
						}
					}
#line 102 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					Console::Log("bad handshake?");
#line 103 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					Assert::Plz(false);
				}
				if (pReceiveBlob) delete pReceiveBlob;
#line 105 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				break;
			}

			case State::CONNECTED:
			{
				gsBlob* pReceiveBlob = __pClientSocket->Receive();
#line 110 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (pReceiveBlob != 0)
				{
					bool bSyncResponse = false;
					unsigned int nSyncId = 0;
#line 115 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					if (!pReceiveBlob->UnpackBool(bSyncResponse) || !pReceiveBlob->UnpackUint32(nSyncId))
					{
#line 117 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						Console::Log("bad blob?");
#line 118 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						Assert::Plz(false);
					}
#line 121 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					if (bSyncResponse)
					{
						gsSyncInner* pSyncInner = GetSyncInnerBySyncId(nSyncId);
#line 124 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						Assert::Plz(pSyncInner != 0);
						unsigned char nResult = 0;
#line 127 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (!pReceiveBlob->UnpackUint8(nResult))
#line 128 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							Assert::Plz(false);
						unsigned char nResponseRaw = 0;
#line 131 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (!pReceiveBlob->UnpackUint8(nResponseRaw))
#line 132 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							Assert::Plz(false);
						gsSync::Response eResponse = (gsSync::Response)(nResponseRaw);
#line 135 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (nResult == gsSync::RESULT_SUCCESS && eResponse != pSyncInner->__eResponse)
						{
#line 137 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							ErrorDisconnect("Response expectation mismatch");
							if (pReceiveBlob) delete pReceiveBlob;
#line 138 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							return;
						}
						bool bHasBlob = false;
#line 142 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (!pReceiveBlob->UnpackBool(bHasBlob))
#line 143 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							Assert::Plz(false);
						gsBlob* pSyncBlob = 0;
#line 146 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (bHasBlob)
						{
#line 148 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							pSyncBlob = new gsBlob();
#line 149 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (!pReceiveBlob->UnpackBlob(pSyncBlob))
#line 150 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								Assert::Plz(false);
						}
#line 153 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (eResponse != gsSync::Response::EXPECT_ROOM_CHANGE)
#line 154 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							pSyncInner->__bComplete = true;
#line 156 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						pSyncInner->__nResult = nResult;
#line 157 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (nResult == gsSync::RESULT_SUCCESS && pSyncInner->__pSync != 0)
#line 158 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							pSyncInner->__pSync->OnComplete(nResult, pSyncBlob);
						if (pSyncBlob) delete pSyncBlob;
					}
					else
					{
						unsigned int nRoomId = 0;
						unsigned int nMessageType = 0;
#line 165 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (!pReceiveBlob->UnpackUint32(nRoomId) || !pReceiveBlob->UnpackUint32(nMessageType))
#line 166 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							Assert::Plz(false);
						gsBlob* pMessageBlob = new gsBlob();
#line 169 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (!pReceiveBlob->UnpackBlob(pMessageBlob))
#line 170 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							Assert::Plz(false);
#line 172 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (nRoomId == 0)
						{
							gsClient_SyncHandler* pHandler = __GetSyncHandler(nMessageType);
#line 175 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (pHandler == 0)
							{
#line 177 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								ErrorDisconnect("No handler registered for sync message");
								if (pMessageBlob) delete pMessageBlob;
								if (pReceiveBlob) delete pReceiveBlob;
#line 178 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								return;
							}
#line 180 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							pHandler->__pHandler(this, nSyncId, pMessageBlob);
						}
						else
						{
							gsClientRoom* pRoom = GetRoomByRoomId(nRoomId);
#line 185 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (pRoom == 0)
							{
#line 187 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								ErrorDisconnect("Bad room id");
								if (pMessageBlob) delete pMessageBlob;
								if (pReceiveBlob) delete pReceiveBlob;
#line 188 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								return;
							}
							gsClientRoom_SyncHandler* pHandler = pRoom->__GetSyncHandler(nMessageType);
#line 191 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (pHandler == 0)
							{
#line 193 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								ErrorDisconnect("No handler registered for room sync message");
								if (pMessageBlob) delete pMessageBlob;
								if (pReceiveBlob) delete pReceiveBlob;
#line 194 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								return;
							}
#line 196 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							pHandler->__pHandler(this, pRoom, nSyncId, pMessageBlob);
						}
						if (pMessageBlob) delete pMessageBlob;
					}
				}
				int i = 0;
#line 202 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				while (i < __pSyncInnerVector->GetSize())
				{
					gsSyncInner* pSyncInner = __pSyncInnerVector->Get(i);
#line 205 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					if (pSyncInner->__eResponse == gsSync::Response::EXPECT_ROOM_CHANGE && !pSyncInner->__bComplete)
					{
						int j = 0;
#line 208 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						for (j = 0; j < __pRoomVector->GetSize(); j++)
						{
							gsClientRoom* pRoom = __pRoomVector->Get(j);
#line 211 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							if (pRoom->__nRoomId == pSyncInner->__nRoomId)
#line 212 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
								break;
						}
#line 215 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						if (j == __pRoomVector->GetSize())
						{
#line 217 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							pSyncInner->__eResponse = gsSync::Response::NO_RESPONSE;
#line 218 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
							pSyncInner->__bComplete = true;
						}
					}
#line 222 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					if (pSyncInner->__bComplete && pSyncInner->__pSync == 0)
					{
#line 224 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						__pSyncInnerVector->Erase(i);
#line 225 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
						continue;
					}
#line 227 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					i++;
				}
				if (pReceiveBlob) delete pReceiveBlob;
#line 231 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				break;
			}

			case State::DISCONNECTED:
			{
#line 235 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				break;
			}

			case State::ERRORED:
			{
#line 239 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				break;
			}

			default:
			{
#line 243 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				Assert::Plz(false);
#line 244 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				break;
			}

		}
	}

#line 249 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	void gsClient::__OnRoomJoin(gsClient* pClient, unsigned int nSyncId, gsBlob* pMessageBlob)
	{
		unsigned int nRoomId = 0;
		unsigned int nRoomType = 0;
		bool bPrimary = false;
#line 254 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		if (pMessageBlob->UnpackUint32(nRoomId) && pMessageBlob->UnpackUint32(nRoomType) && pMessageBlob->UnpackBool(bPrimary))
		{
			gsBlob* pJoinBlob = new gsBlob();
#line 257 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (pMessageBlob->UnpackBlob(pJoinBlob))
			{
				gsClientRoom* pRoom = pClient->OnRoomJoin(nRoomId, nRoomType, bPrimary, pJoinBlob);
#line 260 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (pRoom != 0)
				{
					NumbatLogic::gsClientRoom* __3933567650 = pRoom;
#line 262 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					pRoom = 0;
#line 262 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					pClient->__pRoomVector->PushBack(__3933567650);
					if (pRoom) delete pRoom;
					if (pJoinBlob) delete pJoinBlob;
#line 263 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					return;
				}
				if (pRoom) delete pRoom;
			}
			if (pJoinBlob) delete pJoinBlob;
		}
#line 267 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		pClient->ErrorDisconnect("Room join failed");
	}

#line 270 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	void gsClient::__OnRoomLeave(gsClient* pClient, unsigned int nSyncId, gsBlob* pMessageBlob)
	{
		unsigned int nLeaveRoomId = 0;
		unsigned int nLeaveRoomType = 0;
#line 274 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		if (pMessageBlob->UnpackUint32(nLeaveRoomId) && pMessageBlob->UnpackUint32(nLeaveRoomType))
		{
#line 276 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			for (int i = 0; i < pClient->__pRoomVector->GetSize(); i++)
			{
#line 278 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				if (pClient->__pRoomVector->Get(i)->__nRoomId == nLeaveRoomId)
				{
#line 280 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					pClient->__pRoomVector->Erase(i);
#line 281 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
					return;
				}
			}
		}
#line 285 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		pClient->ErrorDisconnect("Room leave failed");
	}

#line 288 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	void gsClient::RegisterHandler(unsigned int nMessageType, gsClient_SyncHandler::SyncHandler* pHandler)
	{
#line 290 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		if (__GetSyncHandler(nMessageType) != 0)
		{
#line 292 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			Console::Log("Sync handler hash already registered!");
#line 293 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			Assert::Plz(false);
		}
#line 295 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__pSyncHandlerVector->PushBack(new gsClient_SyncHandler(nMessageType, pHandler));
	}

#line 298 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	gsClient_SyncHandler* gsClient::__GetSyncHandler(unsigned int nMessageType)
	{
#line 300 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		for (int i = 0; i < __pSyncHandlerVector->GetSize(); i++)
		{
			gsClient_SyncHandler* pInfo = __pSyncHandlerVector->Get(i);
#line 303 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (pInfo->__nHash == nMessageType)
#line 304 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				return pInfo;
		}
#line 306 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		return 0;
	}

#line 309 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	void gsClient::SyncSend(gsSync* pSync, const char* sxSyncType, gsBlob* pBlob, gsSync::Response eResponse, gsClientRoom* pRoom)
	{
#line 311 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		if (eResponse == gsSync::Response::EXPECT_ROOM_CHANGE)
#line 312 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			Assert::Plz(!HasRoomChangeSyncInFlight(pRoom));
		gsSyncInner* pSyncInner = new gsSyncInner(pSync, ++__nLastSyncId, sxSyncType, pRoom, this);
#line 315 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		pSyncInner->__eResponse = eResponse;
		gsBlob* pSendBlob = new gsBlob();
#line 318 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		pSendBlob->PackUint32(pSyncInner->__nSyncId);
#line 319 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		pSendBlob->PackUint32(0);
#line 320 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		if (pRoom != 0)
#line 321 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			pSendBlob->PackUint32(pRoom->__nRoomId);
		else
#line 323 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			pSendBlob->PackUint32(0);
#line 324 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		pSendBlob->PackUint32(pSyncInner->__nSyncType);
#line 325 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		pSendBlob->PackBlob(pBlob);
#line 327 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__pClientSocket->Send(pSendBlob);
#line 329 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		pSyncInner->__pSync->__pSyncInner = pSyncInner;
#line 331 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		if (pSyncInner->__eResponse == gsSync::Response::NO_RESPONSE)
#line 332 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			pSyncInner->__bComplete = true;
		NumbatLogic::gsSyncInner* __3139231656 = pSyncInner;
#line 334 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		pSyncInner = 0;
#line 334 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__pSyncInnerVector->PushBack(__3139231656);
		if (pSyncInner) delete pSyncInner;
		if (pSendBlob) delete pSendBlob;
	}

#line 337 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	bool gsClient::GetPending()
	{
#line 339 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		if (__eState == State::ERRORED)
#line 340 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			return false;
#line 342 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		if (__pClientSocket->Pending())
#line 343 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			return true;
#line 345 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		if (!__pClientSocket->GetConnected())
#line 346 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			return false;
#line 348 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		for (int i = 0; i < __pSyncInnerVector->GetSize(); i++)
		{
			gsSyncInner* pSyncInner = __pSyncInnerVector->Get(i);
#line 351 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (!pSyncInner->__bComplete)
#line 352 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				return true;
		}
#line 355 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		return false;
	}

#line 358 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	bool gsClient::HasActiveSync()
	{
#line 360 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		for (int i = 0; i < __pSyncInnerVector->GetSize(); i++)
		{
			gsSyncInner* pSyncInner = __pSyncInnerVector->Get(i);
#line 363 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (!pSyncInner->__bComplete)
#line 364 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				return true;
		}
#line 366 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		return false;
	}

#line 369 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	bool gsClient::HasActiveSyncByRoom(gsClientRoom* pRoom)
	{
#line 371 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		for (int i = 0; i < __pSyncInnerVector->GetSize(); i++)
		{
			gsSyncInner* pSyncInner = __pSyncInnerVector->Get(i);
#line 374 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (pSyncInner->__nRoomId == pRoom->__nRoomId && !pSyncInner->__bComplete)
#line 375 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				return true;
		}
#line 377 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		return false;
	}

#line 380 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	bool gsClient::HasRoomChangeSyncInFlight(gsClientRoom* pRoom)
	{
		unsigned int nRoomId = pRoom != 0 ? pRoom->__nRoomId : 0;
#line 383 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		for (int i = 0; i < __pSyncInnerVector->GetSize(); i++)
		{
			gsSyncInner* pSyncInner = __pSyncInnerVector->Get(i);
#line 386 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (pSyncInner->__eResponse == gsSync::Response::EXPECT_ROOM_CHANGE && !pSyncInner->__bComplete && pSyncInner->__nRoomId == nRoomId)
#line 387 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				return true;
		}
#line 389 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		return false;
	}

#line 392 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	gsClientRoom* gsClient::OnRoomJoin(unsigned int nRoomId, unsigned int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob)
	{
#line 394 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		return new gsClientRoom(nRoomId, 0, nRoomTypeHash, bPrimary, this);
	}

#line 418 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	unsigned int gsClient::__ROOM_JOIN_HASH = 1895086341;
#line 419 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	unsigned int gsClient::__ROOM_LEAVE_HASH = 938124572;
#line 423 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	gsClientRoom* gsClient::GetRoomByRoomId(unsigned int nRoomId)
	{
#line 425 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		for (int i = 0; i < __pRoomVector->GetSize(); i++)
		{
			gsClientRoom* pRoom = __pRoomVector->Get(i);
#line 428 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (pRoom->__nRoomId == nRoomId)
#line 429 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				return pRoom;
		}
#line 431 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		return 0;
	}

#line 434 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	void gsClient::ErrorDisconnect(const char* sxErrorMessage)
	{
#line 436 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		Console::Log("Error disconnect");
#line 437 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		Console::Log(sxErrorMessage);
#line 438 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__sErrorMessage = new InternalString(sxErrorMessage);
#line 439 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__eState = State::ERRORED;
#line 440 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		__pClientSocket->Disconnect();
	}

#line 443 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	const char* gsClient::GetErrorMessage()
	{
#line 445 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		Assert::Plz(__eState == State::ERRORED);
#line 446 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		return __sErrorMessage->GetExternalString();
	}

#line 449 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
	gsSyncInner* gsClient::GetSyncInnerBySyncId(unsigned int nSyncId)
	{
#line 451 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		for (int i = 0; i < __pSyncInnerVector->GetSize(); i++)
		{
			gsSyncInner* pSyncInner = __pSyncInnerVector->Get(i);
#line 454 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
			if (nSyncId == pSyncInner->__nSyncId)
#line 455 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
				return pSyncInner;
		}
#line 457 "../LangShared/Transpiled/GameStrutClient/gsClient.nll"
		return 0;
	}

}

