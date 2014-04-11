#pragma once
#include "Stdafx.h"

namespace Unmanaged {

#define	EXIT_FAILURE	1
#define	ASSERT(expr)	if (!expr) PrintMessage(#expr, __FILE__, __LINE__, GetLastError())

	__inline void PrintMessage(LPCSTR lineDesc, LPCSTR fileName, int lineNo, DWORD errNum) {
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

		wsprintf(errBuff, TEXT("[ERR: %d]: %s at line %d, %s\n\nReason: %s"), errNum, fileName, lineNo, lineDesc, lpBuffer);
		WriteFile(GetStdHandle(STD_ERROR_HANDLE), errBuff, _tcslen(errBuff), &numRead, FALSE);
		Sleep(5000);

		ExitProcess(EXIT_FAILURE);
	};

}