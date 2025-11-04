namespace NumbatLogic
{
	class gsSync
	{
		public gsSync()
		{
		}

		~gsSync()
		{
			if (__pSyncInner != null)
				__pSyncInner.__pSync = null;
		}

		public bool GetComplete()
		{
			return __pSyncInner != null ? __pSyncInner.__bComplete : false;
		}

		public bool GetError()
		{
			return __pSyncInner != null ? __pSyncInner.__bError : false;
		}

		public virtual void OnComplete(gsBlob pBlob)
		{
		}

		public gsSyncInner __pSyncInner;
	}
	class gsSyncInner
	{
		public gsSyncInner(gsSync pSync, uint nSyncId, string sxSyncType, gsClientRoom pRoom, gsClient pClient)
		{
			__pSync = pSync;
			__nSyncId = nSyncId;
			__sSyncType = new InternalString(sxSyncType);
			__nSyncType = ExternalString.GetChecksum(sxSyncType);
		}

		~gsSyncInner()
		{
			if (__pSync != null)
				__pSync.__pSyncInner = null;
		}

		public virtual void OnComplete(gsBlob pBlob)
		{
			if (__pSync != null)
				__pSync.OnComplete(pBlob);
			__bComplete = true;
		}

		public gsSync __pSync;
		public uint __nSyncId;
		public InternalString __sSyncType;
		public int __nSyncType;
		public bool __bComplete;
		public bool __bError;
	}
}

