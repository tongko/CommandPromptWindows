#pragma once
#include	"Stdafx.h"
#include	"Msg.h"
#include	"Queue.h"

namespace Unmanaged {

	CQueue<MESSAGE> *	g_sysQ;
	
	DWORD WINAPI	Monitor(LPVOID lpParam);

	class CSysEventMonitor
	{
	public:
		CSysEventMonitor(HANDLE console) {
			if (g_sysQ == NULL)
				g_sysQ = new CQueue<MESSAGE>();

			m_console = console;
		}

		~CSysEventMonitor() {
			if (g_sysQ != NULL)
				delete g_sysQ;
		}

	public:
		void		Start() {
			m_stop = FALSE;
			m_thread = CreateThread(
				NULL,								// default security attributes
				0x00200000,							// default stack size - 2MB
				(LPTHREAD_START_ROUTINE) Monitor,
				(LPVOID)this,						// no thread function arguments
				0,									// default creation flags
				&m_threadId							// receive thread identifier
				);
		}

		BOOL		Discontinue() {
			return m_stop;
		}

		HANDLE		GetInputHandle() {
			return m_console;
		}

	private:
		HANDLE		m_console;
		HANDLE		m_thread;
		DWORD		m_threadId;
		BOOL		m_stop;
	};

	DWORD WINAPI	Monitor(LPVOID lpParam) {
		CSysEventMonitor * monitor = (CSysEventMonitor *)lpParam;
		INPUT_RECORD buffer[10];
		DWORD readCount = 0;

		while (!monitor->Discontinue())
		{
			if (!ReadConsoleInput(monitor->GetInputHandle(),
				buffer,
				10,
				&readCount)) {
				
			}
		}
	};
}