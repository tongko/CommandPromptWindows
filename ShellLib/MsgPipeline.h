#pragma	once

#include	"Stdafx.h"
#include	"Msg.h"
#include	"Queue.h"

namespace Unmanaged {

	CQueue<MSG*> *	g_msgQ;

	void InitializeMessageQueue() {
		if (g_msgQ != NULL) return;

		g_msgQ = new CQueue<MSG*>();
	};

	void FinalizeMessageQueue() {
		if (g_msgQ == NULL) return;

		delete g_msgQ;
	}

	BOOL WINAPI GetMessage(
		_Out_		LPMSG lpMsg,
		_In_opt_	INT hWindow,
		_In_		UINT wMsgFilterMin,
		_In_		UINT wMsgFilterMax) {

		LPMSG msg = g_msgQ->Peek();
		if (msg != NULL) {
			if (hWindow == msg->hWindow && msg->message >= wMsgFilterMin && msg->message <= wMsgFilterMax)
		}
	};

	private class CMsgPipeline
	{
	};

}