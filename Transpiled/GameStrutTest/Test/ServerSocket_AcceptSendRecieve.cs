namespace NumbatLogic
{
	class ServerSocket_AcceptSendRecieve
	{
		public static void Run()
		{
			gsServerSocket pServerSocket = new gsServerSocket();
			pServerSocket.Start(9876);
			gsClientSocket pClientSocket = new gsClientSocket();
			pClientSocket.Connect("localhost", 9876);
			GameStrutTestUtil.Update(pServerSocket, pClientSocket);
			gsClientSocket pServerClientSocket = pServerSocket.Accept();
			Assert.Plz(pServerClientSocket != null);
			{
				gsBlob pSendBlob = new gsBlob();
				pSendBlob.PackInt32(619);
				pServerSocket.Send(pSendBlob, 0);
			}
			GameStrutTestUtil.Update(pServerSocket, pClientSocket);
			{
				gsBlob pReceiveBlob = pClientSocket.Receive();
				Assert.Plz(pReceiveBlob != null);
				int nRecievedInt;
				Assert.Plz(pReceiveBlob.UnpackInt32(nRecievedInt));
				Assert.Plz(nRecievedInt == 619);
			}
			{
				gsBlob pClientResponseBlob = new gsBlob();
				pClientResponseBlob.PackInt32(420);
				pClientSocket.Send(pClientResponseBlob);
			}
			GameStrutTestUtil.Update(pServerSocket, pClientSocket);
			{
				gsBlob pServerReceiveBlob = pServerClientSocket.Receive();
				Assert.Plz(pServerReceiveBlob != null);
				int nServerReceivedInt;
				Assert.Plz(pServerReceiveBlob.UnpackInt32(nServerReceivedInt));
				Assert.Plz(nServerReceivedInt == 420);
			}
			pClientSocket.Disconnect();
			pServerSocket.Stop();
		}

	}
}

