#line 1 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
	class gsServer : System.IDisposable
	{
#line 5 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public gsServer(string sxAddress, ushort nPort, ushort nVersion, string sxDatabasePath)
		{
#line 7 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			__sAddress = new InternalString(sxAddress);
#line 8 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			__nPort = nPort;
#line 9 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			__nVersion = nVersion;
#line 11 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			__pServerSocket = new gsServerSocket();
#line 12 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			__pServerSocket.Start(__nPort);
#line 14 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			__pRoomVector = new OwnedVector<gsServerRoom>();
#line 15 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			__pClientVector = new OwnedVector<gsServerClient>();
		}

		~gsServer()
		{
			Dispose();
		}

		public void Dispose()
		{
			{
#line 20 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				__pServerSocket.Stop();
			}
			System.GC.SuppressFinalize(this);
		}

#line 23 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public void Update()
		{
#line 25 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			__pServerSocket.Update();
			{
#line 28 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				gsClientSocket pClientSocket = __pServerSocket.Accept();
#line 29 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				if (pClientSocket != null)
				{
#line 31 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
					gsServerClient pServerClient = OnCreateServerClient(++__nLastClientId, pClientSocket, this);
#line 32 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
					Assert.Plz(pServerClient != null);
					NumbatLogic.gsServerClient __1702162430 = pServerClient;
#line 33 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
					pServerClient = null;
#line 33 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
					__pClientVector.PushBack(__1702162430);
				}
			}
#line 37 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			for (int i = 0; i < __pClientVector.GetSize(); i++)
			{
#line 39 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				gsServerClient pServerClient = __pClientVector.Get(i);
#line 41 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				pServerClient.__Update();
			}
			{
#line 46 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				int i = 0;
#line 47 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				while (i < __pClientVector.GetSize())
				{
#line 49 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
					gsServerClient pServerClient = __pClientVector.Get(i);
#line 50 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
					if (!pServerClient.__pClientSocket.GetConnected())
					{
#line 70 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
						__pClientVector.Erase(i);
#line 72 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
						continue;
					}
#line 74 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
					i++;
				}
			}
		}

#line 79 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public bool Pending()
		{
#line 81 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			return __pServerSocket.Pending();
		}

#line 84 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public virtual gsServerClient OnCreateServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer)
		{
#line 86 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			return new gsServerClient(nClientId, pClientSocket, this);
		}

#line 89 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public virtual gsServerRoom OnCreateRoom(uint nRoomId, uint nRoomType, gsBlob pCreateBlob)
		{
#line 91 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			return null;
		}

#line 95 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public virtual void Auth(gsBlob pAuthBlob, gsClientSocket pClientSocket)
		{
#line 97 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			Assert.Plz(false);
		}

#line 103 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public InternalString __sAddress;
#line 104 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public ushort __nPort;
#line 105 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public ushort __nVersion;
#line 107 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public gsServerSocket __pServerSocket;
#line 108 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public OwnedVector<gsServerClient> __pClientVector;
#line 109 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public OwnedVector<gsServerRoom> __pRoomVector;
#line 111 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public uint __nLastClientId;
#line 112 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public uint __nLastRoomId;
#line 115 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public void __ClientJoin(gsServerClient pClient, gsServerRoom pRoom)
		{
#line 121 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			while (pClient.__pRoomVector.GetSize() > 0)
			{
#line 123 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				gsServerRoom pCurrentRoom = pClient.__pRoomVector.Get(0);
#line 124 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
				pCurrentRoom.__ClientLeave(pClient);
			}
#line 127 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			pRoom.__ClientJoin(pClient);
		}

#line 130 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
		public gsServerRoom __CreateRoom(string sxRoomType, gsBlob pCreateBlob)
		{
#line 132 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			pCreateBlob.SetOffset(0);
#line 134 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			uint nRoomType = ExternalString.GetChecksum(sxRoomType);
#line 135 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			gsServerRoom pOwnedRoom = OnCreateRoom(++__nLastRoomId, nRoomType, pCreateBlob);
#line 136 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			Assert.Plz(pOwnedRoom != null);
#line 137 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			gsServerRoom pRoom = pOwnedRoom;
			NumbatLogic.gsServerRoom __4188406598 = pOwnedRoom;
#line 138 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			pOwnedRoom = null;
#line 138 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			__pRoomVector.PushBack(__4188406598);
#line 139 "../LangShared/Transpiled/GameStrutServer/gsServer.nll"
			return pRoom;
		}

	}
}

