#line 1 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
	class ServerSocket_AcceptSendRecieve
	{
#line 6 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
		public static void Run()
		{
			gsServerSocket pServerSocket = new gsServerSocket();
#line 9 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			pServerSocket.Start(9876);
			gsClientSocket pClientSocket = new gsClientSocket();
#line 12 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			pClientSocket.Connect("localhost", 9876);
#line 14 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			GameStrutTestUtil.Update(pServerSocket, pClientSocket);
			gsClientSocket pServerClientSocket = pServerSocket.Accept();
#line 17 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			Assert.Plz(pServerClientSocket != null);
#line 19 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			Assert.Plz(pServerClientSocket.GetConnected());
#line 20 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			Assert.Plz(pClientSocket.GetConnected());
			{
				gsBlob pSendBlob = new gsBlob();
#line 24 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
				pSendBlob.PackInt32(619);
#line 25 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
				Assert.Plz(pServerSocket.Broadcast(pSendBlob));
			}
#line 28 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			GameStrutTestUtil.Update(pServerSocket, pClientSocket);
			{
				gsBlob pReceiveBlob = pClientSocket.Receive();
#line 32 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
				Assert.Plz(pReceiveBlob != null);
				int nRecievedInt = 0;
#line 34 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
				Assert.Plz(pReceiveBlob.UnpackInt32(ref nRecievedInt));
#line 35 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
				Assert.Plz(nRecievedInt == 619);
			}
			{
				gsBlob pClientResponseBlob = new gsBlob();
#line 40 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
				pClientResponseBlob.PackInt32(420);
#line 41 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
				Assert.Plz(pClientSocket.Send(pClientResponseBlob));
			}
#line 44 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			GameStrutTestUtil.Update(pServerSocket, pClientSocket);
			{
				gsBlob pServerReceiveBlob = pServerClientSocket.Receive();
#line 48 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
				Assert.Plz(pServerReceiveBlob != null);
				int nServerReceivedInt = 0;
#line 50 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
				Assert.Plz(pServerReceiveBlob.UnpackInt32(ref nServerReceivedInt));
#line 51 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
				Assert.Plz(nServerReceivedInt == 420);
			}
#line 54 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			pClientSocket.Disconnect();
#line 55 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_AcceptSendRecieve.nll"
			pServerSocket.Stop();
		}

	}
}

