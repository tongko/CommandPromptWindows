#include "Stdafx.h"
#include "WorkspaceConfigSection.h"
#include "ConInit.h"

namespace ShellLib {

	CConInit::CConInit()
	{
		m_hSync = CreateMutex(NULL, FALSE, CONINIT_MUTEX);
		ASSERT((m_hSync != NULL));
	}


	void CConInit::Initialize(CWorkspaceConfigSection ^ configSection) {
		StdOut = CreateScreenBuffer();
		StdErr = GetStdHandle(STD_ERROR_HANDLE);
		StdIn = GetStdHandle(STD_INPUT_HANDLE);

		//	Set screen buffer to configured size
		COORD crdSize = { configSection->Width, configSection->Height };
		ASSERT(SetConsoleScreenBufferSize(StdOut, crdSize));

		ResetScreenBufferInfo();


	}

	//
	//	Reset console screen buffer info
	//
	void	CConInit::ResetScreenBufferInfo(void) {
		lock(m_hSync, {

			ASSERT((StdOut != INVALID_HANDLE_VALUE));

			//	Get screen buffer info.
			if (m_pcsbi != NULL)
				delete m_pcsbi;

			m_pcsbi = new CONSOLE_SCREEN_BUFFER_INFOEX();
			m_pcsbi->cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
			ASSERT(GetConsoleScreenBufferInfoEx(StdOut, m_pcsbi));
		});
	}

	//
	//	Get Screen Buffer Information
	//
	PCONSOLE_SCREEN_BUFFER_INFOEX	CConInit::GetScreenBufferInfo(void) const {
		PCONSOLE_SCREEN_BUFFER_INFOEX p;

		lock(m_hSync, {
			p = m_pcsbi;
		});

		return p;
	}

	HANDLE	CConInit::CreateScreenBuffer(void) {
		HANDLE h = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			CONSOLE_TEXTMODE_BUFFER,
			NULL);
		ASSERT((h != INVALID_HANDLE_VALUE));

		return h;
	}

}