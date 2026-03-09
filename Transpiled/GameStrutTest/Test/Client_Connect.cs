#line 1 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
	class Client_Connect_Server : gsServer
	{
#line 6 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		public Client_Connect_Server(string sxAddress, ushort nPort, ushort nVersion, string sxDatabasePath) : base(sxAddress, nPort, nVersion, sxDatabasePath)
		{
		}

#line 10 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		public override gsServerClient OnCreateServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer)
		{
#line 12 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			return new Client_Connect_ServerClient(nClientId, pClientSocket, pServer);
		}

	}
#line 16 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
	class Client_Connect_ServerClient : gsServerClient
	{
#line 18 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		public Client_Connect_ServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer) : base(nClientId, pClientSocket, pServer)
		{
		}

#line 22 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		public override void OnInitialJoin()
		{
			gsServerRoom pOwnedServerRoom = new gsServerRoom(++__pServer.__nLastRoomId, "Client_Connect_Room", __pServer);
			gsServerRoom pServerRoom = pOwnedServerRoom;
			NumbatLogic.gsServerRoom __1621810262 = pOwnedServerRoom;
#line 26 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			pOwnedServerRoom = null;
#line 26 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			__pServer.__pRoomVector.PushBack(__1621810262);
#line 27 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			__pServer.__ClientJoin(this, pServerRoom);
		}

	}
#line 31 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
	class Client_Connect_Client : gsClient
	{
#line 33 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		public Client_Connect_Client(string sxAddress, ushort nPort, ushort nVersion) : base(sxAddress, nPort, nVersion)
		{
		}

#line 37 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		public override gsClientRoom OnRoomJoin(uint nRoomId, uint nRoomTypeHash, bool bPrimary, gsBlob pJoinBlob)
		{
#line 39 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			return base.OnRoomJoin(nRoomId, nRoomTypeHash, bPrimary, pJoinBlob);
		}

	}
#line 44 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
	class Client_Connect
	{
#line 46 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
		public static void Run()
		{
			gsServer pServer = new Client_Connect_Server("localhost", 9876, 0, "");
			gsClient pClient = new Client_Connect_Client("localhost", 9876, 0);
#line 51 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			Assert.Plz(pServer.__pRoomVector.GetSize() == 0);
#line 53 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			GameStrutTestUtil.Update(pServer, pClient);
#line 56 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			Assert.Plz(pServer.__pClientVector.GetSize() == 1);
#line 57 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			Assert.Plz(pServer.__pRoomVector.GetSize() == 1);
			gsServerClient pServerClient = pServer.__pClientVector.Get(0);
#line 60 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			Assert.Plz(pServerClient.__pRoomVector.GetSize() == 1);
			gsServerRoom pServerRoom = pServer.__pRoomVector.Get(0);
#line 63 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			Assert.Plz(pServerRoom.__pClientVector.GetSize() == 1);
#line 66 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			Assert.Plz(pClient.__eState == gsClient.State.CONNECTED);
#line 67 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			Assert.Plz(pServerClient.__nClientId == pClient.__nClientId);
#line 69 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			Assert.Plz(pClient.__pRoomVector.GetSize() == 1);
			gsClientRoom pClientRoom = pClient.__pRoomVector.Get(0);
#line 71 "../LangShared/Transpiled/GameStrutTest/Test/Client_Connect.nll"
			Assert.Plz(pServerRoom.__nRoomId == pClientRoom.__nRoomId);
			if (pServer != null) pServer.Dispose();
		}

	}
}

