#pragma once
#include "Stdafx.h"

namespace Unmanaged {

#define	EXIT_FAILURE	1
#define	ASSERT(expr)	if (!expr) PrintMessage(#expr, __FILE__, __LINE__, GetLastError())

	__forceinline void PrintMessage(LPCSTR lineDesc, LPCSTR fileName, int lineNo, DWORD errNum) {
		LPTSTR	lpBuffer;
		TCHAR	errBuff[256];

		DWORD	numRead;

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			errNum,
			LANG_NEUTRAL,
			(LPTSTR)&lpBuffer,
			0,
			NULL);

		StringCchPrintf(errBuff, 256, TEXT("[ERR: %d]: %s at line %d, %s\n\nReason: %s"), errNum, fileName, lineNo, lineDesc, lpBuffer);
		//wsprintf(errBuff, TEXT("[ERR: %d]: %s at line %d, %s\n\nReason: %s"), errNum, fileName, lineNo, lineDesc, lpBuffer);
		WriteFile(GetStdHandle(STD_ERROR_HANDLE), errBuff, _tcslen(errBuff), &numRead, FALSE);
		Sleep(5000);

		ExitProcess(EXIT_FAILURE);
	};

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