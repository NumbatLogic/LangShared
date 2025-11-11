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
namespace NumbatLogic
{
	void ServerSocket_AcceptSendRecieve::Run()
	{
		gsServerSocket* pServerSocket = new gsServerSocket();
		pServerSocket->Start(9876);
		gsClientSocket* pClientSocket = new gsClientSocket();
		pClientSocket->Connect("localhost", 9876);
		GameStrutTestUtil::Update(pServerSocket, pClientSocket);
		gsClientSocket* pServerClientSocket = pServerSocket->Accept();
		Assert::Plz(pServerClientSocket != 0);
		Assert::Plz(pServerClientSocket->GetConnected());
		Assert::Plz(pClientSocket->GetConnected());
		{
			gsBlob* pSendBlob = new gsBlob();
			pSendBlob->PackInt32(619);
			Assert::Plz(pServerSocket->Broadcast(pSendBlob));
			if (pSendBlob) delete pSendBlob;
		}
		GameStrutTestUtil::Update(pServerSocket, pClientSocket);
		{
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

