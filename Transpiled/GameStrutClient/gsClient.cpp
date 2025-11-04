#include "gsClient.hpp"
#include "gsClientRoom.hpp"
#include "../Vector/OwnedVector.hpp"
#include "../../GameStrutClient/CPP/gsClientSocket.hpp"
#include "gsSync.hpp"
#include "../../ExternalString/CPP/ExternalString.hpp"
#include "../../Blob/CPP/Blob.hpp"
#include "../../InternalString/CPP/InternalString.hpp"
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
	class ExternalString;
	class gsBlob;
	class InternalString;
	class Assert;
	class Console;
	class gsSync;
}
namespace NumbatLogic
{
	gsClient::gsClient(const char* sxAddress, unsigned short nPort, unsigned short nVersion)
	{
		__pRoomVector = 0;
		__pClientSocket = 0;
		__nVersion = 0;
		__nClientId = 0;
		__nLastSyncId = 0;
		__pSyncInnerVector = 0;
		__eState = State::CONNECT;
		__ROOM_JOIN_HASH = 0;
		__pRoomVector = new OwnedVector<gsClientRoom*>();
		__pClientSocket = new gsClientSocket();
		__pClientSocket->Connect(sxAddress, nPort);
		__nVersion = nVersion;
		__eState = CONNECT;
		__pSyncInnerVector = new OwnedVector<gsSyncInner*>();
		__ROOM_JOIN_HASH = ExternalString::GetChecksum("__RoomJoin");
	}

	gsClient::~gsClient()
	{
		__pClientSocket->Disconnect();
		if (__pRoomVector) delete __pRoomVector;
		if (__pClientSocket) delete __pClientSocket;
		if (__pSyncInnerVector) delete __pSyncInnerVector;
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
						unsigned short nMagic;
						unsigned short nVersion;
						bool bSuccess;
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
					bool bSyncResponse;
					unsigned int nSyncId;
					if (!pReceiveBlob->UnpackBool(bSyncResponse) || !pReceiveBlob->UnpackUint32(nSyncId))
					{
						Console::Log("bad blob?");
						Assert::Plz(false);
					}
					if (bSyncResponse)
					{
						gsSyncInner* pSyncInner = GetSyncInnerBySyncId(nSyncId);
						Assert::Plz(pSyncInner != 0);
						gsBlob* pSyncBlob = new gsBlob();
						if (!pReceiveBlob->UnpackBlob(pSyncBlob))
							Assert::Plz(false);
						pSyncInner->OnComplete(pSyncBlob);
						if (pSyncBlob) delete pSyncBlob;
					}
					else
					{
						unsigned int nRoomId;
						int nMessageType;
						if (!pReceiveBlob->UnpackUint32(nRoomId) || !pReceiveBlob->UnpackInt32(nMessageType))
							Assert::Plz(false);
						gsBlob* pMessageBlob = new gsBlob();
						if (!pReceiveBlob->UnpackBlob(pMessageBlob))
							Assert::Plz(false);
						if (nRoomId == 0)
						{
							if (nMessageType == __ROOM_JOIN_HASH)
							{
								int nRoomType;
								bool bPrimary;
								if (!pMessageBlob->UnpackUint32(nRoomId) || !pMessageBlob->UnpackInt32(nRoomType) || !pMessageBlob->UnpackBool(bPrimary))
									Assert::Plz(false);
								gsBlob* pJoinBlob = new gsBlob();
								if (!pMessageBlob->UnpackBlob(pJoinBlob))
									Assert::Plz(false);
								gsClientRoom* pRoom = OnRoomJoin(nRoomId, nRoomType, bPrimary, pJoinBlob);
								Assert::Plz(pRoom != 0);
								NumbatLogic::gsClientRoom* __3132352023 = pRoom;
								pRoom = 0;
								__pRoomVector->PushBack(__3132352023);
								if (pJoinBlob) delete pJoinBlob;
								if (pRoom) delete pRoom;
							}
							else
							{
								Console::Log("unknown hash");
								Assert::Plz(false);
							}
						}
						if (pMessageBlob) delete pMessageBlob;
					}
				}
				int i = 0;
				while (i < __pSyncInnerVector->GetSize())
				{
					gsSyncInner* pSyncInner = __pSyncInnerVector->Get(i);
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

			default:
			{
				Assert::Plz(false);
			}

		}
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
		pSendBlob->PackInt32(pSyncInner->__nSyncType);
		pSendBlob->PackBlob(pBlob);
		__pClientSocket->Send(pSendBlob);
		pSyncInner->__pSync->__pSyncInner = pSyncInner;
		NumbatLogic::gsSyncInner* __2420450420 = pSyncInner;
		pSyncInner = 0;
		__pSyncInnerVector->PushBack(__2420450420);
		if (pSyncInner) delete pSyncInner;
		if (pSendBlob) delete pSendBlob;
	}

	bool gsClient::GetPending()
	{
		return __pClientSocket->Pending();
	}

	gsClientRoom* gsClient::OnRoomJoin(unsigned int nRoomId, int nRoomType, bool bPrimary, gsBlob* pJoinBlob)
	{
		return new gsClientRoom(nRoomId, 0, nRoomType, bPrimary, this);
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

