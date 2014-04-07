#pragma once
#include "LinkList.h"

namespace Unmanaged {

	class CMsgQueue : public CLinkList<MSG>
	{
	public:
		CMsgQueue();
		~CMsgQueue();
	};

}