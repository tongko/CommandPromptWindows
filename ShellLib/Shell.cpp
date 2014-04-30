#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include "Shell.h"

namespace shllib {

	using namespace ShellLib;
	using namespace ShellLib::Threading;

	CShell::CShell()
	{
		m_hMutex = CreateMutex(NULL, FALSE, NULL);
	}

	CShell::~CShell(void) {
		if (m_pcsbi != NULL)
			delete m_pcsbi;
		if (m_hMutex != NULL)
			CloseHandle(m_hMutex);
	}

	void	CShell::Clear(void) {
		CLockGuard lock(m_hMutex);

		GetInfo();

		COORD	coord = { 0, 0 };
		DWORD	dwLength = m_pcsbi->dwSize.X * m_pcsbi->dwSize.Y;

		FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE),
			_T(' '),
			dwLength,
			coord,
			&m_dwCharsWritten);

		FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			m_pcsbi->wAttributes,
			m_pcsbi->dwSize.X * m_pcsbi->dwSize.Y,
			coord,
			&m_dwCharsWritten);

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}

	void	CShell::SetColor(WORD wColor, WORD wMask) {
		CLockGuard lock(m_hMutex);

		GetInfo();
		m_pcsbi->wAttributes &= wMask;
		m_pcsbi->wAttributes |= wColor;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), m_pcsbi->wAttributes);
	}

	BOOL	CShell::SetBufferSize(COORD newSize) {
		CLockGuard lock(m_hMutex);

		GetInfo();
		m_pcsbi->dwSize.X = newSize.X;
		m_pcsbi->dwSize.Y = newSize.Y;

		if (!SetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), m_pcsbi)) {
			_tcerr << endl << _T("ERROR: Failed to set console screen buffer size.")
				<< __FILET__ << _T(" at function ") << __FUNCTIONT__ << _T(": line ")
				<< __LINE__ << endl;

		}
	}

	BOOL	CShell::SetWindowLayout(CRectangle srNew) {
		CLockGuard lock(m_hMutex);

		GetInfo();
		if (m_pcsbi->dwSize.X < srNew.Width
			|| m_pcsbi->dwSize.Y < srNew.Height)
			throw exception();
	}

	BOOL	CShell::GetInfo(PCONSOLE_SCREEN_BUFFER_INFOEX pcsbi) {
		CLockGuard lock(m_hMutex);

		if (pcsbi == NULL) return;

		GetInfo();
		if (!ShallowCopy(m_pcsbi, pcsbi)) {
			_tcerr << endl << _T("ERROR: Buffer pointed to by pcsbi has an invalid size.") << endl
				<< __FILET__ << _T("at functoin ") << __FUNCTIONT__ << _T(": line ")
				<< __LINE__ << endl;
			return FALSE;
		}

		return TRUE;
	}

	void	CShell::GetInfo(void) {
		if (m_pcsbi == NULL) {
			m_pcsbi = new CONSOLE_SCREEN_BUFFER_INFOEX();
			m_pcsbi->cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
		}

		if (!GetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), m_pcsbi)) {
			_tcerr << endl << _T("FATAL: Unable to get console screen buffer.") << endl
				<< __FILET__ << _T(" at function ") << __FUNCTIONT__ << _T(": line ")
				<< __LINE__ << endl;
			ExitProcess(EXIT_FATAL);
		}
	};

	_tostream & clr(_tostream & os) {
		os.flush();
		shell.Clear();
		return os;
	};

	_tostream & fg_red(_tostream & os) {
		os.flush();
		shell.SetColor(FOREGROUND_RED, FOREGROUND_MASK);
		return os;
	};

	_tostream & fg_green(_tostream & os) {
		os.flush();
		shell.SetColor(FOREGROUND_GREEN, FOREGROUND_MASK);
		return os;
	};

	_tostream & fg_ble(_tostream & os) {
		os.flush();
		shell.SetColor(FOREGROUND_BLUE, FOREGROUND_MASK);
		return os;
	};

	_tostream & fg_cyan(_tostream & os) {
		os.flush();
		shell.SetColor(FOREGROUND_CYAN, FOREGROUND_MASK);
		return os;
	};

	_tostream & fg_margenta(_tostream & os) {
		os.flush();
		shell.SetColor(FOREGROUND_MARGENTA, FOREGROUND_MASK);
		return os;
	};

	_tostream & fg_yellow(_tostream & os) {
		os.flush();
		shell.SetColor(FOREGROUND_YELLOW, FOREGROUND_MASK);
		return os;
	};

	_tostream & fg_black(_tostream & os) {
		os.flush();
		shell.SetColor(FOREGROUND_BLACK, FOREGROUND_MASK);
		return os;
	};

	_tostream & fg_gray(_tostream & os) {
		os.flush();
		shell.SetColor(FOREGROUND_GRAY, FOREGROUND_MASK);
		return os;
	};

	_tostream & fg_white(_tostream & os) {
		os.flush();
		shell.SetColor(FOREGROUND_WHITE, FOREGROUND_MASK);
		return os;
	};

	_tostream & fg_light_gray(_tostream & os) {
		os.flush();
		shell.SetColor(FOREGROUND_LIGHT_GRAY, FOREGROUND_MASK);
		return os;
	};

	_tostream & fg_light_red(_tostream & os) {
		os.flush();
		shell.SetColor(FOREGROUND_LIGHT_RED, FOREGROUND_MASK);
		return os;
	};

	_tostream & fg_light_green(_tostream & os) {
		os.flush();
		shell.SetColor(FOREGROUND_LIGHT_GREEN, FOREGROUND_MASK);
		return os;
	};

	_tostream & fg_light_blue(_tostream & os) {
		os.flush();
		shell.SetColor(FOREGROUND_LIGHT_BLUE, FOREGROUND_MASK);
		return os;
	};

	_tostream & fg_light_cyan(_tostream & os) {
		os.flush();
		shell.SetColor(FOREGROUND_LIGHT_CYAN, FOREGROUND_MASK);
		return os;
	};

	_tostream & fg_light_margenta(_tostream & os) {
		os.flush();
		shell.SetColor(FOREGROUND_LIGHT_MARGENTA, FOREGROUND_MASK);
		return os;
	};

	_tostream & fg_light_yellow(_tostream & os) {
		os.flush();
		shell.SetColor(FOREGROUND_LIGHT_YELLOW, FOREGROUND_MASK);
		return os;
	};

	_tostream & bg_red(_tostream & os) {
		os.flush();
		shell.SetColor(BACKGROUND_RED, BACKGROUND_MASK);
		return os;
	};

	_tostream & bg_green(_tostream & os) {
		os.flush();
		shell.SetColor(BACKGROUND_GREEN, BACKGROUND_MASK);
		return os;
	};

	_tostream & bg_ble(_tostream & os) {
		os.flush();
		shell.SetColor(BACKGROUND_BLUE, BACKGROUND_MASK);
		return os;
	};

	_tostream & bg_cyan(_tostream & os) {
		os.flush();
		shell.SetColor(BACKGROUND_CYAN, BACKGROUND_MASK);
		return os;
	};

	_tostream & bg_margenta(_tostream & os) {
		os.flush();
		shell.SetColor(BACKGROUND_MARGENTA, BACKGROUND_MASK);
		return os;
	};

	_tostream & bg_yellow(_tostream & os) {
		os.flush();
		shell.SetColor(BACKGROUND_YELLOW, BACKGROUND_MASK);
		return os;
	};

	_tostream & bg_black(_tostream & os) {
		os.flush();
		shell.SetColor(BACKGROUND_BLACK, BACKGROUND_MASK);
		return os;
	};

	_tostream & bg_gray(_tostream & os) {
		os.flush();
		shell.SetColor(BACKGROUND_GRAY, BACKGROUND_MASK);
		return os;
	};

	_tostream & bg_white(_tostream & os) {
		os.flush();
		shell.SetColor(BACKGROUND_WHITE, BACKGROUND_MASK);
		return os;
	};

	_tostream & bg_light_gray(_tostream & os) {
		os.flush();
		shell.SetColor(BACKGROUND_LIGHT_GRAY, BACKGROUND_MASK);
		return os;
	};

	_tostream & bg_light_red(_tostream & os) {
		os.flush();
		shell.SetColor(BACKGROUND_LIGHT_RED, BACKGROUND_MASK);
		return os;
	};

	_tostream & bg_light_green(_tostream & os) {
		os.flush();
		shell.SetColor(BACKGROUND_LIGHT_GREEN, BACKGROUND_MASK);
		return os;
	};

	_tostream & bg_light_blue(_tostream & os) {
		os.flush();
		shell.SetColor(BACKGROUND_LIGHT_BLUE, BACKGROUND_MASK);
		return os;
	};

	_tostream & bg_light_cyan(_tostream & os) {
		os.flush();
		shell.SetColor(BACKGROUND_LIGHT_CYAN, BACKGROUND_MASK);
		return os;
	};

	_tostream & bg_light_margenta(_tostream & os) {
		os.flush();
		shell.SetColor(BACKGROUND_LIGHT_MARGENTA, BACKGROUND_MASK);
		return os;
	};

	_tostream & bg_light_yellow(_tostream & os) {
		os.flush();
		shell.SetColor(BACKGROUND_LIGHT_YELLOW, BACKGROUND_MASK);
		return os;
	};	
}