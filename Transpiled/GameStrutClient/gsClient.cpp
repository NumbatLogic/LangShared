#include "gsClient.hpp"
#include "gsClientRoom.hpp"
#include "../Vector/OwnedVector.hpp"
#include "../../Source/GameStrutClient/CPP/gsClientSocket.hpp"
#include "gsSync.hpp"
#include "../../Source/InternalString/CPP/InternalString.hpp"
#include "../../Source/Blob/CPP/Blob.hpp"
#include "../../Source/Assert/CPP/Assert.hpp"
#include "../../Source/Console/CPP/Console.hpp"

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
#line 0 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
#line 10 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
	gsClient_SyncHandler::gsClient_SyncHandler(unsigned int nHash, SyncHandler* pHandler)
	{
		__nHash = 0;
		__pHandler = 0;
#line 12 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		__nHash = nHash;
		__pHandler = pHandler;
	}

#line 17 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
#line 27 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
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
#line 29 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		__pRoomVector = new OwnedVector<gsClientRoom*>();
#line 31 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		__pClientSocket = new gsClientSocket();
		__pClientSocket->Connect(sxAddress, nPort);
		__nVersion = nVersion;
		__eState = State::CONNECT;
		__pSyncInnerVector = new OwnedVector<gsSyncInner*>();
		__pSyncHandlerVector = new OwnedVector<gsClient_SyncHandler*>();
#line 38 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		RegisterHandler(__ROOM_JOIN_HASH, __OnRoomJoin);
		RegisterHandler(__ROOM_LEAVE_HASH, __OnRoomLeave);
	}

	gsClient::~gsClient()
	{
		__pClientSocket->Disconnect();
		if (__pRoomVector) delete __pRoomVector;
		if (__pClientSocket) delete __pClientSocket;
		if (__pSyncInnerVector) delete __pSyncInnerVector;
		if (__pSyncHandlerVector) delete __pSyncHandlerVector;
		if (__sErrorMessage) delete __sErrorMessage;
	}

