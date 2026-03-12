#line 1 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
namespace NumbatLogic
{
	class Sync_ClientHandler_Server : gsServer
	{
		public Sync_ClientHandler_Server(string sxAddress, ushort nPort, ushort nVersion, string sxDatabasePath) : base(sxAddress, nPort, nVersion, sxDatabasePath)
		{
		}

		public override gsServerClient OnCreateServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer)
		{
			return new Sync_ClientHandler_ServerClient(nClientId, pClientSocket, pServer);
		}

	}
	class Sync_ClientHandler_ServerClient : gsServerClient
	{
		public Sync_ClientHandler_ServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer) : base(nClientId, pClientSocket, pServer)
		{
		}

		public override void OnInitialJoin()
		{
			gsServerRoom pOwnedServerRoom = new gsServerRoom(++__pServer.__nLastRoomId, "Sync_ClientHandler_Room", __pServer);
			gsServerRoom pServerRoom = pOwnedServerRoom;
			NumbatLogic.gsServerRoom __1621810262 = pOwnedServerRoom;
#line 25 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			pOwnedServerRoom = null;
#line 25 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			__pServer.__pRoomVector.PushBack(__1621810262);
			__pServer.__ClientJoin(this, pServerRoom);
#line 28 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			gsBlob pTestBlob = new gsBlob();
			pTestBlob.PackUint32(42);
			Send(null, 1986771282, pTestBlob);
		}

	}
	class Sync_ClientHandler_Client : gsClient
	{
		public uint m_nTestValue;
#line 38 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public Sync_ClientHandler_Client(string sxAddress, ushort nPort, ushort nVersion) : base(sxAddress, nPort, nVersion)
		{
			RegisterHandler(1986771282, OnTest);
		}

		protected static void OnTest(gsClient pClient, uint nSyncId, gsBlob pMessageBlob)
		{
			Sync_ClientHandler_Client pSyncClient = (Sync_ClientHandler_Client)(pClient);
			Assert.Plz(pSyncClient != null);
			Assert.Plz(pMessageBlob.UnpackUint32(ref pSyncClient.m_nTestValue));
		}

	}
	class Sync_ClientHandler
	{
		public static void Run()
		{
			gsServer pServer = new Sync_ClientHandler_Server("localhost", 9877, 0, "");
			gsClient pClient = new Sync_ClientHandler_Client("localhost", 9877, 0);
#line 58 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Assert.Plz(pServer.__pRoomVector.GetSize() == 0);
#line 60 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			GameStrutTestUtil.Update(pServer, pClient);
#line 62 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Assert.Plz(pServer.__pClientVector.GetSize() == 1);
			Assert.Plz(pServer.__pRoomVector.GetSize() == 1);
			Assert.Plz(pClient.__eState == gsClient.State.CONNECTED);
			Assert.Plz(pClient.__pRoomVector.GetSize() == 1);
#line 67 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Sync_ClientHandler_Client pSyncClient = (Sync_ClientHandler_Client)(pClient);
			Assert.Plz(pSyncClient != null);
			Assert.Plz(pSyncClient.m_nTestValue == 42);
			if (pServer != null) pServer.Dispose();
		}

	}
}

