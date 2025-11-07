#pragma once

namespace NumbatLogic
{
	class gsClient;
	class InternalString;
}
namespace NumbatLogic
{
	class gsClientRoom
	{
		public: gsClientRoom(unsigned int nRoomId, const char* sxRoomType, unsigned int nRoomType, bool bPrimary, gsClient* pClient);
		public: unsigned int __nRoomId;
		public: InternalString* __sRoomType;
		public: unsigned int __nRoomTypeHash;
		public: bool __bPrimary;
		public: gsClient* __pClient;
		public: virtual ~gsClientRoom();
	};
}

