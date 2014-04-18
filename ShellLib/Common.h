#pragma once
#include "Stdafx.h"

namespace ShellLib {

#define	EXIT_FAILURE	1

	__forceinline __declspec(noreturn) void PrintMessage(LPCSTR lineDesc, LPCSTR fileName, int lineNo, DWORD errNum) {
		LPTSTR	lpBuffer;
		TCHAR	errBuff[256];

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			errNum,
			LANG_NEUTRAL,
			(LPTSTR)&lpBuffer,
			0,
			NULL);

		StringCchPrintf(errBuff, 256, TEXT("[ERR: %d]: %s at line %d, %s\r\n\r\nReason: %s"), errNum, fileName, lineNo, lineDesc, lpBuffer);
		System::String ^ msg = gcnew System::String(errBuff);
		throw gcnew CAssertFailedException(msg, lineNo, %String(fileName), %String(lineDesc), (int)errNum, nullptr);
	};

#ifndef ASSERT
#define	ASSERT(expr)	do { if (!expr) PrintMessage(#expr, __FILE__, __LINE__, GetLastError()); } while (0)
#endif

	__forceinline DWORD	GetSysDateTime() {
		LPSYSTEMTIME lpSysTime = new SYSTEMTIME();
		GetSystemTime(lpSysTime);
		LPFILETIME lpFileTime = new FILETIME();
		ASSERT(SystemTimeToFileTime(lpSysTime, lpFileTime));

		delete lpSysTime;
		DWORD dwTime = lpFileTime->dwLowDateTime;
		delete lpFileTime;

		return dwTime;
	}

	typedef struct tagMESSAGE {
		HANDLE		hWkp;
		UINT		message;
		WPARAM		wParam;
		LPARAM		lParam;
		DWORD		time;
		COORD		pt;
	} MESSAGE, far LPMESSAGE;

	HANDLE	GetTopMostWorkplace(HANDLE hWkp);

	HANDLE	GetFocusWorkplace(HANDLE hWkp);

}