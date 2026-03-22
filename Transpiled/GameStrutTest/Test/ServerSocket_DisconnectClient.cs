#line 1 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
namespace NumbatLogic
{
	class ServerSocket_DisconnectClient
	{
		public static void Run()
		{
			gsServerSocket pServerSocket = new gsServerSocket();
			pServerSocket.Start(9877);
#line 10 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			gsClientSocket pClientSocket = new gsClientSocket();
			pClientSocket.Connect("localhost", 9877);
#line 13 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			GameStrutTestUtil.Update(pServerSocket, pClientSocket);
#line 15 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			gsClientSocket pServerClientSocket = pServerSocket.Accept();
			Assert.Plz(pServerClientSocket != null);
#line 18 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			Assert.Plz(pServerClientSocket.GetConnected());
			Assert.Plz(pClientSocket.GetConnected());
#line 21 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			pServerClientSocket.Disconnect();
#line 23 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			GameStrutTestUtil.Update(pServerSocket, pClientSocket);
#line 25 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			Assert.Plz(!pClientSocket.GetConnected());
			Assert.Plz(!pServerClientSocket.GetConnected());
#line 28 "/home/cliffya/git/LangShared/Source/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			pServerSocket.Stop();
		}

	}
}

