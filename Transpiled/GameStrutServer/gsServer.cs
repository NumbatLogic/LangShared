#line 1 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
	class gsServer : System.IDisposable
	{
#line 6 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public gsServer(string sxAddress, ushort nPort, ushort nVersion, string sxDatabasePath)
		{
#line 8 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			__sAddress = new InternalString(sxAddress);
#line 9 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			__nPort = nPort;
#line 10 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			__nVersion = nVersion;
#line 12 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			__pServerSocket = new gsServerSocket();
#line 13 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			__pServerSocket.Start(__nPort);
#line 15 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			__pRoomVector = new OwnedVector<gsServerRoom>();
#line 16 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			__pClientVector = new OwnedVector<gsServerClient>();
		}

		~gsServer()
		{
			Dispose();
		}

		public void Dispose()
		{
			{
#line 21 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				__pServerSocket.Stop();
			}
			System.GC.SuppressFinalize(this);
		}

#line 24 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public void Update()
		{
#line 26 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			__pServerSocket.Update();
			{
				gsClientSocket pClientSocket = __pServerSocket.Accept();
#line 30 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				if (pClientSocket != null)
				{
					gsServerClient pServerClient = OnCreateServerClient(++__nLastClientId, pClientSocket, this);
#line 33 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
					Assert.Plz(pServerClient != null);
					NumbatLogic.gsServerClient __1702162430 = pServerClient;
#line 34 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
					pServerClient = null;
#line 34 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
					__pClientVector.PushBack(__1702162430);
				}
			}
#line 38 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			for (int i = 0; i < __pClientVector.GetSize(); i++)
			{
				gsServerClient pServerClient = __pClientVector.Get(i);
#line 42 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				pServerClient.__Update();
			}
			{
				int i = 0;
#line 48 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				while (i < __pClientVector.GetSize())
				{
					gsServerClient pServerClient = __pClientVector.Get(i);
#line 51 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
					if (!pServerClient.__pClientSocket.GetConnected())
					{
#line 71 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
						__pClientVector.Erase(i);
#line 73 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
						continue;
					}
#line 75 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
					i++;
				}
			}
		}

#line 80 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public bool Pending()
		{
#line 82 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			return __pServerSocket.Pending();
		}

#line 85 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public virtual gsServerClient OnCreateServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer)
		{
#line 87 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			return new gsServerClient(nClientId, pClientSocket, this);
		}

#line 90 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public virtual gsServerRoom OnCreateRoom(uint nRoomId, uint nRoomType, gsBlob pCreateBlob)
		{
#line 92 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			return null;
		}

#line 96 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public virtual void Auth(gsBlob pAuthBlob, gsClientSocket pClientSocket)
		{
#line 98 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			Assert.Plz(false);
		}

#line 104 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public InternalString __sAddress;
#line 105 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public ushort __nPort;
#line 106 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public ushort __nVersion;
#line 108 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public gsServerSocket __pServerSocket;
#line 109 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public OwnedVector<gsServerClient> __pClientVector;
#line 110 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public OwnedVector<gsServerRoom> __pRoomVector;
#line 112 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public uint __nLastClientId;
#line 113 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public uint __nLastRoomId;
#line 116 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public void __ClientJoin(gsServerClient pClient, gsServerRoom pRoom)
		{
#line 122 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			while (pClient.__pRoomVector.GetSize() > 0)
			{
				gsServerRoom pCurrentRoom = pClient.__pRoomVector.Get(0);
#line 125 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				pCurrentRoom.__ClientLeave(pClient);
			}
#line 128 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			pRoom.__ClientJoin(pClient);
		}

#line 131 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public gsServerRoom __CreateRoom(string sxRoomType, gsBlob pCreateBlob)
		{
#line 133 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			pCreateBlob.SetOffset(0);
			uint nRoomType = ExternalString.GetChecksum(sxRoomType);
			gsServerRoom pOwnedRoom = OnCreateRoom(++__nLastRoomId, nRoomType, pCreateBlob);
#line 137 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			Assert.Plz(pOwnedRoom != null);
			gsServerRoom pRoom = pOwnedRoom;
			NumbatLogic.gsServerRoom __4188406598 = pOwnedRoom;
#line 139 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			pOwnedRoom = null;
#line 139 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			__pRoomVector.PushBack(__4188406598);
#line 140 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			return pRoom;
		}

	}
}

