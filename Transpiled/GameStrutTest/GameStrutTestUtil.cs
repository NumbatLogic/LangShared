#line 1 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
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
#line 13 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				if (pServerSocket.Pending() || pClientSocket.Pending())
					nNotPendingCount = 0;
				else
					nNotPendingCount++;
				Utils.Sleep(5 + nNotPendingCount);
			}
		}

		public static void Update(gsServer pServer, gsClient pClient)
		{
			int nNotPendingCount = 0;
			while (nNotPendingCount < 10)
			{
				pServer.Update();
				pClient.Update();
#line 29 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				if (pServer.Pending() || pClient.GetPending())
					nNotPendingCount = 0;
				else
					nNotPendingCount++;
				Utils.Sleep(5 + nNotPendingCount);
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
#line 49 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
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
#line 63 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				if (bPending)
					nNotPendingCount = 0;
				else
					nNotPendingCount++;
				Utils.Sleep(5 + nNotPendingCount);
			}
		}

	}
}

