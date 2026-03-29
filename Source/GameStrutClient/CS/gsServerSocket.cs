using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Threading;

namespace NumbatLogic
{
	public class gsServerSocket
	{
		public Socket __pSocket = null;
		protected List<gsClientSocket> __pClientSockets = new List<gsClientSocket>();
		protected Queue<gsClientSocket> __pAcceptQueue = new Queue<gsClientSocket>();

		private void DrainIncomingConnections()
		{
			if (__pSocket == null)
				return;
			while (__pSocket.Poll(0, SelectMode.SelectRead))
			{
				try
				{
					Socket pIncomingSocket = __pSocket.Accept();
					if (pIncomingSocket == null)
						break;
					gsClientSocket pClientSocket = new gsClientSocket();
					pClientSocket.__pSocket = pIncomingSocket;
					pClientSocket.__bConnected = true;
					pIncomingSocket.Blocking = false;
					__pClientSockets.Add(pClientSocket);
					__pAcceptQueue.Enqueue(pClientSocket);
				}
				catch (SocketException)
				{
					break;
				}
			}
		}

		public void Start(int nPort)
		{
			Assert.Plz(__pSocket == null);
			Assert.Plz(__pClientSockets.Count == 0);
			Assert.Plz(__pAcceptQueue.Count == 0);
			
			IPHostEntry ipHostInfo = Dns.GetHostEntry("localhost");
			IPAddress ipAddress = ipHostInfo.AddressList[0];
			IPEndPoint ipEndPoint = new IPEndPoint(ipAddress, nPort);

			__pSocket = new Socket(ipEndPoint.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
			__pSocket.Blocking = false;
			__pSocket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, true);

			int nNumAttempt = 0;
			while (true)
			{
				try
				{
					__pSocket.Bind(ipEndPoint);
					break;
				}
				catch (SocketException ex)
				{
					if (ex.SocketErrorCode == SocketError.AddressAlreadyInUse && nNumAttempt < 20)
					{
						nNumAttempt++;
						Thread.Sleep(50);
						continue;
					}
					throw;
				}
			}
			__pSocket.Listen(100);
		}

		public void Stop()
		{
			if (__pSocket == null)
				return;

			__pAcceptQueue.Clear();
			while (__pClientSockets.Count > 0)
			{
				gsClientSocket pClientSocket = __pClientSockets[0];
				__pClientSockets.RemoveAt(0);
				pClientSocket.Disconnect();
			}

			__pSocket.Dispose();
			__pSocket = null;
		}
		
		public void Update()
		{
			DrainIncomingConnections();
			for (int i = 0; i < __pClientSockets.Count; i++)
			{
				gsClientSocket pClientSocket = __pClientSockets[i];
				pClientSocket.Update();
			}
		}

		public bool Pending()
		{
			if (__pSocket != null && __pSocket.Poll(0, SelectMode.SelectRead))
				return true;
			if (__pAcceptQueue.Count > 0)
				return true;
			for (int i = 0; i < __pClientSockets.Count; i++)
			{
				gsClientSocket pClientSocket = __pClientSockets[i];
				if (pClientSocket.Pending())
					return true;
			}
			return false;
		}
		
		public int GetNumClient()
		{
			return __pClientSockets.Count;
		}
		
		public gsClientSocket Accept()
		{
			if (__pAcceptQueue.Count > 0)
				return __pAcceptQueue.Dequeue();
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