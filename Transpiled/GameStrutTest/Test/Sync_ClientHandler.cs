#line 1 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
	class Sync_ClientHandler_Server : gsServer
	{
#line 5 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public Sync_ClientHandler_Server(string sxAddress, ushort nPort, ushort nVersion, string sxDatabasePath) : base(sxAddress, nPort, nVersion, sxDatabasePath)
		{
		}

#line 9 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public override gsServerClient OnCreateServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer)
		{
#line 11 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			return new Sync_ClientHandler_ServerClient(nClientId, pClientSocket, pServer);
		}

	}
#line 15 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
	class Sync_ClientHandler_ServerClient : gsServerClient
	{
#line 17 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public Sync_ClientHandler_ServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer) : base(nClientId, pClientSocket, pServer)
		{
		}

#line 21 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public override void OnInitialJoin()
		{
#line 23 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			gsServerRoom pOwnedServerRoom = new gsServerRoom(++__pServer.__nLastRoomId, "Sync_ClientHandler_Room", __pServer);
#line 24 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			gsServerRoom pServerRoom = pOwnedServerRoom;
			NumbatLogic.gsServerRoom __1621810262 = pOwnedServerRoom;
#line 25 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			pOwnedServerRoom = null;
#line 25 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			__pServer.__pRoomVector.PushBack(__1621810262);
#line 26 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			__pServer.__ClientJoin(this, pServerRoom);
#line 28 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			gsBlob pTestBlob = new gsBlob();
#line 29 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			pTestBlob.PackUint32(42);
#line 30 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Send(null, 1986771282, pTestBlob);
		}

	}
#line 34 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
	class Sync_ClientHandler_Client : gsClient
	{
#line 36 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public uint m_nTestValue;
#line 38 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public Sync_ClientHandler_Client(string sxAddress, ushort nPort, ushort nVersion) : base(sxAddress, nPort, nVersion)
		{
#line 40 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			RegisterHandler(1986771282, OnTest);
		}

#line 43 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		protected static void OnTest(gsClient pClient, uint nSyncId, gsBlob pMessageBlob)
		{
#line 45 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Sync_ClientHandler_Client pSyncClient = (Sync_ClientHandler_Client)(pClient);
#line 46 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Assert.Plz(pSyncClient != null);
#line 47 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Assert.Plz(pMessageBlob.UnpackUint32(ref pSyncClient.m_nTestValue));
		}

	}
#line 51 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
	class Sync_ClientHandler
	{
#line 53 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public static void Run()
		{
#line 55 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			gsServer pServer = new Sync_ClientHandler_Server("localhost", 9877, 0, "");
#line 56 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			gsClient pClient = new Sync_ClientHandler_Client("localhost", 9877, 0);
#line 58 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Assert.Plz(pServer.__pRoomVector.GetSize() == 0);
#line 60 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			GameStrutTestUtil.Update(pServer, pClient);
#line 62 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Assert.Plz(pServer.__pClientVector.GetSize() == 1);
#line 63 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Assert.Plz(pServer.__pRoomVector.GetSize() == 1);
#line 64 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Assert.Plz(pClient.__eState == gsClient.State.CONNECTED);
#line 65 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Assert.Plz(pClient.__pRoomVector.GetSize() == 1);
#line 67 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Sync_ClientHandler_Client pSyncClient = (Sync_ClientHandler_Client)(pClient);
#line 68 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Assert.Plz(pSyncClient != null);
#line 69 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Assert.Plz(pSyncClient.m_nTestValue == 42);
			if (pServer != null) pServer.Dispose();
		}

	}
}

