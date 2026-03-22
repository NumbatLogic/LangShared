#line 1 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
namespace NumbatLogic
{
	class ServerSocket_AcceptSendRecieve
	{
		public static void Run()
		{
			gsServerSocket pServerSocket = new gsServerSocket();
			pServerSocket.Start(9876);
#line 10 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			gsClientSocket pClientSocket = new gsClientSocket();
			pClientSocket.Connect("localhost", 9876);
#line 13 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			GameStrutTestUtil.Update(pServerSocket, pClientSocket);
#line 15 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			gsClientSocket pServerClientSocket = pServerSocket.Accept();
			Assert.Plz(pServerClientSocket != null);
#line 18 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			Assert.Plz(pServerClientSocket.GetConnected());
			Assert.Plz(pClientSocket.GetConnected());
			{
#line 22 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
				gsBlob pSendBlob = new gsBlob();
				pSendBlob.PackInt32(619);
				Assert.Plz(pServerSocket.Broadcast(pSendBlob));
			}
#line 27 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			GameStrutTestUtil.Update(pServerSocket, pClientSocket);
			{
#line 30 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
				gsBlob pReceiveBlob = pClientSocket.Receive();
				Assert.Plz(pReceiveBlob != null);
				int nRecievedInt = 0;
				Assert.Plz(pReceiveBlob.UnpackInt32(ref nRecievedInt));
				Assert.Plz(nRecievedInt == 619);
			}
			{
#line 38 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
				gsBlob pClientResponseBlob = new gsBlob();
				pClientResponseBlob.PackInt32(420);
				Assert.Plz(pClientSocket.Send(pClientResponseBlob));
			}
#line 43 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			GameStrutTestUtil.Update(pServerSocket, pClientSocket);
			{
#line 46 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
				gsBlob pServerReceiveBlob = pServerClientSocket.Receive();
				Assert.Plz(pServerReceiveBlob != null);
				int nServerReceivedInt = 0;
				Assert.Plz(pServerReceiveBlob.UnpackInt32(ref nServerReceivedInt));
				Assert.Plz(nServerReceivedInt == 420);
			}
#line 53 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			pClientSocket.Disconnect();
			pServerSocket.Stop();
		}

	}
}

