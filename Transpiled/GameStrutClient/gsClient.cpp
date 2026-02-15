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
		__sErrorMessage = 0;
		__pRoomVector = new OwnedVector<gsClientRoom*>();
		__pClientSocket = new gsClientSocket();
		__pClientSocket->Connect(sxAddress, nPort);
		__nVersion = nVersion;
		__eState = State::CONNECT;
		__sErrorMessage = 0;
		__pSyncInnerVector = new OwnedVector<gsSyncInner*>();
	}

	gsClient::~gsClient()
	{
		__pClientSocket->Disconnect();
		if (__pRoomVector) delete __pRoomVector;
		if (__pClientSocket) delete __pClientSocket;
		if (__pSyncInnerVector) delete __pSyncInnerVector;
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
							if (nMessageType == __ROOM_JOIN_HASH)
							{
								unsigned int nRoomType = 0;
								bool bPrimary = false;
								if (!pMessageBlob->UnpackUint32(nRoomId) || !pMessageBlob->UnpackUint32(nRoomType) || !pMessageBlob->UnpackBool(bPrimary))
									Assert::Plz(false);
								gsBlob* pJoinBlob = new gsBlob();
								if (!pMessageBlob->UnpackBlob(pJoinBlob))
									Assert::Plz(false);
								gsClientRoom* pRoom = OnRoomJoin(nRoomId, nRoomType, bPrimary, pJoinBlob);
								Assert::Plz(pRoom != 0);
								NumbatLogic::gsClientRoom* __3925306145 = pRoom;
								pRoom = 0;
								__pRoomVector->PushBack(__3925306145);
								if (pJoinBlob) delete pJoinBlob;
								if (pRoom) delete pRoom;
							}
							else
								if (nMessageType == __ROOM_LEAVE_HASH)
								{
									unsigned int nLeaveRoomId = 0;
									unsigned int nLeaveRoomType = 0;
									if (!pMessageBlob->UnpackUint32(nLeaveRoomId) || !pMessageBlob->UnpackUint32(nLeaveRoomType))
										Assert::Plz(false);
									bool bRemoved = false;
									for (int i = 0; i < __pRoomVector->GetSize(); i++)
									{
										gsClientRoom* pRoom = __pRoomVector->Get(i);
										if (pRoom->__nRoomId == nLeaveRoomId)
										{
											__pRoomVector->Erase(i);
											bRemoved = true;
											break;
										}
									}
									Assert::Plz(bRemoved);
								}
								else
								{
									OnSync(nSyncId, nMessageType, pMessageBlob);
								}
						}
						else
						{
							gsClientRoom* pRoom = GetRoomByRoomId(nRoomId);
							if (pRoom == 0)
							{
								ErrorDisconnect("Bad room");
								if (pMessageBlob) delete pMessageBlob;
								if (pReceiveBlob) delete pReceiveBlob;
								return;
							}
							pRoom->OnSync(nSyncId, nMessageType, pMessageBlob);
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

	void gsClient::OnSync(unsigned int nSyncId, unsigned int nMessageType, gsBlob* pMessageBlob)
	{
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
		NumbatLogic::gsSyncInner* __3131232547 = pSyncInner;
		pSyncInner = 0;
		__pSyncInnerVector->PushBack(__3131232547);
		if (pSyncInner) delete pSyncInner;
		if (pSendBlob) delete pSendBlob;
	}

	bool gsClient::GetPending()
	{
		if (__pClientSocket->Pending())
			return true;
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

