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
	class gsClientRoom_SyncHandler;
	class gsSync;
}
namespace NumbatLogic
{
	gsClient_SyncHandler::gsClient_SyncHandler(unsigned int nHash, SyncHandler* pHandler)
	{
		__nHash = 0;
		__pHandler = 0;
		__nHash = nHash;
		__pHandler = pHandler;
	}

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
		__pRoomVector = new OwnedVector<gsClientRoom*>();
		__pClientSocket = new gsClientSocket();
		__pClientSocket->Connect(sxAddress, nPort);
		__nVersion = nVersion;
		__eState = State::CONNECT;
		__pSyncInnerVector = new OwnedVector<gsSyncInner*>();
		__pSyncHandlerVector = new OwnedVector<gsClient_SyncHandler*>();
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

	void gsClient::Update()
	{
		__pClientSocket->Update();
		switch (__eState)
		{
			case State::CONNECT:
			{
				if (!__pClientSocket->Pending())
				{
					__eState = State::HANDSHAKE;
					gsBlob* pSendBlob = new gsBlob();
					pSendBlob->PackUint16(MAGIC_WORD);
					pSendBlob->PackUint16(__nVersion);
					pSendBlob->PackUint8(0);
					InternalString* sName = new InternalString("cliffya");
					pSendBlob->PackInternalString(sName);
					InternalString* sPassword = new InternalString("password");
					pSendBlob->PackInternalString(sPassword);
					__pClientSocket->Send(pSendBlob);
					if (pSendBlob) delete pSendBlob;
					if (sName) delete sName;
					if (sPassword) delete sPassword;
				}
				break;
			}

			case State::HANDSHAKE:
			{
				gsBlob* pReceiveBlob = __pClientSocket->Receive();
				if (pReceiveBlob != 0)
				{
					const int INITIAL_SIZE = 2 + 2 + 1 + 4;
					if (pReceiveBlob->GetSize() == INITIAL_SIZE)
					{
						unsigned short nMagic = 0;
						unsigned short nVersion = 0;
						bool bSuccess = false;
						if (pReceiveBlob->UnpackUint16(nMagic) && pReceiveBlob->UnpackUint16(nVersion) && pReceiveBlob->UnpackBool(bSuccess))
						{
							if (nMagic == gsClient::MAGIC_WORD && bSuccess)
							{
								if (!pReceiveBlob->UnpackUint32(__nClientId))
									Assert::Plz(false);
								__eState = State::CONNECTED;
								if (pReceiveBlob) delete pReceiveBlob;
								break;
							}
						}
					}
					Console::Log("bad handshake?");
					Assert::Plz(false);
				}
				if (pReceiveBlob) delete pReceiveBlob;
				break;
			}

			case State::CONNECTED:
			{
				gsBlob* pReceiveBlob = __pClientSocket->Receive();
				if (pReceiveBlob != 0)
				{
					bool bSyncResponse = false;
					unsigned int nSyncId = 0;
					if (!pReceiveBlob->UnpackBool(bSyncResponse) || !pReceiveBlob->UnpackUint32(nSyncId))
					{
						Console::Log("bad blob?");
						Assert::Plz(false);
					}
					if (bSyncResponse)
					{
						gsSyncInner* pSyncInner = GetSyncInnerBySyncId(nSyncId);
						Assert::Plz(pSyncInner != 0);
						unsigned char nResult = 0;
						if (!pReceiveBlob->UnpackUint8(nResult))
							Assert::Plz(false);
						bool bAwaitRoomChange = false;
						if (!pReceiveBlob->UnpackBool(bAwaitRoomChange))
							Assert::Plz(false);
						bool bHasBlob = false;
						if (!pReceiveBlob->UnpackBool(bHasBlob))
							Assert::Plz(false);
						gsBlob* pSyncBlob = 0;
						if (bHasBlob)
						{
							pSyncBlob = new gsBlob();
							if (!pReceiveBlob->UnpackBlob(pSyncBlob))
								Assert::Plz(false);
						}
						pSyncInner->OnComplete(nResult, bAwaitRoomChange, pSyncBlob);
						if (pSyncBlob) delete pSyncBlob;
					}
					else
					{
						unsigned int nRoomId = 0;
						unsigned int nMessageType = 0;
						if (!pReceiveBlob->UnpackUint32(nRoomId) || !pReceiveBlob->UnpackUint32(nMessageType))
							Assert::Plz(false);
						gsBlob* pMessageBlob = new gsBlob();
						if (!pReceiveBlob->UnpackBlob(pMessageBlob))
							Assert::Plz(false);
						if (nRoomId == 0)
						{
							gsClient_SyncHandler* pHandler = __GetSyncHandler(nMessageType);
							if (pHandler == 0)
							{
								ErrorDisconnect("No handler registered for sync message");
								if (pMessageBlob) delete pMessageBlob;
								if (pReceiveBlob) delete pReceiveBlob;
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
								return;
							}
							gsClientRoom_SyncHandler* pHandler = pRoom->__GetSyncHandler(nMessageType);
							if (pHandler == 0)
							{
								ErrorDisconnect("No handler registered for room sync message");
								if (pMessageBlob) delete pMessageBlob;
								if (pReceiveBlob) delete pReceiveBlob;
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
					if (pSyncInner->__bAwaitRoomChange && !pSyncInner->__bComplete)
					{
						int j = 0;
						for (j = 0; j < __pRoomVector->GetSize(); j++)
						{
							gsClientRoom* pRoom = __pRoomVector->Get(j);
							if (pRoom->__nRoomId == pSyncInner->__nRoomId)
								break;
						}
						if (j == __pRoomVector->GetSize())
						{
							pSyncInner->__bAwaitRoomChange = false;
							pSyncInner->__bComplete = true;
						}
					}
					if (pSyncInner->__bComplete && pSyncInner->__pSync == 0)
					{
						__pSyncInnerVector->Erase(i);
						continue;
					}
					i++;
				}
				if (pReceiveBlob) delete pReceiveBlob;
				break;
			}

			case State::DISCONNECTED:
			{
				break;
			}

			case State::ERRORED:
			{
				break;
			}

			default:
			{
				Assert::Plz(false);
				break;
			}

		}
	}

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
					NumbatLogic::gsClientRoom* __3933436460 = pRoom;
					pRoom = 0;
					pClient->__pRoomVector->PushBack(__3933436460);
					if (pRoom) delete pRoom;
					if (pJoinBlob) delete pJoinBlob;
					return;
				}
				if (pRoom) delete pRoom;
			}
			if (pJoinBlob) delete pJoinBlob;
		}
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

