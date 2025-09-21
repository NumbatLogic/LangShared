#include "gsServerClient.hpp"
#include "../../Blob/CPP/Blob.hpp"
#include "../../ExternalString/CPP/ExternalString.hpp"
#include "gsServerRoom.hpp"
#include "../../GameStrutClient/CPP/gsClientSocket.hpp"
#include "../../Vector/CPP/Vector.hpp"
#include "../GameStrutClient/gsClient.hpp"
#include "gsServer.hpp"
#include "../../InternalString/CPP/InternalString.hpp"
#include "../../Console/CPP/Console.hpp"
#include "../GameStrutClient/gsError.hpp"
#include "../../Assert/CPP/Assert.hpp"

namespace NumbatLogic
{
	class gsServerClient;
	class gsBlob;
	class ExternalString;
	class gsClientSocket;
	template <class T>
	class Vector;
	class gsServerRoom;
	class gsClient;
	class gsServer;
	class InternalString;
	class Console;
	class gsError;
	class Assert;
}
namespace NumbatLogic
{
	void gsServerClient::Send(gsServerRoom* pRoom, const char* sxMessageType, gsBlob* pBlob)
	{
		gsBlob* pSendBlob = new gsBlob();
		unsigned int nSyncId = __nLastSyncId++;
		int nMessageTypeHash = ExternalString::GetChecksum(sxMessageType);
		pSendBlob->PackBool(false);
		pSendBlob->PackUint32(nSyncId);
		pSendBlob->PackUint32(pRoom == 0 ? 0 : pRoom->__nRoomId);
		pSendBlob->PackInt32(nMessageTypeHash);
		pSendBlob->PackBlob(pBlob);
		__pClientSocket->Send(pSendBlob);
		if (pSendBlob) delete pSendBlob;
	}

	void gsServerClient::OnInitialJoin()
	{
	}

	gsServerRoom* gsServerClient::GetRoomByRoomId(unsigned int nRoomId)
	{
		for (int i = 0; i < __pRoomVector->GetSize(); i++)
		{
			gsServerRoom* pRoom = __pRoomVector->Get(i);
			if (pRoom->__nRoomId == nRoomId)
				return pRoom;
		}
		return 0;
	}

	void gsServerClient::SyncRespond(unsigned int nSyncId, gsBlob* pBlob)
	{
		gsBlob* pRespondBlob = new gsBlob();
		pRespondBlob->PackBool(true);
		pRespondBlob->PackUint32(nSyncId);
		pRespondBlob->PackBlob(pBlob);
		__pClientSocket->Send(pRespondBlob);
		if (pRespondBlob) delete pRespondBlob;
	}

	gsServerClient::gsServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer)
	{
		__nClientId = 0;
		__pServer = 0;
		__pClientSocket = 0;
		__eState = gsClient::State::CONNECT;
		__pRoomVector = 0;
		__nLastSyncId = 0;
		__nClientId = nClientId;
		__pServer = pServer;
		__pClientSocket = pClientSocket;
		__eState = gsClient::State::CONNECT;
		__pRoomVector = new Vector<gsServerRoom*>();
	}

	void gsServerClient::__Update()
	{
		__pClientSocket->Update();
		switch (__eState)
		{
			case gsClient::State::CONNECT:
			{
				__eState = gsClient::State::HANDSHAKE;
				break;
			}

			case gsClient::State::HANDSHAKE:
			{
				gsBlob* pReceiveBlob = __pClientSocket->Receive();
				if (pReceiveBlob != 0)
				{
					unsigned short nMagic;
					unsigned short nVersion;
					unsigned char nAuthMode;
					if (pReceiveBlob->UnpackUint16(nMagic) && pReceiveBlob->UnpackUint16(nVersion) && pReceiveBlob->UnpackUint8(nAuthMode))
					{
						if (nMagic == gsClient::MAGIC_WORD && nVersion == __pServer->__nVersion)
						{
							if (nAuthMode == 0)
							{
								InternalString* sName = new InternalString("");
								InternalString* sPassword = new InternalString("");
								if (pReceiveBlob->UnpackInternalString(sName))
								{
									if (pReceiveBlob->UnpackInternalString(sPassword))
									{
										gsBlob* pSendBlob = new gsBlob();
										pSendBlob->PackUint16(gsClient::MAGIC_WORD);
										pSendBlob->PackUint16(__pServer->__nVersion);
										pSendBlob->PackBool(true);
										pSendBlob->PackUint32(__nClientId);
										__pClientSocket->Send(pSendBlob);
										__eState = gsClient::State::CONNECTED;
										OnInitialJoin();
										if (pSendBlob) delete pSendBlob;
										if (sName) delete sName;
										if (sPassword) delete sPassword;
										if (pReceiveBlob) delete pReceiveBlob;
										break;
									}
								}
								if (sName) delete sName;
								if (sPassword) delete sPassword;
							}
						}
					}
					{
						Console::Log("Bad handshake, disconnecting");
						gsBlob* pResponseBlob = new gsBlob();
						pResponseBlob->PackUint8(gsError::Error::BAD_HANDSHAKE);
						__pClientSocket->Disconnect();
						if (pResponseBlob) delete pResponseBlob;
						if (pReceiveBlob) delete pReceiveBlob;
						return;
					}
				}
				else
				{
				}
				if (pReceiveBlob) delete pReceiveBlob;
				break;
			}

			case gsClient::State::CONNECTED:
			{
				gsBlob* pReceiveBlob = __pClientSocket->Receive();
				if (pReceiveBlob != 0)
				{
					unsigned int nSyncId;
					unsigned int nLastSyncId;
					unsigned int nRoomId;
					int nSyncType;
					gsBlob* pSyncBlob = new gsBlob();
					if (pReceiveBlob->UnpackUint32(nSyncId) && pReceiveBlob->UnpackUint32(nLastSyncId) && pReceiveBlob->UnpackUint32(nRoomId) && pReceiveBlob->UnpackInt32(nSyncType) && pReceiveBlob->UnpackBlob(pSyncBlob))
					{
						if (nRoomId > 0)
						{
							gsServerRoom* pRoom = GetRoomByRoomId(nRoomId);
							if (!pRoom)
								Assert::Plz(false);
							pRoom->OnSync(nSyncId, nSyncType, pSyncBlob, this);
						}
						else
						{
						}
					}
					else
					{
						Assert::Plz(false);
					}
					if (pSyncBlob) delete pSyncBlob;
				}
				if (pReceiveBlob) delete pReceiveBlob;
				break;
			}

			case gsClient::State::DISCONNECTED:
			{
				break;
			}

			default:
			{
				Assert::Plz(false);
			}

		}
	}

	gsServerClient::~gsServerClient()
	{
		if (__pRoomVector) delete __pRoomVector;
	}

}

