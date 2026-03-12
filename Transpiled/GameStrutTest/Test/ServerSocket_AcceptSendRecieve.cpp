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
#line 0 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
#line 5 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
	void ServerSocket_AcceptSendRecieve::Run()
	{
#line 7 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		gsServerSocket* pServerSocket = new gsServerSocket();
#line 8 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		pServerSocket->Start(9876);
#line 10 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		gsClientSocket* pClientSocket = new gsClientSocket();
#line 11 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		pClientSocket->Connect("localhost", 9876);
#line 13 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		GameStrutTestUtil::Update(pServerSocket, pClientSocket);
#line 15 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		gsClientSocket* pServerClientSocket = pServerSocket->Accept();
#line 16 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		Assert::Plz(pServerClientSocket != 0);
#line 18 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		Assert::Plz(pServerClientSocket->GetConnected());
#line 19 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		Assert::Plz(pClientSocket->GetConnected());
		{
#line 22 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			gsBlob* pSendBlob = new gsBlob();
#line 23 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			pSendBlob->PackInt32(619);
#line 24 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			Assert::Plz(pServerSocket->Broadcast(pSendBlob));
			if (pSendBlob) delete pSendBlob;
		}
#line 27 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		GameStrutTestUtil::Update(pServerSocket, pClientSocket);
		{
#line 30 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			gsBlob* pReceiveBlob = pClientSocket->Receive();
#line 31 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			Assert::Plz(pReceiveBlob != 0);
#line 32 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			int nRecievedInt = 0;
#line 33 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			Assert::Plz(pReceiveBlob->UnpackInt32(nRecievedInt));
#line 34 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			Assert::Plz(nRecievedInt == 619);
			if (pReceiveBlob) delete pReceiveBlob;
		}
		{
#line 38 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			gsBlob* pClientResponseBlob = new gsBlob();
#line 39 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			pClientResponseBlob->PackInt32(420);
#line 40 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			Assert::Plz(pClientSocket->Send(pClientResponseBlob));
			if (pClientResponseBlob) delete pClientResponseBlob;
		}
#line 43 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		GameStrutTestUtil::Update(pServerSocket, pClientSocket);
		{
#line 46 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			gsBlob* pServerReceiveBlob = pServerClientSocket->Receive();
#line 47 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			Assert::Plz(pServerReceiveBlob != 0);
#line 48 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			int nServerReceivedInt = 0;
#line 49 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			Assert::Plz(pServerReceiveBlob->UnpackInt32(nServerReceivedInt));
#line 50 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			Assert::Plz(nServerReceivedInt == 420);
			if (pServerReceiveBlob) delete pServerReceiveBlob;
		}
#line 53 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		pClientSocket->Disconnect();
#line 54 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		pServerSocket->Stop();
		if (pServerSocket) delete pServerSocket;
		if (pClientSocket) delete pClientSocket;
	}

}

