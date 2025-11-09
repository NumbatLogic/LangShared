namespace NumbatLogic
{
	class gsServer
	{
		public gsServer(string sxAddress, ushort nPort, ushort nVersion, string sxDatabasePath)
		{
			__sAddress = new InternalString(sxAddress);
			__nPort = nPort;
			__nVersion = nVersion;
			__pServerSocket = new gsServerSocket();
			__pServerSocket.Start(__nPort);
			__pRoomVector = new OwnedVector<gsServerRoom>();
			__pClientVector = new OwnedVector<gsServerClient>();
		}

		~gsServer()
		{
			__pServerSocket.Stop();
		}

		public void Update()
		{
			__pServerSocket.Update();
			{
				gsClientSocket pClientSocket = __pServerSocket.Accept();
				if (pClientSocket != null)
				{
					gsServerClient pServerClient = OnCreateServerClient(__nLastClientId++, pClientSocket, this);
					Assert.Plz(pServerClient != null);
					NumbatLogic.gsServerClient __206009596 = pServerClient;
					pServerClient = null;
					__pClientVector.PushBack(__206009596);
				}
			}
			for (int i = 0; i < __pClientVector.GetSize(); i++)
			{
				gsServerClient pServerClient = __pClientVector.Get(i);
				pServerClient.__Update();
			}
			{
				int i = 0;
				while (i < __pClientVector.GetSize())
				{
					gsServerClient pServerClient = __pClientVector.Get(i);
					if (!pServerClient.__pClientSocket.GetConnected())
					{
						__pClientVector.Erase(i);
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
			return new gsServerClient(__nLastClientId++, pClientSocket, this);
		}

		public virtual gsServerRoom OnCreateRoom(uint nRoomId, uint nRoomType, gsBlob pCreateBlob)
		{
			return null;
		}

		public virtual void Auth(gsBlob pAuthBlob, gsClientSocket pClientSocket)
		{
			Assert.Plz(false);
		}

		public InternalString __sAddress;
		public ushort __nPort;
		public ushort __nVersion;
		public gsServerSocket __pServerSocket;
		public OwnedVector<gsServerClient> __pClientVector;
		public OwnedVector<gsServerRoom> __pRoomVector;
		public uint __nLastClientId;
		public uint __nLastRoomId;
		public void __ClientJoin(gsServerClient pClient, gsServerRoom pRoom)
		{
			while (pClient.__pRoomVector.GetSize() > 0)
			{
				gsServerRoom pCurrentRoom = pClient.__pRoomVector.Get(0);
				pCurrentRoom.__ClientLeave(pClient);
			}
			pRoom.__ClientJoin(pClient);
		}

		public gsServerRoom __CreateRoom(string sxRoomType, gsBlob pCreateBlob)
		{
			pCreateBlob.SetOffset(0);
			uint nRoomType = ExternalString.GetChecksum(sxRoomType);
			gsServerRoom pOwnedRoom = OnCreateRoom(++__nLastRoomId, nRoomType, pCreateBlob);
			Assert.Plz(pOwnedRoom != null);
			gsServerRoom pRoom = pOwnedRoom;
			NumbatLogic.gsServerRoom __432254608 = pOwnedRoom;
			pOwnedRoom = null;
			__pRoomVector.PushBack(__432254608);
			return pRoom;
		}

	}
}

