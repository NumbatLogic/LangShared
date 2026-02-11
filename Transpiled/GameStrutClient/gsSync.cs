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
			return false;
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
			__nRoomId = pRoom != null ? pRoom.__nRoomId : 0;
		}

		~gsSyncInner()
		{
			if (__pSync != null)
				__pSync.__pSyncInner = null;
		}

		public virtual void OnComplete(gsBlob pBlob, bool bAwaitRoomChange)
		{
			if (__pSync != null)
				__pSync.OnComplete(pBlob);
			if (bAwaitRoomChange)
				__bAwaitRoomChange = true;
			else
				__bComplete = true;
		}

		public gsSync __pSync;
		public uint __nSyncId;
		public InternalString __sSyncType;
		public uint __nSyncType;
		public bool __bComplete;
		public bool __bAwaitRoomChange;
		public uint __nRoomId;
	}
}

