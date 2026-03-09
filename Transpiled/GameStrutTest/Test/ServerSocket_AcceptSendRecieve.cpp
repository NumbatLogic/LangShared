#include "ServerSocket_AcceptSendRecieve.hpp"
#include "../../../GameStrutClient/CPP/gsServerSocket.hpp"
#include "../../../GameStrutClient/CPP/gsClientSocket.hpp"
#include "../GameStrutTestUtil.hpp"
#include "../../../Assert/CPP/Assert.hpp"
#include "../../../Blob/CPP/Blob.hpp"

namespace NumbatLogic
{
	class ServerSocket_AcceptSendRecieve;
	class gsServerSocket;
	class gsClientSocket;
	class GameStrutTestUtil;
	class Assert;
	class gsBlob;
}
#line 1 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
#line 6 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
	void ServerSocket_AcceptSendRecieve::Run()
	{
		gsServerSocket* pServerSocket = new gsServerSocket();
#line 9 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		pServerSocket->Start(9876);
		gsClientSocket* pClientSocket = new gsClientSocket();
#line 12 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		pClientSocket->Connect("localhost", 9876);
#line 14 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		GameStrutTestUtil::Update(pServerSocket, pClientSocket);
		gsClientSocket* pServerClientSocket = pServerSocket->Accept();
#line 17 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		Assert::Plz(pServerClientSocket != 0);
#line 19 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		Assert::Plz(pServerClientSocket->GetConnected());
#line 20 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		Assert::Plz(pClientSocket->GetConnected());
		{
			gsBlob* pSendBlob = new gsBlob();
#line 24 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			pSendBlob->PackInt32(619);
#line 25 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			Assert::Plz(pServerSocket->Broadcast(pSendBlob));
			if (pSendBlob) delete pSendBlob;
		}
#line 28 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		GameStrutTestUtil::Update(pServerSocket, pClientSocket);
		{
			gsBlob* pReceiveBlob = pClientSocket->Receive();
#line 32 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			Assert::Plz(pReceiveBlob != 0);
			int nRecievedInt = 0;
#line 34 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			Assert::Plz(pReceiveBlob->UnpackInt32(nRecievedInt));
#line 35 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			Assert::Plz(nRecievedInt == 619);
			if (pReceiveBlob) delete pReceiveBlob;
		}
		{
			gsBlob* pClientResponseBlob = new gsBlob();
#line 40 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			pClientResponseBlob->PackInt32(420);
#line 41 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			Assert::Plz(pClientSocket->Send(pClientResponseBlob));
			if (pClientResponseBlob) delete pClientResponseBlob;
		}
#line 44 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		GameStrutTestUtil::Update(pServerSocket, pClientSocket);
		{
			gsBlob* pServerReceiveBlob = pServerClientSocket->Receive();
#line 48 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			Assert::Plz(pServerReceiveBlob != 0);
			int nServerReceivedInt = 0;
#line 50 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			Assert::Plz(pServerReceiveBlob->UnpackInt32(nServerReceivedInt));
#line 51 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			Assert::Plz(nServerReceivedInt == 420);
			if (pServerReceiveBlob) delete pServerReceiveBlob;
		}
#line 54 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		pClientSocket->Disconnect();
#line 55 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		pServerSocket->Stop();
		if (pServerSocket) delete pServerSocket;
		if (pClientSocket) delete pClientSocket;
	}

}

