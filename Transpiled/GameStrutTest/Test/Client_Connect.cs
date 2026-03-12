#line 1 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
	class Client_Connect_Server : gsServer
	{
#line 5 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		public Client_Connect_Server(string sxAddress, ushort nPort, ushort nVersion, string sxDatabasePath) : base(sxAddress, nPort, nVersion, sxDatabasePath)
		{
		}

#line 9 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		public override gsServerClient OnCreateServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer)
		{
#line 11 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			return new Client_Connect_ServerClient(nClientId, pClientSocket, pServer);
		}

	}
#line 15 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
	class Client_Connect_ServerClient : gsServerClient
	{
#line 17 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		public Client_Connect_ServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer) : base(nClientId, pClientSocket, pServer)
		{
		}

#line 21 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		public override void OnInitialJoin()
		{
#line 23 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			gsServerRoom pOwnedServerRoom = new gsServerRoom(++__pServer.__nLastRoomId, "Client_Connect_Room", __pServer);
#line 24 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			gsServerRoom pServerRoom = pOwnedServerRoom;
			NumbatLogic.gsServerRoom __1621810262 = pOwnedServerRoom;
#line 25 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			pOwnedServerRoom = null;
#line 25 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			__pServer.__pRoomVector.PushBack(__1621810262);
#line 26 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			__pServer.__ClientJoin(this, pServerRoom);
		}

	}
#line 30 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
	class Client_Connect_Client : gsClient
	{
#line 32 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		public Client_Connect_Client(string sxAddress, ushort nPort, ushort nVersion) : base(sxAddress, nPort, nVersion)
		{
		}

#line 36 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		public override gsClientRoom OnRoomJoin(uint nRoomId, uint nRoomTypeHash, bool bPrimary, gsBlob pJoinBlob)
		{
#line 38 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			return base.OnRoomJoin(nRoomId, nRoomTypeHash, bPrimary, pJoinBlob);
		}

	}
#line 43 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
	class Client_Connect
	{
#line 45 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		public static void Run()
		{
#line 47 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			gsServer pServer = new Client_Connect_Server("localhost", 9876, 0, "");
#line 48 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			gsClient pClient = new Client_Connect_Client("localhost", 9876, 0);
#line 50 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			Assert.Plz(pServer.__pRoomVector.GetSize() == 0);
#line 52 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			GameStrutTestUtil.Update(pServer, pClient);
#line 55 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			Assert.Plz(pServer.__pClientVector.GetSize() == 1);
#line 56 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			Assert.Plz(pServer.__pRoomVector.GetSize() == 1);
#line 58 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			gsServerClient pServerClient = pServer.__pClientVector.Get(0);
#line 59 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			Assert.Plz(pServerClient.__pRoomVector.GetSize() == 1);
#line 61 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			gsServerRoom pServerRoom = pServer.__pRoomVector.Get(0);
#line 62 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			Assert.Plz(pServerRoom.__pClientVector.GetSize() == 1);
#line 65 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			Assert.Plz(pClient.__eState == gsClient.State.CONNECTED);
#line 66 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			Assert.Plz(pServerClient.__nClientId == pClient.__nClientId);
#line 68 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			Assert.Plz(pClient.__pRoomVector.GetSize() == 1);
#line 69 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			gsClientRoom pClientRoom = pClient.__pRoomVector.Get(0);
#line 70 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			Assert.Plz(pServerRoom.__nRoomId == pClientRoom.__nRoomId);
			if (pServer != null) pServer.Dispose();
		}

	}
}

