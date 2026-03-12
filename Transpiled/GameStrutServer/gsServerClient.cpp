#include "gsServerClient.hpp"
#include "../../Blob/CPP/Blob.hpp"
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
	class gsClientSocket;
	template <class T>
	class Vector;
	class gsServerRoom;
	class gsClient;
	class gsServer;
	class InternalString;
	class Console;
	class gsError;
	class gsServerRoom_SyncHandler;
	class Assert;
}
#line 0 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
#line 5 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
	void gsServerClient::Send(gsServerRoom* pRoom, unsigned int nMessageTypeHash, gsBlob* pBlob)
	{
		gsBlob* pSendBlob = new gsBlob();
#line 9 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		unsigned int nSyncId = __nLastSyncId++;
#line 11 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		pSendBlob->PackBool(false);
		pSendBlob->PackUint32(nSyncId);
		pSendBlob->PackUint32(pRoom == 0 ? 0 : pRoom->__nRoomId);
		pSendBlob->PackUint32(nMessageTypeHash);
		pSendBlob->PackBlob(pBlob);
#line 17 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		__pClientSocket->Send(pSendBlob);
		if (pSendBlob) delete pSendBlob;
	}

#line 23 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
	void gsServerClient::OnInitialJoin()
	{
	}

#line 30 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
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

#line 43 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
	void gsServerClient::SyncRespond(unsigned int nSyncId, unsigned char nResult, gsSync::Response eResponse, gsBlob* pBlob)
	{
		gsBlob* pRespondBlob = new gsBlob();
#line 47 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		pRespondBlob->PackBool(true);
		pRespondBlob->PackUint32(nSyncId);
		pRespondBlob->PackUint8(nResult);
		pRespondBlob->PackUint8((unsigned char)(eResponse));
#line 52 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		if (pBlob != 0)
		{
			pRespondBlob->PackBool(true);
			pRespondBlob->PackBlob(pBlob);
		}
		else
		{
			pRespondBlob->PackBool(false);
		}
#line 62 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		__pClientSocket->Send(pRespondBlob);
		if (pRespondBlob) delete pRespondBlob;
	}

#line 95 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
	gsServerClient::gsServerClient(unsigned int nClientId, gsClientSocket* pClientSocket, gsServer* pServer)
	{
		__nClientId = 0;
		__pServer = 0;
		__pClientSocket = 0;
		__eState = gsClient::State::CONNECT;
		__pRoomVector = 0;
		__nLastSyncId = 0;
#line 97 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		__nClientId = nClientId;
		__pServer = pServer;
		__pClientSocket = pClientSocket;
		__eState = gsClient::State::CONNECT;
		__pRoomVector = new Vector<gsServerRoom*>();
	}

	void gsServerClient::__Update()
	{
		__pClientSocket->Update();
#line 108 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		switch (__eState)
		{
			case gsClient::State::CONNECT:
			{
				__eState = gsClient::State::HANDSHAKE;
				break;
			}

			case gsClient::State::HANDSHAKE:
			{
#line 117 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
				gsBlob* pReceiveBlob = __pClientSocket->Receive();
				if (pReceiveBlob != 0)
				{
					unsigned short nMagic = 0;
					unsigned short nVersion = 0;
					unsigned char nAuthMode = 0;
#line 124 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					if (pReceiveBlob->UnpackUint16(nMagic) && pReceiveBlob->UnpackUint16(nVersion) && pReceiveBlob->UnpackUint8(nAuthMode))
					{
						if (nMagic == gsClient::MAGIC_WORD && nVersion == __pServer->__nVersion)
						{
#line 129 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
							if (nAuthMode == 0)
							{
								InternalString* sName = new InternalString("");
								InternalString* sPassword = new InternalString("");
#line 134 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
								if (pReceiveBlob->UnpackInternalString(sName))
								{
									if (pReceiveBlob->UnpackInternalString(sPassword))
									{
#line 140 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
										gsBlob* pSendBlob = new gsBlob();
										pSendBlob->PackUint16(gsClient::MAGIC_WORD);
										pSendBlob->PackUint16(__pServer->__nVersion);
										pSendBlob->PackBool(true);
										pSendBlob->PackUint32(__nClientId);
										__pClientSocket->Send(pSendBlob);
#line 147 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
										__eState = gsClient::State::CONNECTED;
#line 149 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
										OnInitialJoin();
										if (pSendBlob) delete pSendBlob;
										if (sName) delete sName;
										if (sPassword) delete sPassword;
										if (pReceiveBlob) delete pReceiveBlob;
#line 150 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
										break;
									}
								}
								if (sName) delete sName;
								if (sPassword) delete sPassword;
							}
						}
					}
					{
#line 158 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
						Console::Log("Bad handshake, disconnecting");
						gsBlob* pResponseBlob = new gsBlob();
						pResponseBlob->PackUint8((unsigned char)(gsError::Error::BAD_HANDSHAKE));
						__pClientSocket->Disconnect();
						if (pResponseBlob) delete pResponseBlob;
						if (pReceiveBlob) delete pReceiveBlob;
#line 162 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
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
#line 173 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
				gsBlob* pReceiveBlob = __pClientSocket->Receive();
				if (pReceiveBlob != 0)
				{
					unsigned int nSyncId = 0;
					unsigned int nLastSyncId = 0;
					unsigned int nRoomId = 0;
					unsigned int nSyncType = 0;
					gsBlob* pSyncBlob = new gsBlob();
#line 182 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					if (pReceiveBlob->UnpackUint32(nSyncId) && pReceiveBlob->UnpackUint32(nLastSyncId) && pReceiveBlob->UnpackUint32(nRoomId) && pReceiveBlob->UnpackUint32(nSyncType) && pReceiveBlob->UnpackBlob(pSyncBlob))
					{
#line 188 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
						if (nRoomId > 0)
						{
							gsServerRoom* pRoom = GetRoomByRoomId(nRoomId);
#line 192 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
							if (pRoom == 0)
							{
								ErrorDisconnect("Bad room");
								if (pSyncBlob) delete pSyncBlob;
								if (pReceiveBlob) delete pReceiveBlob;
#line 195 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
								return;
							}
							gsServerRoom_SyncHandler* pHandler = pRoom->__GetSyncHandler(nSyncType);
							if (pHandler == 0)
							{
								ErrorDisconnect("No handler for room sync");
								if (pSyncBlob) delete pSyncBlob;
								if (pReceiveBlob) delete pReceiveBlob;
#line 201 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
								return;
							}
							pHandler->__pHandler(pRoom, nSyncId, nSyncType, pSyncBlob, this);
						}
						else
						{
						}
					}
					else
					{
#line 213 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
						Assert::Plz(false);
					}
					if (pSyncBlob) delete pSyncBlob;
				}
				if (pReceiveBlob) delete pReceiveBlob;
#line 216 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
				break;
			}

			case gsClient::State::DISCONNECTED:
			{
#line 220 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
				break;
			}

			default:
			{
#line 224 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
				Assert::Plz(false);
				break;
			}

		}
	}

#line 230 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
	void gsServerClient::ErrorDisconnect(const char* sxErrorMessage)
	{
		Console::Log("Error disconnect");
		Console::Log(sxErrorMessage);
#line 240 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		__pClientSocket->Disconnect();
	}

#line 3 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
	gsServerClient::~gsServerClient()
	{
		if (__pRoomVector) delete __pRoomVector;
	}

}

