#pragma once

namespace Unmanaged {

#define		MAX_INPUT_REC_READ	120

	DWORD WINAPI	Monitor(LPVOID lpParam) {
		CSysEventMonitor * monitor = (CSysEventMonitor *)lpParam;
		monitor->MonitorProc();
	};

	private class CSysEventMonitor
	{
	public:
		CSysEventMonitor();
		~CSysEventMonitor();

	public:
		void		Start();
		void		MonitorProc();

	protected:
		void		KeyEventProc(const KEY_EVENT_RECORD &ker);
		void		MouseEventProc(const MOUSE_EVENT_RECORD &mer);
		void		WinBufferSizeProc(const WINDOW_BUFFER_SIZE_RECORD &wbsr);

	private:
		HANDLE				m_console;
		HANDLE				m_thread;
		DWORD				m_threadId;
		BOOL				m_stop;
		CQueue<MESSAGE> *	m_sysQ;
	};
}