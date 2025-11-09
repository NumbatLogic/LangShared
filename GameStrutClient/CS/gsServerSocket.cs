namespace NumbatLogic
{
	class gsServerSocket : gsSocket
	{
		public void Start(int port)
		{
		}

		public void Stop()
		{
			
		}
		
		public void Update()
		{
		}

		public bool Pending()
		{
			return false;
		}
		
		public gsClientSocket Accept()
		{
			return null;
		}

		public void Send(gsBlob pBlob, uint clientSocketId)
		{
		}



		/*public virtual bool Send(gsBlob pBlob)
		{
			return false;
		}

		public virtual gsBlob Receive()
		{
			return null;
		}*/
	}
}