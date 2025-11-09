namespace NumbatLogic
{
	class gsClientSocket : gsSocket
	{
		public void Connect(string sHost, int nPort)
		{
		}

		public void Disconnect()
		{
		}

		public void Update()
		{
		}

		public bool Pending()
		{
			return false;
		}

		public bool GetConnected()
		{
			return false;
		}

		public override bool Send(gsBlob pBlob)
		{
			return false;
		}

		public override gsBlob Receive()
		{
			return null;
		}

		public void SetAcceptedSocket(int socket)
		{
		}

		public uint GetClientSocketId() { return m_nClientSocketId; }
		public void SetClientSocketId(uint clientSocketId) { m_nClientSocketId = clientSocketId; }

		protected uint m_nClientSocketId;
	}
}