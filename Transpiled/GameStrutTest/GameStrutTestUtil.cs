#line 1 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
	class GameStrutTestUtil
	{
#line 5 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
		public static void Update(gsServerSocket pServerSocket, gsClientSocket pClientSocket)
		{
#line 7 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
			int nNotPendingCount = 0;
#line 8 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
			while (nNotPendingCount < 10)
			{
#line 10 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				pServerSocket.Update();
#line 11 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				pClientSocket.Update();
#line 13 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				if (pServerSocket.Pending() || pClientSocket.Pending())
#line 14 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
					nNotPendingCount = 0;
				else
#line 16 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
					nNotPendingCount++;
#line 17 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				Utils.Sleep(5 + nNotPendingCount);
			}
		}

#line 21 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
		public static void Update(gsServer pServer, gsClient pClient)
		{
#line 23 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
			int nNotPendingCount = 0;
#line 24 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
			while (nNotPendingCount < 10)
			{
#line 26 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				pServer.Update();
#line 27 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				pClient.Update();
#line 29 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				if (pServer.Pending() || pClient.GetPending())
#line 30 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
					nNotPendingCount = 0;
				else
#line 32 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
					nNotPendingCount++;
#line 33 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				Utils.Sleep(5 + nNotPendingCount);
			}
		}

#line 37 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
		public static void UpdateVector(gsServer pServer, OwnedVector<gsClient> pClientVector)
		{
#line 39 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
			int nNotPendingCount = 0;
#line 40 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
			while (nNotPendingCount < 10)
			{
#line 42 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				pServer.Update();
#line 43 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				for (int i = 0; i < pClientVector.GetSize(); i++)
				{
#line 45 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
					gsClient pClient = pClientVector.Get(i);
#line 46 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
					pClient.Update();
				}
#line 49 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				bool bPending = pServer.Pending();
#line 50 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				if (!bPending)
				{
#line 52 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
					for (int i = 0; i < pClientVector.GetSize(); i++)
					{
#line 54 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
						gsClient pClient = pClientVector.Get(i);
#line 55 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
						if (pClient.GetPending())
						{
#line 57 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
							bPending = true;
#line 58 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
							break;
						}
					}
				}
#line 63 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				if (bPending)
#line 64 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
					nNotPendingCount = 0;
				else
#line 66 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
					nNotPendingCount++;
#line 67 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				Utils.Sleep(5 + nNotPendingCount);
			}
		}

	}
}

