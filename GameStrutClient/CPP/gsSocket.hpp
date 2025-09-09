#pragma once

namespace NumbatLogic
{
    class Blob;
	class gsSocket
	{
		public:
			virtual bool Send(Blob* pBlob);
			virtual Blob* Receive();
	};
}