	void gsClient::SyncSend(gsSync* pSync, const char* sxSyncType, gsBlob* pBlob, bool mayChangeRoom, gsClientRoom* pRoom)
	{
		gsSyncInner* pSyncInner = new gsSyncInner(pSync, ++__nLastSyncId, sxSyncType, pRoom, this);
		gsBlob* pSendBlob = new gsBlob();
		pSendBlob->PackUint32(pSyncInner->__nSyncId);
		pSendBlob->PackUint32(0);
		if (pRoom != 0)
			pSendBlob->PackUint32(pRoom->__nRoomId);
		else
			pSendBlob->PackUint32(0);
		pSendBlob->PackUint32(pSyncInner->__nSyncType);
		pSendBlob->PackBlob(pBlob);
		__pClientSocket->Send(pSendBlob);
		pSyncInner->__pSync->__pSyncInner = pSyncInner;
		NumbatLogic::gsSyncInner* __3139100460 = pSyncInner;
		pSyncInner = 0;
		__pSyncInnerVector->PushBack(__3139100460);
		if (pSyncInner) delete pSyncInner;
		if (pSendBlob) delete pSendBlob;
	}

	bool gsClient::GetPending()
	{
		if (__eState == State::ERRORED)
			return false;
		if (__pClientSocket->Pending())
			return true;
		if (!__pClientSocket->GetConnected())
			return false;
		for (int i = 0; i < __pSyncInnerVector->GetSize(); i++)
		{
			gsSyncInner* pSyncInner = __pSyncInnerVector->Get(i);
			if (!pSyncInner->__bComplete)
				return true;
		}
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

	gsClientRoom* gsClient::OnRoomJoin(unsigned int nRoomId, unsigned int nRoomTypeHash, bool bPrimary, gsBlob* pJoinBlob)
	{
		return new gsClientRoom(nRoomId, 0, nRoomTypeHash, bPrimary, this);
	}

	unsigned int gsClient::__ROOM_JOIN_HASH = 1895086341;
	unsigned int gsClient::__ROOM_LEAVE_HASH = 938124572;
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

