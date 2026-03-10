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
		unsigned int nSyncId = __nLastSyncId++;
#line 11 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		pSendBlob->PackBool(false);
#line 12 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		pSendBlob->PackUint32(nSyncId);
#line 13 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		pSendBlob->PackUint32(pRoom == 0 ? 0 : pRoom->__nRoomId);
#line 14 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		pSendBlob->PackUint32(nMessageTypeHash);
#line 15 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
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
#line 32 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		for (int i = 0; i < __pRoomVector->GetSize(); i++)
		{
			gsServerRoom* pRoom = __pRoomVector->Get(i);
#line 35 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			if (pRoom->__nRoomId == nRoomId)
#line 36 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
				return pRoom;
		}
#line 38 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		return 0;
	}

#line 43 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
	void gsServerClient::SyncRespond(unsigned int nSyncId, unsigned char nResult, gsSync::Response eResponse, gsBlob* pBlob)
	{
		gsBlob* pRespondBlob = new gsBlob();
#line 47 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		pRespondBlob->PackBool(true);
#line 48 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		pRespondBlob->PackUint32(nSyncId);
#line 49 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		pRespondBlob->PackUint8(nResult);
#line 50 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		pRespondBlob->PackUint8((unsigned char)(eResponse));
#line 52 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		if (pBlob != 0)
		{
#line 54 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			pRespondBlob->PackBool(true);
#line 55 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
			pRespondBlob->PackBlob(pBlob);
		}
		else
		{
#line 59 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
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
#line 98 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		__pServer = pServer;
#line 99 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		__pClientSocket = pClientSocket;
#line 100 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		__eState = gsClient::State::CONNECT;
#line 101 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		__pRoomVector = new Vector<gsServerRoom*>();
	}

#line 104 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
	void gsServerClient::__Update()
	{
#line 106 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		__pClientSocket->Update();
#line 108 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		switch (__eState)
		{
			case gsClient::State::CONNECT:
			{
#line 112 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
				__eState = gsClient::State::HANDSHAKE;
#line 113 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
				break;
			}

			case gsClient::State::HANDSHAKE:
			{
				gsBlob* pReceiveBlob = __pClientSocket->Receive();
#line 118 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
				if (pReceiveBlob != 0)
				{
					unsigned short nMagic = 0;
					unsigned short nVersion = 0;
					unsigned char nAuthMode = 0;
#line 124 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
					if (pReceiveBlob->UnpackUint16(nMagic) && pReceiveBlob->UnpackUint16(nVersion) && pReceiveBlob->UnpackUint8(nAuthMode))
					{
#line 126 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
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
#line 136 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
									if (pReceiveBlob->UnpackInternalString(sPassword))
									{
										gsBlob* pSendBlob = new gsBlob();
#line 141 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
										pSendBlob->PackUint16(gsClient::MAGIC_WORD);
#line 142 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
										pSendBlob->PackUint16(__pServer->__nVersion);
#line 143 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
										pSendBlob->PackBool(true);
#line 144 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
										pSendBlob->PackUint32(__nClientId);
#line 145 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
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
#line 160 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
						pResponseBlob->PackUint8((unsigned char)(gsError::Error::BAD_HANDSHAKE));
#line 161 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
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
#line 169 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
				break;
			}

			case gsClient::State::CONNECTED:
			{
				gsBlob* pReceiveBlob = __pClientSocket->Receive();
#line 174 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
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
#line 194 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
								ErrorDisconnect("Bad room");
								if (pSyncBlob) delete pSyncBlob;
								if (pReceiveBlob) delete pReceiveBlob;
#line 195 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
								return;
							}
							gsServerRoom_SyncHandler* pHandler = pRoom->__GetSyncHandler(nSyncType);
#line 198 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
							if (pHandler == 0)
							{
#line 200 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
								ErrorDisconnect("No handler for room sync");
								if (pSyncBlob) delete pSyncBlob;
								if (pReceiveBlob) delete pReceiveBlob;
#line 201 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
								return;
							}
#line 203 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
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
#line 225 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
				break;
			}

		}
	}

#line 230 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
	void gsServerClient::ErrorDisconnect(const char* sxErrorMessage)
	{
#line 232 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
		Console::Log("Error disconnect");
#line 233 "../LangShared/Transpiled/GameStrutServer/gsServerClient.nll"
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

