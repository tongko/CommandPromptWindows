#pragma once
#include "Stdafx.h"
#include <iterator>

namespace ShellLib {

	using namespace std;
	using namespace stdext;

#define	EXIT_FAILURE	1

	__forceinline void _twrite(LPCTSTR lpszFormat, ...) {
		TCHAR	outTemp[MAX_STR_LENGTH];
		va_list	argPtr;
		
		va_start(argPtr, lpszFormat);
		HRESULT hr = StringCchPrintf(outTemp, MAX_STR_LENGTH, lpszFormat, argPtr);
		va_end(argPtr);
		
		if (FAILED(hr)) {
			if (hr == STRSAFE_E_INVALID_PARAMETER) {
				cerr << L"FATAL: common.h at line 20, _twrite(HANDLE, LPCTSTR, ...)\r\n\r\nReason: ";
				cerr << L"The value in cchDest is either 0 or larger than STRSAFE_MAX_CCH." << endl;
				ExitProcess(3);		// Unrecoverable.
			}
			else if (hr == STRSAFE_E_INSUFFICIENT_BUFFER) {
				cerr << L"WARNING: common.h at line 20, _twrite(HANDLE, LPCTSTR, ...)\r\n\r\nReason: ";
				cerr << L"Insufficient space in 'outTemp'. Truncated, null-terminated version of the intended result were written."
					<< endl;
			}
			else {
				cerr << L"FATAL: common.h at line 20, _twrite(HANDLE, LPCTSTR, ...)\r\n\r\nReason: ";
				cerr << L"Unknown error occurs. HRESULT is " << hr << endl;
				ExitProcess(3);
			}
		}

		cout << outTemp;
	};

	__forceinline __declspec(noreturn) void WriteErrorExit(LPCSTR lineDesc, LPCSTR fileName, int lineNo, DWORD errNum) {
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
#define	ASSERT(expr)	do { if (!expr) WriteErrorExit(#expr, __FILE__, __LINE__, GetLastError()); } while (0)
#endif

	__forceinline DWORD	GetSysDateTime() {
		LPSYSTEMTIME lpSysTime = new SYSTEMTIME();
		GetSystemTime(lpSysTime);
		LPFILETIME lpFileTime = new ::FILETIME();
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


	__forceinline BOOL	ShallowCopy(const LPVOID psource, LPVOID pdest) {
		LPBYTE ps = reinterpret_cast<LPBYTE>(psource);
		LPBYTE pd = reinterpret_cast<LPBYTE>(pdest);

		// Get psource byte count
		ULONG sourceCount = *reinterpret_cast<PULONG>(ps);
		//	Get pdest byte count
		ULONG destCount = *reinterpret_cast<PULONG>(pd);

		if (sourceCount != destCount) {
			SetLastError(ERROR_INVALID_PARAMETER);
			return FALSE;
		}

		std::copy(ps, ps + sourceCount, checked_array_iterator<LPBYTE>(pd, destCount));
	}

}
