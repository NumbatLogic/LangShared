#line 1 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
	class ServerSocket_DisconnectClient
	{
#line 6 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
		public static void Run()
		{
			gsServerSocket pServerSocket = new gsServerSocket();
#line 9 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			pServerSocket.Start(9877);
			gsClientSocket pClientSocket = new gsClientSocket();
#line 12 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			pClientSocket.Connect("localhost", 9877);
#line 14 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			GameStrutTestUtil.Update(pServerSocket, pClientSocket);
			gsClientSocket pServerClientSocket = pServerSocket.Accept();
#line 17 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			Assert.Plz(pServerClientSocket != null);
#line 19 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			Assert.Plz(pServerClientSocket.GetConnected());
#line 20 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			Assert.Plz(pClientSocket.GetConnected());
#line 22 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			pServerClientSocket.Disconnect();
#line 24 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			GameStrutTestUtil.Update(pServerSocket, pClientSocket);
#line 26 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			Assert.Plz(!pClientSocket.GetConnected());
#line 27 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			Assert.Plz(!pServerClientSocket.GetConnected());
#line 29 "../LangShared/Transpiled/GameStrutTest/Test/ServerSocket_DisconnectClient.nll"
			pServerSocket.Stop();
		}

	}
}

