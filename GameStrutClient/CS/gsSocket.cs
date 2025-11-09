namespace NumbatLogic
{
	class gsSocket
	{
		public virtual bool Send(gsBlob pBlob)
		{
			return false;
		}

		public virtual gsBlob Receive()
		{
			return null;
		}
	}
}