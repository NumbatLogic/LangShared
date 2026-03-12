#line 1 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
namespace NumbatLogic
{
	class Sync_ClientRoomHandler_Server : gsServer
	{
		public Sync_ClientRoomHandler_Server(string sxAddress, ushort nPort, ushort nVersion, string sxDatabasePath) : base(sxAddress, nPort, nVersion, sxDatabasePath)
		{
		}

		public override gsServerClient OnCreateServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer)
		{
			return new Sync_ClientRoomHandler_ServerClient(nClientId, pClientSocket, pServer);
		}

	}
	class Sync_ClientRoomHandler_ServerClient : gsServerClient
	{
		public Sync_ClientRoomHandler_ServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer) : base(nClientId, pClientSocket, pServer)
		{
		}

		public override void OnInitialJoin()
		{
			gsServerRoom pOwnedServerRoom = new gsServerRoom(++__pServer.__nLastRoomId, "Sync_ClientRoomHandler_Room", __pServer);
			gsServerRoom pServerRoom = pOwnedServerRoom;
			NumbatLogic.gsServerRoom __1621810262 = pOwnedServerRoom;
#line 25 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			pOwnedServerRoom = null;
#line 25 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			__pServer.__pRoomVector.PushBack(__1621810262);
			__pServer.__ClientJoin(this, pServerRoom);
#line 28 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			gsBlob pTestBlob = new gsBlob();
			pTestBlob.PackUint32(42);
			Send(pServerRoom, 395751469, pTestBlob);
		}

	}
	class Sync_ClientRoomHandler_ClientRoom : gsClientRoom
	{
		public static string ROOM_TYPE = "Sync_ClientRoomHandler_Room";
		public const uint ROOM_TYPE_HASH = 3638174234;
#line 39 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public uint m_nTestValue;
#line 41 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public Sync_ClientRoomHandler_ClientRoom(uint nRoomId, bool bPrimary, gsBlob pJoinBlob, gsClient pClient) : base(nRoomId, ROOM_TYPE, ROOM_TYPE_HASH, bPrimary, pClient)
		{
			RegisterHandler(395751469, OnRoomTest);
		}

		protected static void OnRoomTest(gsClient pClient, gsClientRoom pRoom, uint nSyncId, gsBlob pMessageBlob)
		{
			Sync_ClientRoomHandler_ClientRoom pRoomTyped = (Sync_ClientRoomHandler_ClientRoom)(pRoom);
			Assert.Plz(pRoomTyped != null);
			Assert.Plz(pMessageBlob.UnpackUint32(ref pRoomTyped.m_nTestValue));
		}

	}
	class Sync_ClientRoomHandler_Client : gsClient
	{
		public Sync_ClientRoomHandler_Client(string sxAddress, ushort nPort, ushort nVersion) : base(sxAddress, nPort, nVersion)
		{
		}

		public override gsClientRoom OnRoomJoin(uint nRoomId, uint nRoomTypeHash, bool bPrimary, gsBlob pJoinBlob)
		{
			if (nRoomTypeHash == Sync_ClientRoomHandler_ClientRoom.ROOM_TYPE_HASH)
				return new Sync_ClientRoomHandler_ClientRoom(nRoomId, bPrimary, pJoinBlob, this);
			return base.OnRoomJoin(nRoomId, nRoomTypeHash, bPrimary, pJoinBlob);
		}

	}
	class Sync_ClientRoomHandler
	{
		public static void Run()
		{
			gsServer pServer = new Sync_ClientRoomHandler_Server("localhost", 9878, 0, "");
			gsClient pClient = new Sync_ClientRoomHandler_Client("localhost", 9878, 0);
#line 75 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			Assert.Plz(pServer.__pRoomVector.GetSize() == 0);
#line 77 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			GameStrutTestUtil.Update(pServer, pClient);
#line 79 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			Assert.Plz(pServer.__pClientVector.GetSize() == 1);
			Assert.Plz(pServer.__pRoomVector.GetSize() == 1);
			Assert.Plz(pClient.__eState == gsClient.State.CONNECTED);
			Assert.Plz(pClient.__pRoomVector.GetSize() == 1);
#line 84 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			gsClientRoom pRoom = pClient.__pRoomVector.Get(0);
			Sync_ClientRoomHandler_ClientRoom pRoomTyped = (Sync_ClientRoomHandler_ClientRoom)(pRoom);
			Assert.Plz(pRoomTyped != null);
			Assert.Plz(pRoomTyped.m_nTestValue == 42);
			if (pServer != null) pServer.Dispose();
		}

	}
}

