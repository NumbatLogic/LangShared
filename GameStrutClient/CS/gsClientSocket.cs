using System.Net;
using System.Net.Sockets;
using System;

namespace NumbatLogic
{
	class gsClientSocket
	{
		public Socket __pSocket;
		
		public byte[] __pRecieveBuffer = null;
		public int __nRecieveOffset = 0;

		public bool __bRecentSend = false;


		public void Connect(string sHost, int nPort)
		{
			IPHostEntry pIPHostEntry = Dns.GetHostEntry(sHost);
			IPAddress pIPAddress = pIPHostEntry.AddressList[0];
			IPEndPoint pIPEndPoint = new IPEndPoint(pIPAddress, nPort);

			__pSocket = new Socket(pIPEndPoint.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
			__pSocket.Connect(pIPEndPoint);
			__pSocket.Blocking = false;
		}

		public void Disconnect()
		{
		}

		public void Update()
		{
			__bRecentSend = false;

			if (__pSocket.Poll(0, SelectMode.SelectRead))
			{
				if (__pRecieveBuffer == null)
					__pRecieveBuffer = new byte[1024];

				if (__nRecieveOffset > __pRecieveBuffer.Length - 32)
				{
					int nNewSize = __pRecieveBuffer.Length * 2;
					Assert.Plz(nNewSize < 1024 * 32);

					Array.Resize(ref __pRecieveBuffer, nNewSize);
				}

				int nReadSize = __pSocket.Receive(__pRecieveBuffer, __nRecieveOffset, __pRecieveBuffer.Length - __nRecieveOffset, SocketFlags.None);
				__nRecieveOffset += nReadSize;
			}
		}

		public bool Pending()
		{
			return !GetConnected() || __bRecentSend;
		}

		public bool GetConnected()
		{
			return __pSocket != null && __pSocket.Connected;
		}

		public bool Send(gsBlob pBlob)
		{
			Assert.Plz(pBlob != null);
			Assert.Plz(pBlob.GetSize() > 0);

			ushort nBlobSize = (ushort)pBlob.__nSize;

			int nSendSize = __pSocket.Send(System.BitConverter.GetBytes(nBlobSize), SocketFlags.None);
			Assert.Plz(nSendSize == 2);
			
			nSendSize = __pSocket.Send(pBlob.__pBuffer, 0, pBlob.__nSize, SocketFlags.None);
			Assert.Plz(nSendSize == pBlob.__nSize);

			__bRecentSend = true;

			return true;
		}

		public gsBlob Receive()
		{
			if (__nRecieveOffset >= 2)
			{
				ushort nBlobSize = System.BitConverter.ToUInt16(__pRecieveBuffer);

				
				if (nBlobSize <= __nRecieveOffset - 2)
				{
					gsBlob pBlob = new gsBlob();

					pBlob.Resize(nBlobSize);
					System.Buffer.BlockCopy(__pRecieveBuffer, 2, pBlob.__pBuffer, 0, nBlobSize);


					int nRecieveRemain = __nRecieveOffset - nBlobSize - 2;
					if (nRecieveRemain > 0)
						System.Buffer.BlockCopy(__pRecieveBuffer, nBlobSize + 2, __pRecieveBuffer, 0, nRecieveRemain);
					__nRecieveOffset = nRecieveRemain;

					return pBlob;
				}
			}
			return null;
		}
	}
}