#line 47 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
	void gsClient::Update()
	{
		__pClientSocket->Update();
#line 51 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		switch (__eState)
		{
			case State::CONNECT:
			{
				if (!__pClientSocket->Pending())
				{
					__eState = State::HANDSHAKE;
#line 59 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
					gsBlob* pSendBlob = new gsBlob();
					pSendBlob->PackUint16(MAGIC_WORD);
					pSendBlob->PackUint16(__nVersion);
#line 63 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
					pSendBlob->PackUint8(0);
#line 65 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
					InternalString* sName = new InternalString("cliffya");
					pSendBlob->PackInternalString(sName);
#line 68 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
					InternalString* sPassword = new InternalString("password");
					pSendBlob->PackInternalString(sPassword);
#line 71 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
					__pClientSocket->Send(pSendBlob);
					if (pSendBlob) delete pSendBlob;
					if (sName) delete sName;
					if (sPassword) delete sPassword;
				}
#line 73 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
				break;
			}

			case State::HANDSHAKE:
			{
#line 77 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
				gsBlob* pReceiveBlob = __pClientSocket->Receive();
				if (pReceiveBlob != 0)
				{
#line 81 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
					const int INITIAL_SIZE = 2 + 2 + 1 + 4;
					if (pReceiveBlob->GetSize() == INITIAL_SIZE)
					{
						unsigned short nMagic = 0;
						unsigned short nVersion = 0;
						bool bSuccess = false;
#line 88 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						if (pReceiveBlob->UnpackUint16(nMagic) && pReceiveBlob->UnpackUint16(nVersion) && pReceiveBlob->UnpackBool(bSuccess))
						{
							if (nMagic == gsClient::MAGIC_WORD && bSuccess)
							{
								if (!pReceiveBlob->UnpackUint32(__nClientId))
									Assert::Plz(false);
								__eState = State::CONNECTED;
								if (pReceiveBlob) delete pReceiveBlob;
#line 95 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
								break;
							}
						}
					}
#line 101 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
					Console::Log("bad handshake?");
					Assert::Plz(false);
				}
				if (pReceiveBlob) delete pReceiveBlob;
#line 104 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
				break;
			}

			case State::CONNECTED:
			{
#line 108 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
				gsBlob* pReceiveBlob = __pClientSocket->Receive();
				if (pReceiveBlob != 0)
				{
					bool bSyncResponse = false;
					unsigned int nSyncId = 0;
#line 114 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
					if (!pReceiveBlob->UnpackBool(bSyncResponse) || !pReceiveBlob->UnpackUint32(nSyncId))
					{
						Console::Log("bad blob?");
						Assert::Plz(false);
					}
#line 120 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
					if (bSyncResponse)
					{
						gsSyncInner* pSyncInner = GetSyncInnerBySyncId(nSyncId);
						Assert::Plz(pSyncInner != 0);
#line 125 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						unsigned char nResult = 0;
						if (!pReceiveBlob->UnpackUint8(nResult))
							Assert::Plz(false);
#line 129 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						unsigned char nResponseRaw = 0;
						if (!pReceiveBlob->UnpackUint8(nResponseRaw))
							Assert::Plz(false);
						gsSync::Response eResponse = (gsSync::Response)(nResponseRaw);
#line 134 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						if (nResult == gsSync::RESULT_SUCCESS && eResponse != pSyncInner->__eResponse)
						{
							ErrorDisconnect("Response expectation mismatch");
							if (pReceiveBlob) delete pReceiveBlob;
#line 137 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
							return;
						}
#line 140 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						bool bHasBlob = false;
						if (!pReceiveBlob->UnpackBool(bHasBlob))
							Assert::Plz(false);
#line 144 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						gsBlob* pSyncBlob = 0;
						if (bHasBlob)
						{
							pSyncBlob = new gsBlob();
							if (!pReceiveBlob->UnpackBlob(pSyncBlob))
								Assert::Plz(false);
						}
#line 152 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						if (eResponse != gsSync::Response::EXPECT_ROOM_CHANGE)
							pSyncInner->__bComplete = true;
#line 155 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						pSyncInner->__nResult = nResult;
						if (nResult == gsSync::RESULT_SUCCESS && pSyncInner->__pSync != 0)
							pSyncInner->__pSync->OnComplete(nResult, pSyncBlob);
						if (pSyncBlob) delete pSyncBlob;
					}
					else
					{
#line 161 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						unsigned int nRoomId = 0;
						unsigned int nMessageType = 0;
#line 164 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						if (!pReceiveBlob->UnpackUint32(nRoomId) || !pReceiveBlob->UnpackUint32(nMessageType))
							Assert::Plz(false);
#line 167 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						gsBlob* pMessageBlob = new gsBlob();
						if (!pReceiveBlob->UnpackBlob(pMessageBlob))
							Assert::Plz(false);
#line 171 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						if (nRoomId == 0)
						{
							gsClient_SyncHandler* pHandler = __GetSyncHandler(nMessageType);
							if (pHandler == 0)
							{
								ErrorDisconnect("No handler registered for sync message");
								if (pMessageBlob) delete pMessageBlob;
								if (pReceiveBlob) delete pReceiveBlob;
#line 177 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
								return;
							}
							pHandler->__pHandler(this, nSyncId, pMessageBlob);
						}
						else
						{
							gsClientRoom* pRoom = GetRoomByRoomId(nRoomId);
							if (pRoom == 0)
							{
								ErrorDisconnect("Bad room id");
								if (pMessageBlob) delete pMessageBlob;
								if (pReceiveBlob) delete pReceiveBlob;
#line 187 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
								return;
							}
							gsClientRoom_SyncHandler* pHandler = pRoom->__GetSyncHandler(nMessageType);
							if (pHandler == 0)
							{
								ErrorDisconnect("No handler registered for room sync message");
								if (pMessageBlob) delete pMessageBlob;
								if (pReceiveBlob) delete pReceiveBlob;
#line 193 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
								return;
							}
							pHandler->__pHandler(this, pRoom, nSyncId, pMessageBlob);
						}
						if (pMessageBlob) delete pMessageBlob;
					}
				}
				int i = 0;
				while (i < __pSyncInnerVector->GetSize())
				{
					gsSyncInner* pSyncInner = __pSyncInnerVector->Get(i);
					if (pSyncInner->__eResponse == gsSync::Response::EXPECT_ROOM_CHANGE && !pSyncInner->__bComplete)
					{
						int j = 0;
						for (j = 0; j < __pRoomVector->GetSize(); j++)
						{
							gsClientRoom* pRoom = __pRoomVector->Get(j);
							if (pRoom->__nRoomId == pSyncInner->__nRoomId)
								break;
						}
#line 214 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
						if (j == __pRoomVector->GetSize())
						{
							pSyncInner->__eResponse = gsSync::Response::NO_RESPONSE;
							pSyncInner->__bComplete = true;
						}
					}
#line 221 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
					if (pSyncInner->__bComplete && pSyncInner->__pSync == 0)
					{
						__pSyncInnerVector->Erase(i);
						continue;
					}
					i++;
				}
				if (pReceiveBlob) delete pReceiveBlob;
#line 230 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
				break;
			}

			case State::DISCONNECTED:
			{
#line 234 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
				break;
			}

			case State::ERRORED:
			{
#line 238 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
				break;
			}

			default:
			{
#line 242 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
				Assert::Plz(false);
				break;
			}

		}
	}

