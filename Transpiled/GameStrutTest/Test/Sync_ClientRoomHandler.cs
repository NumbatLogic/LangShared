#line 1 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	class Sync_ClientRoomHandler_Server : gsServer
	{
#line 5 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public Sync_ClientRoomHandler_Server(string sxAddress, ushort nPort, ushort nVersion, string sxDatabasePath) : base(sxAddress, nPort, nVersion, sxDatabasePath)
		{
		}

#line 9 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public override gsServerClient OnCreateServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer)
		{
#line 11 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			return new Sync_ClientRoomHandler_ServerClient(nClientId, pClientSocket, pServer);
		}

	}
#line 15 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	class Sync_ClientRoomHandler_ServerClient : gsServerClient
	{
#line 17 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public Sync_ClientRoomHandler_ServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer) : base(nClientId, pClientSocket, pServer)
		{
		}

#line 21 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public override void OnInitialJoin()
		{
#line 23 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			gsServerRoom pOwnedServerRoom = new gsServerRoom(++__pServer.__nLastRoomId, "Sync_ClientRoomHandler_Room", __pServer);
#line 24 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			gsServerRoom pServerRoom = pOwnedServerRoom;
			NumbatLogic.gsServerRoom __1621810262 = pOwnedServerRoom;
#line 25 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			pOwnedServerRoom = null;
#line 25 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			__pServer.__pRoomVector.PushBack(__1621810262);
#line 26 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			__pServer.__ClientJoin(this, pServerRoom);
#line 28 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			gsBlob pTestBlob = new gsBlob();
#line 29 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			pTestBlob.PackUint32(42);
#line 30 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			Send(pServerRoom, 395751469, pTestBlob);
		}

	}
#line 34 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	class Sync_ClientRoomHandler_ClientRoom : gsClientRoom
	{
#line 36 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public static string ROOM_TYPE = "Sync_ClientRoomHandler_Room";
#line 37 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public const uint ROOM_TYPE_HASH = 3638174234;
#line 39 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public uint m_nTestValue;
#line 41 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public Sync_ClientRoomHandler_ClientRoom(uint nRoomId, bool bPrimary, gsBlob pJoinBlob, gsClient pClient) : base(nRoomId, ROOM_TYPE, ROOM_TYPE_HASH, bPrimary, pClient)
		{
#line 43 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			RegisterHandler(395751469, OnRoomTest);
		}

#line 46 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		protected static void OnRoomTest(gsClient pClient, gsClientRoom pRoom, uint nSyncId, gsBlob pMessageBlob)
		{
#line 48 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			Sync_ClientRoomHandler_ClientRoom pRoomTyped = (Sync_ClientRoomHandler_ClientRoom)(pRoom);
#line 49 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			Assert.Plz(pRoomTyped != null);
#line 50 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			Assert.Plz(pMessageBlob.UnpackUint32(ref pRoomTyped.m_nTestValue));
		}

	}
#line 54 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	class Sync_ClientRoomHandler_Client : gsClient
	{
#line 56 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public Sync_ClientRoomHandler_Client(string sxAddress, ushort nPort, ushort nVersion) : base(sxAddress, nPort, nVersion)
		{
		}

#line 60 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public override gsClientRoom OnRoomJoin(uint nRoomId, uint nRoomTypeHash, bool bPrimary, gsBlob pJoinBlob)
		{
#line 62 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			if (nRoomTypeHash == Sync_ClientRoomHandler_ClientRoom.ROOM_TYPE_HASH)
#line 63 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
				return new Sync_ClientRoomHandler_ClientRoom(nRoomId, bPrimary, pJoinBlob, this);
#line 64 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			return base.OnRoomJoin(nRoomId, nRoomTypeHash, bPrimary, pJoinBlob);
		}

	}
#line 68 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	class Sync_ClientRoomHandler
	{
#line 70 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public static void Run()
		{
#line 72 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			gsServer pServer = new Sync_ClientRoomHandler_Server("localhost", 9878, 0, "");
#line 73 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			gsClient pClient = new Sync_ClientRoomHandler_Client("localhost", 9878, 0);
#line 75 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			Assert.Plz(pServer.__pRoomVector.GetSize() == 0);
#line 77 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			GameStrutTestUtil.Update(pServer, pClient);
#line 79 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			Assert.Plz(pServer.__pClientVector.GetSize() == 1);
#line 80 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			Assert.Plz(pServer.__pRoomVector.GetSize() == 1);
#line 81 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			Assert.Plz(pClient.__eState == gsClient.State.CONNECTED);
#line 82 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			Assert.Plz(pClient.__pRoomVector.GetSize() == 1);
#line 84 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			gsClientRoom pRoom = pClient.__pRoomVector.Get(0);
#line 85 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			Sync_ClientRoomHandler_ClientRoom pRoomTyped = (Sync_ClientRoomHandler_ClientRoom)(pRoom);
#line 86 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			Assert.Plz(pRoomTyped != null);
#line 87 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			Assert.Plz(pRoomTyped.m_nTestValue == 42);
			if (pServer != null) pServer.Dispose();
		}

	}
}

