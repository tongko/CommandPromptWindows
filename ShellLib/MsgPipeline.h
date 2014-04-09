#pragma	once

#include	"Stdafx.h"
#include	"Msg.h"
#include	"Queue.h"

namespace Unmanaged {

	CQueue<LPMESSAGE> *	g_msgQ;

	void InitializeMessageQueue() {
		if (g_msgQ != NULL) return;

		g_msgQ = new CQueue<LPMESSAGE>();
	};

	void FinalizeMessageQueue() {
		if (g_msgQ == NULL) return;

		delete g_msgQ;
	}

	BOOL WINAPI GetMessage(
		_Out_		LPMESSAGE lpMsg,
		_In_opt_	INT hWindow,
		_In_		UINT wMsgFilterMin,
		_In_		UINT wMsgFilterMax) {
		BOOL bResult = FALSE;
		LPMESSAGE msg = g_msgQ->Peek();
		if (msg != NULL) {
			if (hWindow == msg->hWindow) {
				if ((wMsgFilterMin == wMsgFilterMax == 0)
					|| (msg->message >= wMsgFilterMin && msg->message <= wMsgFilterMax)) {
					lpMsg = g_msgQ->Pop;
					bResult = TRUE;
				}
			}
		}
	};

	private class CMsgPipeline
	{
	};

}