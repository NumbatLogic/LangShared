namespace NumbatLogic
{
	class Sync_FromServer_Server : gsServer
	{
		public Sync_FromServer_Server(string sxAddress, ushort nPort, ushort nVersion, string sxDatabasePath) : base(sxAddress, nPort, nVersion, sxDatabasePath)
		{
		}

		public override gsServerClient OnCreateServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer)
		{
			return new Sync_FromServer_ServerClient(nClientId, pClientSocket, pServer);
		}

	}
	class Sync_FromServer_ServerClient : gsServerClient
	{
		public Sync_FromServer_ServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer) : base(nClientId, pClientSocket, pServer)
		{
		}

		public override void OnInitialJoin()
		{
			gsServerRoom pOwnedServerRoom = new gsServerRoom(__pServer.__nLastRoomId++, "Sync_FromServer_Room", __pServer);
			gsServerRoom pServerRoom = pOwnedServerRoom;
			NumbatLogic.gsServerRoom __1621810262 = pOwnedServerRoom;
			pOwnedServerRoom = null;
			__pServer.__pRoomVector.PushBack(__1621810262);
			__pServer.__ClientJoin(this, pServerRoom);
			gsBlob pTestBlob = new gsBlob();
			pTestBlob.PackUint32(42);
			Send(pServerRoom, 1986771282, pTestBlob);
		}

	}
	class Sync_FromServer_Client : gsClient
	{
		public uint m_nTestValue;
		public Sync_FromServer_Client(string sxAddress, ushort nPort, ushort nVersion) : base(sxAddress, nPort, nVersion)
		{
			RegisterHandler(1986771282, OnTest);
		}

		protected static bool OnTest(gsClient pClient, uint nSyncId, gsBlob pMessageBlob)
		{
			Sync_FromServer_Client pSyncClient = (Sync_FromServer_Client)(pClient);
			Assert.Plz(pSyncClient != null);
			Assert.Plz(pMessageBlob.UnpackUint32(ref pSyncClient.m_nTestValue));
			return true;
		}

	}
	class Sync_FromServer
	{
		public static void Run()
		{
			gsServer pServer = new Sync_FromServer_Server("localhost", 9877, 0, "");
			gsClient pClient = new Sync_FromServer_Client("localhost", 9877, 0);
			Assert.Plz(pServer.__pRoomVector.GetSize() == 0);
			GameStrutTestUtil.Update(pServer, pClient);
			Assert.Plz(pServer.__pClientVector.GetSize() == 1);
			Assert.Plz(pServer.__pRoomVector.GetSize() == 1);
			Assert.Plz(pClient.__eState == gsClient.State.CONNECTED);
			Assert.Plz(pClient.__pRoomVector.GetSize() == 1);
			Sync_FromServer_Client pSyncClient = (Sync_FromServer_Client)(pClient);
			Assert.Plz(pSyncClient != null);
			Assert.Plz(pSyncClient.m_nTestValue == 42);
			if (pServer != null) pServer.Dispose();
		}

	}
}

