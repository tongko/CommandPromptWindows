#include	"Stdafx.h"
#include	"Msg.h"
#include	"Queue.h"
#include	"SysEventMonitor.h"

namespace Unmanaged {

	CSysEventMonitor::CSysEventMonitor()  {
		if (m_sysQ == NULL)
			m_sysQ = new CQueue<MESSAGE>();
	}

	CSysEventMonitor::~CSysEventMonitor() {
		if (m_sysQ != NULL)
			delete m_sysQ;
	}

	void CSysEventMonitor::Start() {
		m_stop = FALSE;
		m_thread = CreateThread(
			NULL,								// default security attributes
			0x00200000,							// default stack size - 2MB
			(LPTHREAD_START_ROUTINE)Monitor,
			(LPVOID)this,						// no thread function arguments
			0,									// default creation flags
			&m_threadId							// receive thread identifier
			);
	}

	void CSysEventMonitor::MonitorProc() {
		m_console = GetStdHandle(STD_INPUT_HANDLE);

		INPUT_RECORD ir[MAX_INPUT_REC_READ];
		DWORD recRead;

		while (!m_stop) {
			ASSERT(ReadConsoleInput(m_console, ir, MAX_INPUT_REC_READ, &recRead));
			for (DWORD i = 0; i < recRead; i++) {
				switch (ir[i].EventType) {
				case KEY_EVENT:
					KeyEventProc(ir[i].Event.KeyEvent);
					break;
				case MOUSE_EVENT:
					MouseEventProc(ir[i].Event.MouseEvent);
					break;
				case WINDOW_BUFFER_SIZE_EVENT:
					WinBufferSizeProc(ir[i].Event.WindowBufferSizeEvent);
					break;
				}
			}

		}
	}

	void CSysEventMonitor::KeyEventProc(const KEY_EVENT_RECORD & ker) {
		LPMESSAGE msg = new MESSAGE();
		msg->hWindow = 0;
		msg->message = 
	}

	void CSysEventMonitor::MouseEventProc(const MOUSE_EVENT_RECORD & mer) {

	}

	void CSysEventMonitor::WinBufferSizeProc(const WINDOW_BUFFER_SIZE_RECORD & wbsr) {

	}
}