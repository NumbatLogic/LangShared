#pragma once

#include <vector>
//#include "../../Blob/CPP/Blob.hpp"


namespace NumbatLogic
{
    class Blob;
	class Socket
	{
		public:
			virtual bool Send(Blob* pBlob);
			virtual Blob* Receive();
	};
}