#include "ServerSocket_AcceptSendRecieve.hpp"
#include "../../../Source/GameStrutClient/CPP/gsServerSocket.hpp"
#include "../../../Source/GameStrutClient/CPP/gsClientSocket.hpp"
#include "../GameStrutTestUtil.hpp"
#include "../../../Source/Assert/CPP/Assert.hpp"
#include "../../../Source/Blob/CPP/Blob.hpp"

namespace NumbatLogic
{
	class ServerSocket_AcceptSendRecieve;
	class gsServerSocket;
	class gsClientSocket;
	class GameStrutTestUtil;
	class Assert;
	class gsBlob;
}
#line 0 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
#line 5 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
	void ServerSocket_AcceptSendRecieve::Run()
	{
		gsServerSocket* pServerSocket = new gsServerSocket();
		pServerSocket->Start(9876);
#line 10 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		gsClientSocket* pClientSocket = new gsClientSocket();
		pClientSocket->Connect("localhost", 9876);
#line 13 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		GameStrutTestUtil::Update(pServerSocket, pClientSocket);
#line 15 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		gsClientSocket* pServerClientSocket = pServerSocket->Accept();
		Assert::Plz(pServerClientSocket != 0);
#line 18 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		Assert::Plz(pServerClientSocket->GetConnected());
		Assert::Plz(pClientSocket->GetConnected());
		{
#line 22 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			gsBlob* pSendBlob = new gsBlob();
			pSendBlob->PackInt32(619);
			Assert::Plz(pServerSocket->Broadcast(pSendBlob));
			if (pSendBlob) delete pSendBlob;
		}
		GameStrutTestUtil::Update(pServerSocket, pClientSocket);
		{
#line 30 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			gsBlob* pReceiveBlob = pClientSocket->Receive();
			Assert::Plz(pReceiveBlob != 0);
			int nRecievedInt = 0;
			Assert::Plz(pReceiveBlob->UnpackInt32(nRecievedInt));
			Assert::Plz(nRecievedInt == 619);
			if (pReceiveBlob) delete pReceiveBlob;
		}
		{
			gsBlob* pClientResponseBlob = new gsBlob();
			pClientResponseBlob->PackInt32(420);
			Assert::Plz(pClientSocket->Send(pClientResponseBlob));
			if (pClientResponseBlob) delete pClientResponseBlob;
		}
		GameStrutTestUtil::Update(pServerSocket, pClientSocket);
		{
#line 46 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			gsBlob* pServerReceiveBlob = pServerClientSocket->Receive();
			Assert::Plz(pServerReceiveBlob != 0);
			int nServerReceivedInt = 0;
			Assert::Plz(pServerReceiveBlob->UnpackInt32(nServerReceivedInt));
			Assert::Plz(nServerReceivedInt == 420);
			if (pServerReceiveBlob) delete pServerReceiveBlob;
		}
		pClientSocket->Disconnect();
		pServerSocket->Stop();
		if (pServerSocket) delete pServerSocket;
		if (pClientSocket) delete pClientSocket;
	}

}

