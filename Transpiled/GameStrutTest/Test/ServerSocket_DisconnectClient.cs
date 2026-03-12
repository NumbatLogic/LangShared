#line 1 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
	class ServerSocket_DisconnectClient
	{
#line 5 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
		public static void Run()
		{
#line 7 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			gsServerSocket pServerSocket = new gsServerSocket();
#line 8 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			pServerSocket.Start(9877);
#line 10 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			gsClientSocket pClientSocket = new gsClientSocket();
#line 11 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			pClientSocket.Connect("localhost", 9877);
#line 13 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			GameStrutTestUtil.Update(pServerSocket, pClientSocket);
#line 15 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			gsClientSocket pServerClientSocket = pServerSocket.Accept();
#line 16 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			Assert.Plz(pServerClientSocket != null);
#line 18 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			Assert.Plz(pServerClientSocket.GetConnected());
#line 19 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			Assert.Plz(pClientSocket.GetConnected());
#line 21 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			pServerClientSocket.Disconnect();
#line 23 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			GameStrutTestUtil.Update(pServerSocket, pClientSocket);
#line 25 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			Assert.Plz(!pClientSocket.GetConnected());
#line 26 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			Assert.Plz(!pServerClientSocket.GetConnected());
#line 28 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			pServerSocket.Stop();
		}

	}
}

