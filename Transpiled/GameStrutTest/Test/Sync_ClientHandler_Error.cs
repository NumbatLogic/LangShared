namespace NumbatLogic
{
	class Sync_ClientHandler_Error_Server : gsServer
	{
		public Sync_ClientHandler_Error_Server(string sxAddress, ushort nPort, ushort nVersion, string sxDatabasePath) : base(sxAddress, nPort, nVersion, sxDatabasePath)
		{
		}

		public override gsServerClient OnCreateServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer)
		{
			return new Sync_ClientHandler_Error_ServerClient(nClientId, pClientSocket, pServer);
		}

	}
	class Sync_ClientHandler_Error_ServerClient : gsServerClient
	{
		public Sync_ClientHandler_Error_ServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer) : base(nClientId, pClientSocket, pServer)
		{
		}

		public override void OnInitialJoin()
		{
			gsServerRoom pRoom = new gsServerRoom(1234, "Sync_ClientHandler_Error_Room", __pServer);
			gsBlob pBlob = new gsBlob();
			Send(pRoom, 2223003848, pBlob);
		}

	}
	class Sync_ClientHandler_Error
	{
		public static void Run()
		{
			gsServer pServer = new Sync_ClientHandler_Error_Server("localhost", 9878, 0, "");
			gsClient pClient = new gsClient("localhost", 9878, 0);
			GameStrutTestUtil.Update(pServer, pClient);
			Assert.Plz(pClient.__eState == gsClient.State.ERRORED);
			if (pServer != null) pServer.Dispose();
		}

	}
}

