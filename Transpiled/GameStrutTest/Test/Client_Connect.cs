#line 1 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
namespace NumbatLogic
{
	class Client_Connect_Server : gsServer
	{
		public Client_Connect_Server(string sxAddress, ushort nPort, ushort nVersion, string sxDatabasePath) : base(sxAddress, nPort, nVersion, sxDatabasePath)
		{
		}

		public override gsServerClient OnCreateServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer)
		{
			return new Client_Connect_ServerClient(nClientId, pClientSocket, pServer);
		}

	}
	class Client_Connect_ServerClient : gsServerClient
	{
		public Client_Connect_ServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer) : base(nClientId, pClientSocket, pServer)
		{
		}

		public override void OnInitialJoin()
		{
			gsServerRoom pOwnedServerRoom = new gsServerRoom(++__pServer.__nLastRoomId, "Client_Connect_Room", __pServer);
			gsServerRoom pServerRoom = pOwnedServerRoom;
			NumbatLogic.gsServerRoom __1621810262 = pOwnedServerRoom;
#line 25 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			pOwnedServerRoom = null;
#line 25 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			__pServer.__pRoomVector.PushBack(__1621810262);
			__pServer.__ClientJoin(this, pServerRoom);
		}

	}
	class Client_Connect_Client : gsClient
	{
		public Client_Connect_Client(string sxAddress, ushort nPort, ushort nVersion) : base(sxAddress, nPort, nVersion)
		{
		}

		public override gsClientRoom OnRoomJoin(uint nRoomId, uint nRoomTypeHash, bool bPrimary, gsBlob pJoinBlob)
		{
			return base.OnRoomJoin(nRoomId, nRoomTypeHash, bPrimary, pJoinBlob);
		}

	}
#line 43 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
	class Client_Connect
	{
		public static void Run()
		{
			gsServer pServer = new Client_Connect_Server("localhost", 9876, 0, "");
			gsClient pClient = new Client_Connect_Client("localhost", 9876, 0);
#line 50 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			Assert.Plz(pServer.__pRoomVector.GetSize() == 0);
#line 52 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			GameStrutTestUtil.Update(pServer, pClient);
#line 55 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			Assert.Plz(pServer.__pClientVector.GetSize() == 1);
			Assert.Plz(pServer.__pRoomVector.GetSize() == 1);
#line 58 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			gsServerClient pServerClient = pServer.__pClientVector.Get(0);
			Assert.Plz(pServerClient.__pRoomVector.GetSize() == 1);
#line 61 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			gsServerRoom pServerRoom = pServer.__pRoomVector.Get(0);
			Assert.Plz(pServerRoom.__pClientVector.GetSize() == 1);
#line 65 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			Assert.Plz(pClient.__eState == gsClient.State.CONNECTED);
			Assert.Plz(pServerClient.__nClientId == pClient.__nClientId);
#line 68 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			Assert.Plz(pClient.__pRoomVector.GetSize() == 1);
			gsClientRoom pClientRoom = pClient.__pRoomVector.Get(0);
			Assert.Plz(pServerRoom.__nRoomId == pClientRoom.__nRoomId);
			if (pServer != null) pServer.Dispose();
		}

	}
}

