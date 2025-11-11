using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;

namespace NumbatLogic
{
	class gsServerSocket
	{
		public Socket __pSocket = null;
		protected List<gsClientSocket> __pClientSockets = new List<gsClientSocket>();

		public void Start(int nPort)
		{
			Assert.Plz(__pSocket == null);
			Assert.Plz(__pClientSockets.Count == 0);
			
			IPHostEntry ipHostInfo = Dns.GetHostEntry("localhost");
			IPAddress ipAddress = ipHostInfo.AddressList[0];
			IPEndPoint ipEndPoint = new IPEndPoint(ipAddress, nPort);

			__pSocket = new Socket(ipEndPoint.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
			__pSocket.Blocking = false;
			__pSocket.Bind(ipEndPoint);
			__pSocket.Listen(100);
		}

		public void Stop()
		{
			while (__pClientSockets.Count > 0)
			{
				gsClientSocket pClientSocket = __pClientSockets[0];
				__pClientSockets.RemoveAt(0);
				pClientSocket.Disconnect();
			}

			__pSocket.Dispose();
		}
		
		public void Update()
		{
			for (int i = 0; i < __pClientSockets.Count; i++)
			{
				gsClientSocket pClientSocket = __pClientSockets[i];
				pClientSocket.Update();
			}
		}

		public bool Pending()
		{
			for (int i = 0; i < __pClientSockets.Count; i++)
			{
				gsClientSocket pClientSocket = __pClientSockets[i];
				if (pClientSocket.Pending())
					return true;
			}
			return false;
		}
		
		public gsClientSocket Accept()
		{
			if (__pSocket.Poll(0, SelectMode.SelectRead))
			{
				Socket pIncomingSocket = __pSocket.Accept();
				if (pIncomingSocket != null)
				{
					gsClientSocket pClientSocket = new gsClientSocket();
					pClientSocket.__pSocket = pIncomingSocket;
					
					__pClientSockets.Add(pClientSocket);
					return pClientSocket;
				}
			}

			return null;
		}

		public bool Broadcast(gsBlob pBlob)
		{
			Assert.Plz(pBlob != null);
			Assert.Plz(__pSocket != null);
			
			for (int i = 0; i < __pClientSockets.Count; i++)
			{
				gsClientSocket pClientSocket = __pClientSockets[i];
				if (!pClientSocket.Send(pBlob))
					return false;
			}
			return true;
		}
	}
}