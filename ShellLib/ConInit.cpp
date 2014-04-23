#include "Stdafx.h"
#include "ConInit.h"

namespace ShellLib {

	using namespace ShellLib::Threading;

	COORD ConvertTo(CCoord manage) {
		COORD c = COORD();
		c.X = manage.X;
		c.Y = manage.Y;
		return c;
	}

	COORD ConvertTo(CSize manage) {
		COORD c = COORD();
		c.X = manage.Width;
		c.Y = manage.Height;
		return c;
	}

	CConInit::CConInit()
	{
		m_hSync = CreateMutex(NULL, FALSE, CONINIT_MUTEX);
		ASSERT((m_hSync != NULL));
	}

	CConInit::~CConInit(void) {
		//	Cleaning up
		if (m_oldCaption != NULL)
			delete[] m_oldCaption;
	}


	void CConInit::Initialize(CShellLibSettings ^ settings) {
		CLockGuard lock(m_hSync);
		StdOut = StdErr = GetStdHandle(STD_OUTPUT_HANDLE);
		StdIn = GetStdHandle(STD_INPUT_HANDLE);

		SaveShellCaption();

		StdOut = CreateScreenBuffer();

		//	Set screen buffer to configured size
		COORD crdSize = ConvertTo((settings->Layout.WindowSize));
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

	void							CConInit::SaveShellCaption(void) {
		TCHAR	szOld[MAX_PATH];
		DWORD	charRead = GetConsoleTitle(szOld, MAX_PATH);
		
		if (charRead == 0) return;
		m_oldCaption = new TCHAR[charRead]();
		HRESULT hr = StringCchCopy(m_oldCaption, charRead, szOld);
		if (FAILED(hr)) {
			System::Runtime::InteropServices::Marshal::ThrowExceptionForHR(hr);
		}
	}
}