#line 248 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
	void gsClient::__OnRoomJoin(gsClient* pClient, unsigned int nSyncId, gsBlob* pMessageBlob)
	{
		unsigned int nRoomId = 0;
		unsigned int nRoomType = 0;
		bool bPrimary = false;
		if (pMessageBlob->UnpackUint32(nRoomId) && pMessageBlob->UnpackUint32(nRoomType) && pMessageBlob->UnpackBool(bPrimary))
		{
			gsBlob* pJoinBlob = new gsBlob();
			if (pMessageBlob->UnpackBlob(pJoinBlob))
			{
				gsClientRoom* pRoom = pClient->OnRoomJoin(nRoomId, nRoomType, bPrimary, pJoinBlob);
				if (pRoom != 0)
				{
					NumbatLogic::gsClientRoom* __3933567650 = pRoom;
#line 261 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
					pRoom = 0;
#line 261 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
					pClient->__pRoomVector->PushBack(__3933567650);
					if (pRoom) delete pRoom;
					if (pJoinBlob) delete pJoinBlob;
#line 262 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
					return;
				}
				if (pRoom) delete pRoom;
			}
			if (pJoinBlob) delete pJoinBlob;
		}
#line 266 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		pClient->ErrorDisconnect("Room join failed");
	}

	void gsClient::__OnRoomLeave(gsClient* pClient, unsigned int nSyncId, gsBlob* pMessageBlob)
	{
		unsigned int nLeaveRoomId = 0;
		unsigned int nLeaveRoomType = 0;
		if (pMessageBlob->UnpackUint32(nLeaveRoomId) && pMessageBlob->UnpackUint32(nLeaveRoomType))
		{
			for (int i = 0; i < pClient->__pRoomVector->GetSize(); i++)
			{
				if (pClient->__pRoomVector->Get(i)->__nRoomId == nLeaveRoomId)
				{
					pClient->__pRoomVector->Erase(i);
					return;
				}
			}
		}
		pClient->ErrorDisconnect("Room leave failed");
	}

	void gsClient::RegisterHandler(unsigned int nMessageType, gsClient_SyncHandler::SyncHandler* pHandler)
	{
		if (__GetSyncHandler(nMessageType) != 0)
		{
			Console::Log("Sync handler hash already registered!");
			Assert::Plz(false);
		}
		__pSyncHandlerVector->PushBack(new gsClient_SyncHandler(nMessageType, pHandler));
	}

	gsClient_SyncHandler* gsClient::__GetSyncHandler(unsigned int nMessageType)
	{
		for (int i = 0; i < __pSyncHandlerVector->GetSize(); i++)
		{
			gsClient_SyncHandler* pInfo = __pSyncHandlerVector->Get(i);
			if (pInfo->__nHash == nMessageType)
				return pInfo;
		}
		return 0;
	}

	void gsClient::SyncSend(gsSync* pSync, const char* sxSyncType, gsBlob* pBlob, gsSync::Response eResponse, gsClientRoom* pRoom)
	{
		if (eResponse == gsSync::Response::EXPECT_ROOM_CHANGE)
			Assert::Plz(!HasRoomChangeSyncInFlight(pRoom));
#line 313 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		gsSyncInner* pSyncInner = new gsSyncInner(pSync, ++__nLastSyncId, sxSyncType, pRoom, this);
		pSyncInner->__eResponse = eResponse;
#line 316 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		gsBlob* pSendBlob = new gsBlob();
		pSendBlob->PackUint32(pSyncInner->__nSyncId);
		pSendBlob->PackUint32(0);
		if (pRoom != 0)
			pSendBlob->PackUint32(pRoom->__nRoomId);
		else
			pSendBlob->PackUint32(0);
		pSendBlob->PackUint32(pSyncInner->__nSyncType);
		pSendBlob->PackBlob(pBlob);
#line 326 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		__pClientSocket->Send(pSendBlob);
#line 328 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		pSyncInner->__pSync->__pSyncInner = pSyncInner;
#line 330 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		if (pSyncInner->__eResponse == gsSync::Response::NO_RESPONSE)
			pSyncInner->__bComplete = true;
		NumbatLogic::gsSyncInner* __3139231656 = pSyncInner;
		pSyncInner = 0;
#line 333 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		__pSyncInnerVector->PushBack(__3139231656);
		if (pSyncInner) delete pSyncInner;
		if (pSendBlob) delete pSendBlob;
	}

