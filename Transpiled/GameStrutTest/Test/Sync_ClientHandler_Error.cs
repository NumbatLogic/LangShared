#line 1 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
	class Sync_ClientHandler_Error_Server : gsServer
	{
#line 5 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		public Sync_ClientHandler_Error_Server(string sxAddress, ushort nPort, ushort nVersion, string sxDatabasePath) : base(sxAddress, nPort, nVersion, sxDatabasePath)
		{
		}

#line 9 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		public override gsServerClient OnCreateServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer)
		{
#line 11 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
			return new Sync_ClientHandler_Error_ServerClient(nClientId, pClientSocket, pServer);
		}

	}
#line 15 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
	class Sync_ClientHandler_Error_ServerClient : gsServerClient
	{
#line 17 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		public Sync_ClientHandler_Error_ServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer) : base(nClientId, pClientSocket, pServer)
		{
		}

#line 21 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		public override void OnInitialJoin()
		{
#line 23 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
			gsServerRoom pRoom = new gsServerRoom(1234, "Sync_ClientHandler_Error_Room", __pServer);
#line 24 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
			gsBlob pBlob = new gsBlob();
#line 25 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
			Send(pRoom, 2223003848, pBlob);
		}

	}
#line 29 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
	class Sync_ClientHandler_Error
	{
#line 31 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		public static void Run()
		{
#line 33 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
			gsServer pServer = new Sync_ClientHandler_Error_Server("localhost", 9878, 0, "");
#line 34 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
			gsClient pClient = new gsClient("localhost", 9878, 0);
#line 36 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
			GameStrutTestUtil.Update(pServer, pClient);
#line 37 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
			Assert.Plz(pClient.__eState == gsClient.State.ERRORED);
#line 38 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
			Assert.Plz(!pClient.__pClientSocket.GetConnected());
			if (pServer != null) pServer.Dispose();
		}

	}
}

