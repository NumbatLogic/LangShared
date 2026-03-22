#line 1 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServer.nll"
namespace NumbatLogic
{
	class gsServer : System.IDisposable
	{
		public gsServer(string sxAddress, ushort nPort, ushort nVersion, string sxDatabasePath)
		{
			__sAddress = new InternalString(sxAddress);
			__nPort = nPort;
			__nVersion = nVersion;
#line 11 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServer.nll"
			__pServerSocket = new gsServerSocket();
			__pServerSocket.Start(__nPort);
#line 14 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServer.nll"
			__pRoomVector = new OwnedVector<gsServerRoom>();
			__pClientVector = new OwnedVector<gsServerClient>();
		}

		~gsServer()
		{
			Dispose();
		}

		public void Dispose()
		{
			{
#line 20 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServer.nll"
				__pServerSocket.Stop();
			}
			System.GC.SuppressFinalize(this);
		}

#line 23 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServer.nll"
		public void Update()
		{
			__pServerSocket.Update();
			{
#line 28 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServer.nll"
				gsClientSocket pClientSocket = __pServerSocket.Accept();
				if (pClientSocket != null)
				{
					gsServerClient pServerClient = OnCreateServerClient(++__nLastClientId, pClientSocket, this);
					Assert.Plz(pServerClient != null);
					NumbatLogic.gsServerClient __1702162430 = pServerClient;
#line 33 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServer.nll"
					pServerClient = null;
#line 33 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServer.nll"
					__pClientVector.PushBack(__1702162430);
				}
			}
#line 37 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServer.nll"
			for (int i = 0; i < __pClientVector.GetSize(); i++)
			{
				gsServerClient pServerClient = __pClientVector.Get(i);
#line 41 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServer.nll"
				pServerClient.__Update();
			}
			{
#line 46 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServer.nll"
				int i = 0;
				while (i < __pClientVector.GetSize())
				{
					gsServerClient pServerClient = __pClientVector.Get(i);
					if (!pServerClient.__pClientSocket.GetConnected())
					{
#line 70 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServer.nll"
						__pClientVector.Erase(i);
#line 72 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServer.nll"
						continue;
					}
					i++;
				}
			}
		}

		public bool Pending()
		{
			return __pServerSocket.Pending();
		}

		public virtual gsServerClient OnCreateServerClient(uint nClientId, gsClientSocket pClientSocket, gsServer pServer)
		{
			return new gsServerClient(nClientId, pClientSocket, this);
		}

		public virtual gsServerRoom OnCreateRoom(uint nRoomId, uint nRoomType, gsBlob pCreateBlob)
		{
			return null;
		}

#line 95 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServer.nll"
		public virtual void Auth(gsBlob pAuthBlob, gsClientSocket pClientSocket)
		{
			Assert.Plz(false);
		}

#line 103 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServer.nll"
		public InternalString __sAddress;
		public ushort __nPort;
		public ushort __nVersion;
#line 107 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServer.nll"
		public gsServerSocket __pServerSocket;
		public OwnedVector<gsServerClient> __pClientVector;
		public OwnedVector<gsServerRoom> __pRoomVector;
#line 111 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServer.nll"
		public uint __nLastClientId;
		public uint __nLastRoomId;
#line 115 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServer.nll"
		public void __ClientJoin(gsServerClient pClient, gsServerRoom pRoom)
		{
#line 121 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServer.nll"
			while (pClient.__pRoomVector.GetSize() > 0)
			{
				gsServerRoom pCurrentRoom = pClient.__pRoomVector.Get(0);
				pCurrentRoom.__ClientLeave(pClient);
			}
#line 127 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServer.nll"
			pRoom.__ClientJoin(pClient);
		}

		public gsServerRoom __CreateRoom(string sxRoomType, gsBlob pCreateBlob)
		{
			pCreateBlob.SetOffset(0);
#line 134 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServer.nll"
			uint nRoomType = ExternalString.GetChecksum(sxRoomType);
			gsServerRoom pOwnedRoom = OnCreateRoom(++__nLastRoomId, nRoomType, pCreateBlob);
			Assert.Plz(pOwnedRoom != null);
			gsServerRoom pRoom = pOwnedRoom;
			NumbatLogic.gsServerRoom __4188406598 = pOwnedRoom;
#line 138 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServer.nll"
			pOwnedRoom = null;
#line 138 "/home/cliffya/git/LangShared/Source/GameStrutServer/gsServer.nll"
			__pRoomVector.PushBack(__4188406598);
			return pRoom;
		}

	}
}

