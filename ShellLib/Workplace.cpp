#include "stdafx.h"
#include "MsgPipeline.h"
#include "Workplace.h"

using namespace Unmanaged;

namespace ShellLib {

	CWorkplace::CWorkplace() {
		InitializeMessageQueue();
	}

	CWorkplace::~CWorkplace() {
		FinalizeMessageQueue();
	}

}