#line 336 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
	bool gsClient::GetPending()
	{
		if (__eState == State::ERRORED)
			return false;
#line 341 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		if (__pClientSocket->Pending())
			return true;
#line 344 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		if (!__pClientSocket->GetConnected())
			return false;
#line 347 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		for (int i = 0; i < __pSyncInnerVector->GetSize(); i++)
		{
			gsSyncInner* pSyncInner = __pSyncInnerVector->Get(i);
			if (!pSyncInner->__bComplete)
				return true;
		}
#line 354 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
		return false;
	}

	bool gsClient::HasActiveSync()
	{
		for (int i = 0; i < __pSyncInnerVector->GetSize(); i++)
		{
			gsSyncInner* pSyncInner = __pSyncInnerVector->Get(i);
			if (!pSyncInner->__bComplete)
				return true;
		}
		return false;
	}

	bool gsClient::HasActiveSyncByRoom(gsClientRoom* pRoom)
	{
		for (int i = 0; i < __pSyncInnerVector->GetSize(); i++)
		{
			gsSyncInner* pSyncInner = __pSyncInnerVector->Get(i);
			if (pSyncInner->__nRoomId == pRoom->__nRoomId && !pSyncInner->__bComplete)
				return true;
		}
		return false;
	}

	bool gsClient::HasRoomChangeSyncInFlight(gsClientRoom* pRoom)
	{
		unsigned int nRoomId = pRoom != 0 ? pRoom->__nRoomId : 0;
		for (int i = 0; i < __pSyncInnerVector->GetSize(); i++)
		{
			gsSyncInner* pSyncInner = __pSyncInnerVector->Get(i);
			if (pSyncInner->__eResponse == gsSync::Response::EXPECT_ROOM_CHANGE && !pSyncInner->__bComplete && pSyncInner->__nRoomId == nRoomId)
				return true;
		}
		return false;
	}

	gsClientRoom* gsClient::OnRoomJoin(unsigned int nRoomId, unsigned int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob)
	{
		return new gsClientRoom(nRoomId, 0, nRoomTypeHash, bPrimary, this);
	}

#line 417 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
	unsigned int gsClient::__ROOM_JOIN_HASH = 1895086341;
	unsigned int gsClient::__ROOM_LEAVE_HASH = 938124572;
#line 422 "/home/cliffya/git/LangShared/Source/GameStrutClient/gsClient.nll"
	gsClientRoom* gsClient::GetRoomByRoomId(unsigned int nRoomId)
	{
		for (int i = 0; i < __pRoomVector->GetSize(); i++)
		{
			gsClientRoom* pRoom = __pRoomVector->Get(i);
			if (pRoom->__nRoomId == nRoomId)
				return pRoom;
		}
		return 0;
	}

	void gsClient::ErrorDisconnect(const char* sxErrorMessage)
	{
		Console::Log("Error disconnect");
		Console::Log(sxErrorMessage);
		__sErrorMessage = new InternalString(sxErrorMessage);
		__eState = State::ERRORED;
		__pClientSocket->Disconnect();
	}

	const char* gsClient::GetErrorMessage()
	{
		Assert::Plz(__eState == State::ERRORED);
		return __sErrorMessage->GetExternalString();
	}

	gsSyncInner* gsClient::GetSyncInnerBySyncId(unsigned int nSyncId)
	{
		for (int i = 0; i < __pSyncInnerVector->GetSize(); i++)
		{
			gsSyncInner* pSyncInner = __pSyncInnerVector->Get(i);
			if (nSyncId == pSyncInner->__nSyncId)
				return pSyncInner;
		}
		return 0;
	}

}

