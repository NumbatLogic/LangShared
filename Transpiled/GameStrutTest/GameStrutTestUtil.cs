namespace NumbatLogic
{
	class GameStrutTestUtil
	{
		public static void Update(gsServerSocket pServerSocket, gsClientSocket pClientSocket)
		{
			int nNotPendingCount = 0;
			while (nNotPendingCount < 10)
			{
				pServerSocket.Update();
				pClientSocket.Update();
				if (pServerSocket.Pending() || pClientSocket.Pending())
					nNotPendingCount = 0;
				else
					nNotPendingCount++;
				Utils.Sleep(5);
			}
		}

		public static void Update(gsServer pServer, gsClient pClient)
		{
			int nNotPendingCount = 0;
			while (nNotPendingCount < 10)
			{
				pServer.Update();
				pClient.Update();
				if (pServer.Pending() || pClient.GetPending())
					nNotPendingCount = 0;
				else
					nNotPendingCount++;
				Utils.Sleep(5);
			}
		}

		public static void UpdateVector(gsServer pServer, OwnedVector<gsClient> pClientVector)
		{
			int nNotPendingCount = 0;
			while (nNotPendingCount < 10)
			{
				pServer.Update();
				for (int i = 0; i < pClientVector.GetSize(); i++)
				{
					gsClient pClient = pClientVector.Get(i);
					pClient.Update();
				}
				bool bPending = pServer.Pending();
				if (!bPending)
				{
					for (int i = 0; i < pClientVector.GetSize(); i++)
					{
						gsClient pClient = pClientVector.Get(i);
						if (pClient.GetPending())
						{
							bPending = true;
							break;
						}
					}
				}
				if (bPending)
					nNotPendingCount = 0;
				else
					nNotPendingCount++;
				Utils.Sleep(5);
			}
		}

	}
}

