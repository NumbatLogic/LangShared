#line 1 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
	class Sync_ClientHandler_Error_Server : gsServer
	{
#line 6 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		public Sync_ClientHandler_Error_Server(string sxAddress, ushort nPort, ushort nVersion, string sxDatabasePath) : base(sxAddress, nPort, nVersion, sxDatabasePath)
		{
		}

#line 10 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		public override gsServerClient OnCreateServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer)
		{
#line 12 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
			return new Sync_ClientHandler_Error_ServerClient(nClientId, pClientSocket, pServer);
		}

	}
#line 16 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
	class Sync_ClientHandler_Error_ServerClient : gsServerClient
	{
#line 18 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		public Sync_ClientHandler_Error_ServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer) : base(nClientId, pClientSocket, pServer)
		{
		}

#line 22 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		public override void OnInitialJoin()
		{
			gsServerRoom pRoom = new gsServerRoom(1234, "Sync_ClientHandler_Error_Room", __pServer);
			gsBlob pBlob = new gsBlob();
#line 26 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
			Send(pRoom, 2223003848, pBlob);
		}

	}
#line 30 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
	class Sync_ClientHandler_Error
	{
#line 32 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
		public static void Run()
		{
			gsServer pServer = new Sync_ClientHandler_Error_Server("localhost", 9878, 0, "");
			gsClient pClient = new gsClient("localhost", 9878, 0);
#line 37 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
			GameStrutTestUtil.Update(pServer, pClient);
#line 38 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
			Assert.Plz(pClient.__eState == gsClient.State.ERRORED);
#line 39 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler_Error.nll"
			Assert.Plz(!pClient.__pClientSocket.GetConnected());
			if (pServer != null) pServer.Dispose();
		}

	}
}

