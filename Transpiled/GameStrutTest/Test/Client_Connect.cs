namespace NumbatLogic
{
	class Client_Connect_Server : gsServer
	{
		public Client_Connect_Server(string sxAddress, ushort nPort, ushort nVersion, string sxDatabasePath) : base(sxAddress, nPort, nVersion, sxDatabasePath)
		{
		}

		public virtual gsServerClient OnCreateServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer)
		{
			return new Client_Connect_ServerClient(nClientId, pClientSocket, pServer);
		}

	}
	class Client_Connect_ServerClient : gsServerClient
	{
		public Client_Connect_ServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer) : base(nClientId, pClientSocket, pServer)
		{
		}

		public virtual void OnInitialJoin()
		{
			gsServerRoom pOwnedServerRoom = new gsServerRoom(__pServer.__nLastRoomId++, "Client_Connect_Room", __pServer);
			gsServerRoom pServerRoom = pOwnedServerRoom;
			NumbatLogic.gsServerRoom __214264756 = pOwnedServerRoom;
			pOwnedServerRoom = null;
			__pServer.__pRoomVector.PushBack(__214264756);
			__pServer.__ClientJoin(this, pServerRoom);
		}

	}
	class Client_Connect_Client : gsClient
	{
		public Client_Connect_Client(string sxAddress, ushort nPort, ushort nVersion) : base(sxAddress, nPort, nVersion)
		{
		}

		public virtual gsClientRoom OnRoomJoin(uint nRoomId, int nRoomTypeHash, bool bPrimary, gsBlob pJoinBlob)
		{
			return base.OnRoomJoin(nRoomId, nRoomTypeHash, bPrimary, pJoinBlob);
		}

	}
	class Client_Connect
	{
		public static void Run()
		{
			gsServer pServer = new Client_Connect_Server("localhost", 9876, 0, "");
			gsClient pClient = new Client_Connect_Client("localhost", 9876, 0);
			Assert.Plz(pServer.__pRoomVector.GetSize() == 0);
			GameStrutTestUtil.Update(pServer, pClient);
			Assert.Plz(pServer.__pClientVector.GetSize() == 1);
			Assert.Plz(pServer.__pRoomVector.GetSize() == 1);
			gsServerClient pServerClient = pServer.__pClientVector.Get(0);
			Assert.Plz(pServerClient.__pRoomVector.GetSize() == 1);
			gsServerRoom pServerRoom = pServer.__pRoomVector.Get(0);
			Assert.Plz(pServerRoom.__pClientVector.GetSize() == 1);
			Assert.Plz(pClient.__eState == gsClient.CONNECTED);
			Assert.Plz(pServerClient.__nClientId == pClient.__nClientId);
			Assert.Plz(pClient.__pRoomVector.GetSize() == 1);
			gsClientRoom pClientRoom = pClient.__pRoomVector.Get(0);
			Assert.Plz(pServerRoom.__nRoomId == pClientRoom.__nRoomId);
		}

	}
}

