#line 1 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
	class Sync_ClientHandler_Server : gsServer
	{
#line 6 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public Sync_ClientHandler_Server(string sxAddress, ushort nPort, ushort nVersion, string sxDatabasePath) : base(sxAddress, nPort, nVersion, sxDatabasePath)
		{
		}

#line 10 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public override gsServerClient OnCreateServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer)
		{
#line 12 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			return new Sync_ClientHandler_ServerClient(nClientId, pClientSocket, pServer);
		}

	}
#line 16 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
	class Sync_ClientHandler_ServerClient : gsServerClient
	{
#line 18 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public Sync_ClientHandler_ServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer) : base(nClientId, pClientSocket, pServer)
		{
		}

#line 22 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public override void OnInitialJoin()
		{
			gsServerRoom pOwnedServerRoom = new gsServerRoom(++__pServer.__nLastRoomId, "Sync_ClientHandler_Room", __pServer);
			gsServerRoom pServerRoom = pOwnedServerRoom;
			NumbatLogic.gsServerRoom __1621810262 = pOwnedServerRoom;
#line 26 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			pOwnedServerRoom = null;
#line 26 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			__pServer.__pRoomVector.PushBack(__1621810262);
#line 27 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			__pServer.__ClientJoin(this, pServerRoom);
			gsBlob pTestBlob = new gsBlob();
#line 30 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			pTestBlob.PackUint32(42);
#line 31 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Send(null, 1986771282, pTestBlob);
		}

	}
#line 35 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
	class Sync_ClientHandler_Client : gsClient
	{
#line 37 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public uint m_nTestValue;
#line 39 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public Sync_ClientHandler_Client(string sxAddress, ushort nPort, ushort nVersion) : base(sxAddress, nPort, nVersion)
		{
#line 41 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			RegisterHandler(1986771282, OnTest);
		}

#line 44 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		protected static void OnTest(gsClient pClient, uint nSyncId, gsBlob pMessageBlob)
		{
			Sync_ClientHandler_Client pSyncClient = (Sync_ClientHandler_Client)(pClient);
#line 47 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Assert.Plz(pSyncClient != null);
#line 48 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Assert.Plz(pMessageBlob.UnpackUint32(ref pSyncClient.m_nTestValue));
		}

	}
#line 52 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
	class Sync_ClientHandler
	{
#line 54 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
		public static void Run()
		{
			gsServer pServer = new Sync_ClientHandler_Server("localhost", 9877, 0, "");
			gsClient pClient = new Sync_ClientHandler_Client("localhost", 9877, 0);
#line 59 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Assert.Plz(pServer.__pRoomVector.GetSize() == 0);
#line 61 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			GameStrutTestUtil.Update(pServer, pClient);
#line 63 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Assert.Plz(pServer.__pClientVector.GetSize() == 1);
#line 64 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Assert.Plz(pServer.__pRoomVector.GetSize() == 1);
#line 65 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Assert.Plz(pClient.__eState == gsClient.State.CONNECTED);
#line 66 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Assert.Plz(pClient.__pRoomVector.GetSize() == 1);
			Sync_ClientHandler_Client pSyncClient = (Sync_ClientHandler_Client)(pClient);
#line 69 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Assert.Plz(pSyncClient != null);
#line 70 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ClientHandler.nll"
			Assert.Plz(pSyncClient.m_nTestValue == 42);
			if (pServer != null) pServer.Dispose();
		}

	}
}

