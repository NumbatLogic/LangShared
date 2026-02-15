namespace NumbatLogic
{
	class Client_Errored_Server : gsServer
	{
		public Client_Errored_Server(string sxAddress, ushort nPort, ushort nVersion, string sxDatabasePath) : base(sxAddress, nPort, nVersion, sxDatabasePath)
		{
		}

		public override gsServerClient OnCreateServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer)
		{
			return new Client_Errored_ServerClient(nClientId, pClientSocket, pServer);
		}

	}
	class Client_Errored_ServerClient : gsServerClient
	{
		public Client_Errored_ServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer) : base(nClientId, pClientSocket, pServer)
		{
		}

		public override void OnInitialJoin()
		{
			gsServerRoom pRoom = new gsServerRoom(1234, "Client_Errored_Room", __pServer);
			gsBlob pBlob = new gsBlob();
			Send(pRoom, 2223003848, pBlob);
		}

	}
	class Client_Errored_Client : gsClient
	{
		public Client_Errored_Client(string sxAddress, ushort nPort, ushort nVersion) : base(sxAddress, nPort, nVersion)
		{
		}

		public override gsClientRoom OnRoomJoin(uint nRoomId, uint nRoomTypeHash, bool bPrimary, gsBlob pJoinBlob)
		{
			return base.OnRoomJoin(nRoomId, nRoomTypeHash, bPrimary, pJoinBlob);
		}

	}
	class Client_Errored
	{
		public static void Run()
		{
			gsServer pServer = new Client_Errored_Server("localhost", 9878, 0, "");
			gsClient pClient = new gsClient("localhost", 9878, 0);
			GameStrutTestUtil.Update(pServer, pClient);
			Assert.Plz(pClient.__eState == gsClient.State.ERRORED);
			if (pServer != null) pServer.Dispose();
		}

	}
}

