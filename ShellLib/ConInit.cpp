#include "Stdafx.h"
#include "WorkspaceConfigSection.h"
#include "ConInit.h"

namespace ShellLib {

	using namespace ShellLib::Threading;

	CConInit::CConInit()
	{
		m_hSync = CreateMutex(NULL, FALSE, CONINIT_MUTEX);
		ASSERT((m_hSync != NULL));
	}


	void CConInit::Initialize(CWorkspaceConfigSection ^ configSection) {
		CLockGuard lock(m_hSync);

		StdOut = CreateScreenBuffer();
		StdErr = GetStdHandle(STD_ERROR_HANDLE);
		StdIn = GetStdHandle(STD_INPUT_HANDLE);

		//	Set screen buffer to configured size
		COORD crdSize = { configSection->Width, configSection->Height };
		ASSERT(SetConsoleScreenBufferSize(StdOut, crdSize));

		ResetScreenBufferInfoInternal();
	}

	//
	//	Reset console screen buffer info
	//
	void	CConInit::ResetScreenBufferInfo(void) {
		CLockGuard lock(m_hSync);
		ResetScreenBufferInfoInternal();
	}

	void	CConInit::ResetScreenBufferInfoInternal(void) {
		ASSERT((StdOut != INVALID_HANDLE_VALUE));

		//	Get screen buffer info.
		if (m_pcsbi != NULL)
			delete m_pcsbi;

		m_pcsbi = new CONSOLE_SCREEN_BUFFER_INFOEX();
		m_pcsbi->cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
		ASSERT(GetConsoleScreenBufferInfoEx(StdOut, m_pcsbi));
	}

	//
	//	Get Screen Buffer Information interface
	//
	PCONSOLE_SCREEN_BUFFER_INFOEX	CConInit::GetScreenBufferInfo(void) const {
		CLockGuard lock(m_hSync);
		return m_pcsbi;
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