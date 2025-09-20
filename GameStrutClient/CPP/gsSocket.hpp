#pragma once

namespace NumbatLogic
{
    class gsBlob;
	class gsSocket
	{
		public:
			virtual bool Send(gsBlob* pBlob);
			virtual gsBlob* Receive();
	};
}