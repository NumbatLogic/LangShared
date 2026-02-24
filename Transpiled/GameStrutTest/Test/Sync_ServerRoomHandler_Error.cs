namespace NumbatLogic
{
	class Sync_ServerRoomHandler_Error_Server : gsServer
	{
		public Sync_ServerRoomHandler_Error_Server(string sxAddress, ushort nPort, ushort nVersion, string sxDatabasePath) : base(sxAddress, nPort, nVersion, sxDatabasePath)
		{
		}

		public override gsServerClient OnCreateServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer)
		{
			return new Sync_ServerRoomHandler_Error_ServerClient(nClientId, pClientSocket, pServer);
		}

	}
	class Sync_ServerRoomHandler_Error_ServerClient : gsServerClient
	{
		public Sync_ServerRoomHandler_Error_ServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer) : base(nClientId, pClientSocket, pServer)
		{
		}

		public override void OnInitialJoin()
		{
			gsServerRoom pOwnedServerRoom = new gsServerRoom(++__pServer.__nLastRoomId, "Sync_ServerRoomHandler_Error_Room", __pServer);
			gsServerRoom pServerRoom = pOwnedServerRoom;
			NumbatLogic.gsServerRoom __1621810262 = pOwnedServerRoom;
			pOwnedServerRoom = null;
			__pServer.__pRoomVector.PushBack(__1621810262);
			__pServer.__ClientJoin(this, pServerRoom);
		}

	}
	class Sync_ServerRoomHandler_Error_ClientRoom : gsClientRoom
	{
		public static string ROOM_TYPE = "Sync_ServerRoomHandler_Error_Room";
		public const uint ROOM_TYPE_HASH = 3685084777;
		public Sync_ServerRoomHandler_Error_ClientRoom(uint nRoomId, bool bPrimary, gsBlob pJoinBlob, gsClient pClient) : base(nRoomId, ROOM_TYPE, ROOM_TYPE_HASH, bPrimary, pClient)
		{
		}

	}
	class Sync_ServerRoomHandler_Error_Client : gsClient
	{
		public gsSync __pDummySync;
		public Sync_ServerRoomHandler_Error_Client(string sxAddress, ushort nPort, ushort nVersion) : base(sxAddress, nPort, nVersion)
		{
		}

		public override gsClientRoom OnRoomJoin(uint nRoomId, uint nRoomTypeHash, bool bPrimary, gsBlob pJoinBlob)
		{
			if (nRoomTypeHash == Sync_ServerRoomHandler_Error_ClientRoom.ROOM_TYPE_HASH)
			{
				gsClientRoom pRoom = new Sync_ServerRoomHandler_Error_ClientRoom(nRoomId, bPrimary, pJoinBlob, this);
				__pDummySync = new gsSync();
				gsBlob pBlob = new gsBlob();
				SyncSend(__pDummySync, "Dummy", pBlob, gsSync.Response.EXPECT_RESPONSE, pRoom);
				NumbatLogic.gsClientRoom __2731727373 = pRoom;
				pRoom = null;
				return __2731727373;
			}
			return base.OnRoomJoin(nRoomId, nRoomTypeHash, bPrimary, pJoinBlob);
		}

		~Sync_ServerRoomHandler_Error_Client()
		{
		}

	}
	class Sync_ServerRoomHandler_Error
	{
		public static void Run()
		{
			gsServer pServer = new Sync_ServerRoomHandler_Error_Server("localhost", 9879, 0, "");
			gsClient pClient = new Sync_ServerRoomHandler_Error_Client("localhost", 9879, 0);
			GameStrutTestUtil.Update(pServer, pClient);
			Assert.Plz(!pClient.__pClientSocket.GetConnected());
			Assert.Plz(pServer.__pClientVector.GetSize() == 0);
			if (pServer != null) pServer.Dispose();
		}

	}
}

