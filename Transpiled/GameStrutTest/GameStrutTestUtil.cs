#line 1 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
namespace NumbatLogic
{
#line 4 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
	class GameStrutTestUtil
	{
#line 6 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
		public static void Update(gsServerSocket pServerSocket, gsClientSocket pClientSocket)
		{
			int nNotPendingCount = 0;
#line 9 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
			while (nNotPendingCount < 10)
			{
#line 11 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				pServerSocket.Update();
#line 12 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				pClientSocket.Update();
#line 14 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				if (pServerSocket.Pending() || pClientSocket.Pending())
#line 15 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
					nNotPendingCount = 0;
				else
#line 17 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
					nNotPendingCount++;
#line 18 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				Utils.Sleep(5);
			}
		}

#line 22 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
		public static void Update(gsServer pServer, gsClient pClient)
		{
			int nNotPendingCount = 0;
#line 25 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
			while (nNotPendingCount < 10)
			{
#line 27 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				pServer.Update();
#line 28 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				pClient.Update();
#line 30 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				if (pServer.Pending() || pClient.GetPending())
#line 31 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
					nNotPendingCount = 0;
				else
#line 33 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
					nNotPendingCount++;
#line 34 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				Utils.Sleep(5);
			}
		}

#line 38 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
		public static void UpdateVector(gsServer pServer, OwnedVector<gsClient> pClientVector)
		{
			int nNotPendingCount = 0;
#line 41 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
			while (nNotPendingCount < 10)
			{
#line 43 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				pServer.Update();
#line 44 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				for (int i = 0; i < pClientVector.GetSize(); i++)
				{
					gsClient pClient = pClientVector.Get(i);
#line 47 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
					pClient.Update();
				}
				bool bPending = pServer.Pending();
#line 51 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				if (!bPending)
				{
#line 53 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
					for (int i = 0; i < pClientVector.GetSize(); i++)
					{
						gsClient pClient = pClientVector.Get(i);
#line 56 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
						if (pClient.GetPending())
						{
#line 58 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
							bPending = true;
#line 59 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
							break;
						}
					}
				}
#line 64 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				if (bPending)
#line 65 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
					nNotPendingCount = 0;
				else
#line 67 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
					nNotPendingCount++;
#line 68 "../LangShared/Transpiled/GameStrutTest/GameStrutTestUtil.nll"
				Utils.Sleep(5);
			}
		}

	}
}

