#line 1 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	class Sync_ServerRoomHandler_Error_Server : gsServer
	{
#line 6 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public Sync_ServerRoomHandler_Error_Server(string sxAddress, ushort nPort, ushort nVersion, string sxDatabasePath) : base(sxAddress, nPort, nVersion, sxDatabasePath)
		{
		}

#line 10 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public override gsServerClient OnCreateServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer)
		{
#line 12 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
			return new Sync_ServerRoomHandler_Error_ServerClient(nClientId, pClientSocket, pServer);
		}

	}
#line 16 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	class Sync_ServerRoomHandler_Error_ServerClient : gsServerClient
	{
#line 18 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public Sync_ServerRoomHandler_Error_ServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer) : base(nClientId, pClientSocket, pServer)
		{
		}

#line 22 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public override void OnInitialJoin()
		{
			gsServerRoom pOwnedServerRoom = new gsServerRoom(++__pServer.__nLastRoomId, "Sync_ServerRoomHandler_Error_Room", __pServer);
			gsServerRoom pServerRoom = pOwnedServerRoom;
			NumbatLogic.gsServerRoom __1621810262 = pOwnedServerRoom;
#line 26 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
			pOwnedServerRoom = null;
#line 26 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
			__pServer.__pRoomVector.PushBack(__1621810262);
#line 27 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
			__pServer.__ClientJoin(this, pServerRoom);
		}

	}
#line 31 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	class Sync_ServerRoomHandler_Error_ClientRoom : gsClientRoom
	{
#line 33 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public static string ROOM_TYPE = "Sync_ServerRoomHandler_Error_Room";
#line 34 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public const uint ROOM_TYPE_HASH = 3685084777;
#line 36 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public Sync_ServerRoomHandler_Error_ClientRoom(uint nRoomId, bool bPrimary, gsBlob pJoinBlob, gsClient pClient) : base(nRoomId, ROOM_TYPE, ROOM_TYPE_HASH, bPrimary, pClient)
		{
		}

	}
#line 41 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	class Sync_ServerRoomHandler_Error_Client : gsClient
	{
#line 43 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public gsSync __pDummySync;
#line 45 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public Sync_ServerRoomHandler_Error_Client(string sxAddress, ushort nPort, ushort nVersion) : base(sxAddress, nPort, nVersion)
		{
		}

#line 50 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public override gsClientRoom OnRoomJoin(uint nRoomId, uint nRoomTypeHash, bool bPrimary, gsBlob pJoinBlob)
		{
#line 52 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
			if (nRoomTypeHash == Sync_ServerRoomHandler_Error_ClientRoom.ROOM_TYPE_HASH)
			{
				gsClientRoom pRoom = new Sync_ServerRoomHandler_Error_ClientRoom(nRoomId, bPrimary, pJoinBlob, this);
#line 55 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
				__pDummySync = new gsSync();
				gsBlob pBlob = new gsBlob();
#line 57 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
				SyncSend(__pDummySync, "Dummy", pBlob, gsSync.Response.EXPECT_RESPONSE, pRoom);
				NumbatLogic.gsClientRoom __2731727373 = pRoom;
#line 58 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
				pRoom = null;
#line 58 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
				return __2731727373;
			}
#line 60 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
			return base.OnRoomJoin(nRoomId, nRoomTypeHash, bPrimary, pJoinBlob);
		}

#line 41 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		~Sync_ServerRoomHandler_Error_Client()
		{
		}

	}
#line 64 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
	class Sync_ServerRoomHandler_Error
	{
#line 66 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
		public static void Run()
		{
			gsServer pServer = new Sync_ServerRoomHandler_Error_Server("localhost", 9879, 0, "");
			gsClient pClient = new Sync_ServerRoomHandler_Error_Client("localhost", 9879, 0);
#line 71 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
			GameStrutTestUtil.Update(pServer, pClient);
#line 73 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
			Assert.Plz(!pClient.__pClientSocket.GetConnected());
#line 74 "../LangShared/Transpiled/GameStrutTest/Test/Sync_ServerRoomHandler_Error.nll"
			Assert.Plz(pServer.__pClientVector.GetSize() == 0);
			if (pServer != null) pServer.Dispose();
		}

	}
}

