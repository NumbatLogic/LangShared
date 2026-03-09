#line 1 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	class Sync_ClientRoomHandler_Server : gsServer
	{
#line 6 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public Sync_ClientRoomHandler_Server(string sxAddress, ushort nPort, ushort nVersion, string sxDatabasePath) : base(sxAddress, nPort, nVersion, sxDatabasePath)
		{
		}

#line 10 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public override gsServerClient OnCreateServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer)
		{
#line 12 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			return new Sync_ClientRoomHandler_ServerClient(nClientId, pClientSocket, pServer);
		}

	}
#line 16 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	class Sync_ClientRoomHandler_ServerClient : gsServerClient
	{
#line 18 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public Sync_ClientRoomHandler_ServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer) : base(nClientId, pClientSocket, pServer)
		{
		}

#line 22 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public override void OnInitialJoin()
		{
			gsServerRoom pOwnedServerRoom = new gsServerRoom(++__pServer.__nLastRoomId, "Sync_ClientRoomHandler_Room", __pServer);
			gsServerRoom pServerRoom = pOwnedServerRoom;
			NumbatLogic.gsServerRoom __1621810262 = pOwnedServerRoom;
#line 26 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			pOwnedServerRoom = null;
#line 26 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			__pServer.__pRoomVector.PushBack(__1621810262);
#line 27 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			__pServer.__ClientJoin(this, pServerRoom);
			gsBlob pTestBlob = new gsBlob();
#line 30 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			pTestBlob.PackUint32(42);
#line 31 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			Send(pServerRoom, 395751469, pTestBlob);
		}

	}
#line 35 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	class Sync_ClientRoomHandler_ClientRoom : gsClientRoom
	{
#line 37 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public static string ROOM_TYPE = "Sync_ClientRoomHandler_Room";
#line 38 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public const uint ROOM_TYPE_HASH = 3638174234;
#line 40 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public uint m_nTestValue;
#line 42 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public Sync_ClientRoomHandler_ClientRoom(uint nRoomId, bool bPrimary, gsBlob pJoinBlob, gsClient pClient) : base(nRoomId, ROOM_TYPE, ROOM_TYPE_HASH, bPrimary, pClient)
		{
#line 44 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			RegisterHandler(395751469, OnRoomTest);
		}

#line 47 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		protected static void OnRoomTest(gsClient pClient, gsClientRoom pRoom, uint nSyncId, gsBlob pMessageBlob)
		{
			Sync_ClientRoomHandler_ClientRoom pRoomTyped = (Sync_ClientRoomHandler_ClientRoom)(pRoom);
#line 50 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			Assert.Plz(pRoomTyped != null);
#line 51 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			Assert.Plz(pMessageBlob.UnpackUint32(ref pRoomTyped.m_nTestValue));
		}

	}
#line 55 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	class Sync_ClientRoomHandler_Client : gsClient
	{
#line 57 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public Sync_ClientRoomHandler_Client(string sxAddress, ushort nPort, ushort nVersion) : base(sxAddress, nPort, nVersion)
		{
		}

#line 61 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public override gsClientRoom OnRoomJoin(uint nRoomId, uint nRoomTypeHash, bool bPrimary, gsBlob pJoinBlob)
		{
#line 63 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			if (nRoomTypeHash == Sync_ClientRoomHandler_ClientRoom.ROOM_TYPE_HASH)
#line 64 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
				return new Sync_ClientRoomHandler_ClientRoom(nRoomId, bPrimary, pJoinBlob, this);
#line 65 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			return base.OnRoomJoin(nRoomId, nRoomTypeHash, bPrimary, pJoinBlob);
		}

	}
#line 69 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
	class Sync_ClientRoomHandler
	{
#line 71 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
		public static void Run()
		{
			gsServer pServer = new Sync_ClientRoomHandler_Server("localhost", 9878, 0, "");
			gsClient pClient = new Sync_ClientRoomHandler_Client("localhost", 9878, 0);
#line 76 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			Assert.Plz(pServer.__pRoomVector.GetSize() == 0);
#line 78 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			GameStrutTestUtil.Update(pServer, pClient);
#line 80 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			Assert.Plz(pServer.__pClientVector.GetSize() == 1);
#line 81 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			Assert.Plz(pServer.__pRoomVector.GetSize() == 1);
#line 82 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			Assert.Plz(pClient.__eState == gsClient.State.CONNECTED);
#line 83 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			Assert.Plz(pClient.__pRoomVector.GetSize() == 1);
			gsClientRoom pRoom = pClient.__pRoomVector.Get(0);
			Sync_ClientRoomHandler_ClientRoom pRoomTyped = (Sync_ClientRoomHandler_ClientRoom)(pRoom);
#line 87 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			Assert.Plz(pRoomTyped != null);
#line 88 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientRoomHandler.nll"
			Assert.Plz(pRoomTyped.m_nTestValue == 42);
			if (pServer != null) pServer.Dispose();
		}

	}
}

