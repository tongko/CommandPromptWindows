// ConsolePlayground.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iomanip>
#include <iterator>

using namespace std;
using namespace stdext;

#define		WIDTH		30
#define		HEIGHT		4
void ErrorExit(LPCTSTR lpszFunction);
void ReadAndHandleOutput(HANDLE hPipeRead);
void PrepAndLaunchRedirectedChild(HANDLE hChildStdOut,
	HANDLE hChildStdIn,
	HANDLE hChildStdErr);
DWORD WINAPI GetAndSendInputThread(LPVOID lpvThreadParam);

HANDLE		gOut;
HANDLE		hChildProcess;
HANDLE		hStdIn = NULL; // Handle to parents std input.
BOOL		bRunThread = TRUE;

//void WriteChar(CHAR_INFO info[], int x, int y, TCHAR *chs, int len) {
//	int xpos = x;
//	CHAR_INFO * ci;
//
//	for (int i = 0; i < len; i++) {
//		ci = &info[y * WIDTH + xpos];
//		ci->Char.UnicodeChar = chs[i];
//		ci->Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
//		xpos++;
//	}
//}
//
void ReadKey(HANDLE hInput)
{
	INPUT_RECORD ir[10];
	DWORD read;
	bool result = false;

	while (true)
	{
		ReadConsoleInput(hInput, ir, 10, &read);
		for (DWORD i = 0; i < read; i++)
		{
			static BOOL flag = FALSE;
			if (ir[i].EventType == KEY_EVENT)
			{
				if (ir[i].Event.KeyEvent.wVirtualKeyCode == VK_RETURN) {
					if (flag && !ir[i].Event.KeyEvent.bKeyDown)
						result = true;
					flag = ir[i].Event.KeyEvent.bKeyDown;
					break;
				}
			}
		}

		if (result) break;
	}
}

//void SwapArray(COLORREF array1[], COLORREF array2[])
//{
//	COLORREF * temp;
//	temp = array1;
//	array1 = array2;
//	array2 = temp;
//}


class MutexLock {
public:
	MutexLock(HANDLE hMutex) {
		m_hMutex = hMutex;
	}
	void	Lock() {
		WaitForSingleObject((m_hMutex), INFINITE);
	}

	~MutexLock() {
		if (m_hMutex != NULL) {
			ReleaseMutex(m_hMutex);
			std::cout << "Mutex released." << std::endl;
		}
	}

private:
	HANDLE	m_hMutex;
};

class TestMutex
{
public:
	TestMutex(void) {
		m_mutex = CreateMutex(NULL, FALSE, NULL);
		std::cout << "Mutex created." << std::endl;
	}
	~TestMutex(void) {
		if (m_mutex != NULL)
			CloseHandle(m_mutex);
	}

	void	Func1(void) {
		MutexLock ml(m_mutex);
		ml.Lock();

		std::cout << "Func1: Owning mutex." << std::endl;
		std::cout << "Press enter key to end this." << std::endl;
		ReadKey(GetStdHandle(STD_INPUT_HANDLE));
	}
	void	Func2(void) {
		MutexLock ml(m_mutex);
		ml.Lock();
		//std::cout << "Press enter key to start this." << std::endl;
		//ReadKey(GetStdHandle(STD_INPUT_HANDLE));

		std::cout << "Func2: Owning mutex." << std::endl;
		std::cout << "Press enter key to end this." << std::endl;
		ReadKey(GetStdHandle(STD_INPUT_HANDLE));
	}

private:
	HANDLE	m_mutex;
};

void ThreadProc(LPVOID data) {
	TestMutex * tm = (TestMutex *)data;
	static int g = 1;

	if (g++ == 1)
		tm->Func1();
	else
		tm->Func2();
}

void WriteToConsole(LPCTSTR msg) {
	size_t length = 0;
	HRESULT hr = StringCchLength(msg, MAX_PATH, &length);
	if (FAILED(hr)) {
		printf("\r\nFailed to get string length. HRESULT: %d\r\n", hr);
		exit(1);
	}

	DWORD charWritten = 0;
	WriteConsole(gOut, msg, length, &charWritten, NULL);
}

void ErrorExit(LPCTSTR lpszFunction)
{
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message and exit the process

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	WriteToConsole((LPCTSTR)lpDisplayBuf);


	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ReadKey(GetStdHandle(STD_INPUT_HANDLE));
	ExitProcess(dw);
}

void PrepareConsole(void) {
	gOut = GetStdHandle(STD_INPUT_HANDLE);

	HANDLE	hNew = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL);
	if (hNew == INVALID_HANDLE_VALUE) {
		ErrorExit(_T("_tmain"));
	}

	if (!SetConsoleActiveScreenBuffer(hNew)) {
		ErrorExit(_T("_tmain"));
	}

	gOut = hNew;

	PCONSOLE_SCREEN_BUFFER_INFOEX csbi = new CONSOLE_SCREEN_BUFFER_INFOEX();
	csbi->cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	if (!GetConsoleScreenBufferInfoEx(hNew, csbi)) {
		ErrorExit(_T("_tmain"));
	}

	csbi->dwSize.X = 198;
	csbi->dwSize.Y = 50;

	if (!SetConsoleScreenBufferInfoEx(hNew, csbi)) {
		ErrorExit(_T("_tmain"));
	}

	if (!GetConsoleScreenBufferInfoEx(hNew, csbi)) {
		ErrorExit(_T("_tmain"));
	}

	csbi->srWindow.Left = 0;
	csbi->srWindow.Bottom = 0;
	csbi->srWindow.Right = csbi->dwMaximumWindowSize.X - 1;
	csbi->srWindow.Bottom = csbi->dwMaximumWindowSize.Y - 1;

	if (!SetConsoleWindowInfo(hNew, TRUE, &csbi->srWindow))
		ErrorExit(_T("_tmain"));

	delete csbi;
}

BOOL	ShallowCopy(const LPVOID psource, LPVOID pdest) {
	LPBYTE ps = reinterpret_cast<LPBYTE>(psource);
	LPBYTE pd = reinterpret_cast<LPBYTE>(pdest);
	//LPBYTE pbCount = new BYTE[8];
	ULONG sourceCount;

	std::copy(ps, ps + 8, checked_array_iterator<LPBYTE>((LPBYTE)((LPVOID)&sourceCount), 8));	// Get psource byte count
	//sourceCount = *((PULONG)pbCount);
	ULONG destCount;
	std::copy(pd, pd + 8, checked_array_iterator<LPBYTE>((LPBYTE)((LPVOID)&destCount), 8));		//	Get pdest byte count
	//destCount = *((PULONG)pbCount);

	//delete[] pbCount;

	if (sourceCount != destCount) {
		SetLastError(ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	std::copy(ps, ps + sourceCount, checked_array_iterator<unsigned char *>(pd, destCount));
	return TRUE;
}

int _tmain(int argc, _TCHAR* argv[])
{
	system("cls");
	PCONSOLE_SCREEN_BUFFER_INFOEX pcsbi = new CONSOLE_SCREEN_BUFFER_INFOEX();
	pcsbi->cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), pcsbi);

	CONSOLE_SCREEN_BUFFER_INFOEX csbi;
	csbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	ShallowCopy(pcsbi, &csbi);

	wcout.fill(L' ');
	wcout << left;

	wcout.width(21);
	wcout << L' ' << setw(50) << L"Source" << L"Destination" << endl;
	wcout << setw(21) << L"cbSize:" << setw(50) << pcsbi->cbSize << csbi.cbSize << endl;
	wcout << setw(21) << L"dwSize:" << setw(5) << L"X: " << setw(5) << pcsbi->dwSize.X << setw(5) << L", Y: " << setw(35) << pcsbi->dwSize.Y
		<< setw(5) << L"X: " << setw(5) << csbi.dwSize.X << setw(5) << L", Y: " << csbi.dwSize.Y << endl;
	wcout << setw(21) << L"dwCursorPos:" << setw(5) << L"X: " << setw(5) << pcsbi->dwCursorPosition.X << setw(5) << L", Y: " << setw(35) << pcsbi->dwCursorPosition.Y
		<< setw(5) << setw(5) << L"X: " << setw(5) << csbi.dwCursorPosition.X << setw(5) << L", Y: " << csbi.dwCursorPosition.Y << endl;
	wcout << setw(21) << L"wAttributes:" << setw(50) << pcsbi->wAttributes << csbi.wAttributes << endl;
	wcout << setw(21) << L"srWindow:" << setw(5) << L"L:" << setw(5) << pcsbi->srWindow.Left << setw(5) << L", T:" << setw(5) << pcsbi->srWindow.Top
		<< setw(5) << L", R:" << setw(5) << pcsbi->srWindow.Right << setw(5) << L", B:" << setw(15) << pcsbi->srWindow.Bottom;
	wcout << setw(5) << L"L:" << setw(5) << csbi.srWindow.Left << setw(5) << L", T:" << setw(5) << csbi.srWindow.Top
		<< setw(5) << L", R:" << setw(5) << csbi.srWindow.Right << setw(5) << L", B:" << setw(15) << csbi.srWindow.Bottom << endl;

	wcout << setw(21) << L"dwMaximumWindowSize:" << setw(5) << L"X: " << setw(5) << pcsbi->dwMaximumWindowSize.X << setw(5) << L", Y: " 
		<< setw(35) << pcsbi->dwMaximumWindowSize.Y << setw(5) << L"X: " << setw(5) << csbi.dwMaximumWindowSize.X << setw(5) << L", Y: "
		<< csbi.dwMaximumWindowSize.Y << endl;

	wcout << setw(21) << L"wPopupAttributes:" << setw(50) << pcsbi->wPopupAttributes << csbi.wPopupAttributes << endl;
	wcout << setw(21) << L"bFullscreen:" << setw(50) << pcsbi->bFullscreenSupported << csbi.bFullscreenSupported << endl;

	system("PAUSE");
	//PrepareConsole();

	//HANDLE hOutputReadTmp, hOutputRead, hOutputWrite;
	//HANDLE hInputWriteTmp, hInputRead, hInputWrite;
	//HANDLE hErrorWrite;
	//HANDLE hThread;
	//DWORD ThreadId;
	//SECURITY_ATTRIBUTES sa;

	//// Set up the security attributes struct.
	//sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	//sa.lpSecurityDescriptor = NULL;
	//sa.bInheritHandle = TRUE;

	//// Create the child output pipe.
	//if (!CreatePipe(&hOutputReadTmp, &hOutputWrite, &sa, 0))
	//	ErrorExit(L"CreatePipe");

	//// Create a duplicate of the output write handle for the std error
	//// write handle. This is necessary in case the child application
	//// closes one of its std output handles.
	//if (!DuplicateHandle(GetCurrentProcess(), hOutputWrite,
	//	GetCurrentProcess(), &hErrorWrite, 0,
	//	TRUE, DUPLICATE_SAME_ACCESS))
	//	ErrorExit(L"DuplicateHandle");

	//// Create the child input pipe.
	//if (!CreatePipe(&hInputRead, &hInputWriteTmp, &sa, 0))
	//	ErrorExit(L"CreatePipe");

	//// Create new output read handle and the input write handles. Set
	//// the Properties to FALSE. Otherwise, the child inherits the
	//// properties and, as a result, non-closeable handles to the pipes
	//// are created.
	//if (!DuplicateHandle(GetCurrentProcess(), hOutputReadTmp,
	//	GetCurrentProcess(),
	//	&hOutputRead, // Address of new handle.
	//	0, FALSE, // Make it uninheritable.
	//	DUPLICATE_SAME_ACCESS))
	//	ErrorExit(L"DupliateHandle");

	//if (!DuplicateHandle(GetCurrentProcess(), hInputWriteTmp,
	//	GetCurrentProcess(),
	//	&hInputWrite, // Address of new handle.
	//	0, FALSE, // Make it uninheritable.
	//	DUPLICATE_SAME_ACCESS))
	//	ErrorExit(L"DupliateHandle");

	//// Close inheritable copies of the handles you do not want to be
	//// inherited.
	//if (!CloseHandle(hOutputReadTmp)) ErrorExit(L"CloseHandle");
	//if (!CloseHandle(hInputWriteTmp)) ErrorExit(L"CloseHandle");

	//// Get std input handle so you can close it and force the ReadFile to
	//// fail when you want the input thread to exit.
	//if ((hStdIn = GetStdHandle(STD_INPUT_HANDLE)) ==
	//	INVALID_HANDLE_VALUE)
	//	ErrorExit(L"GetStdHandle");

	//PrepAndLaunchRedirectedChild(hOutputWrite, hInputRead, hErrorWrite);

	//// Close pipe handles (do not continue to modify the parent).
	//// You need to make sure that no handles to the write end of the
	//// output pipe are maintained in this process or else the pipe will
	//// not close when the child process exits and the ReadFile will hang.
	//if (!CloseHandle(hOutputWrite)) ErrorExit(L"CloseHandle");
	//if (!CloseHandle(hInputRead)) ErrorExit(L"CloseHandle");
	//if (!CloseHandle(hErrorWrite)) ErrorExit(L"CloseHandle");

	//// Launch the thread that gets the input and sends it to the child.
	//hThread = CreateThread(NULL, 0, GetAndSendInputThread,
	//	(LPVOID)hInputWrite, 0, &ThreadId);
	//if (hThread == NULL) ErrorExit(L"CreateThread");

	//// Read the child's output.
	//ReadAndHandleOutput(hOutputRead);
	//// Redirection is complete

	//// Force the read on the input to return by closing the stdin handle.
	//if (!CloseHandle(hStdIn)) ErrorExit(L"CloseHandle");

	//// Tell the thread to exit and wait for thread to die.
	//bRunThread = FALSE;

	//if (WaitForSingleObject(hThread, INFINITE) == WAIT_FAILED)
	//	ErrorExit(L"WaitForSingleObject");

	//if (!CloseHandle(hOutputRead)) ErrorExit(L"CloseHandle");
	//if (!CloseHandle(hInputWrite)) ErrorExit(L"CloseHandle");
	//ReadKey(GetStdHandle(STD_INPUT_HANDLE));

	//if (gOut != NULL)
	//	CloseHandle(gOut);

	return 0;
}



/////////////////////////////////////////////////////////////////////// 
// ReadAndHandleOutput
// Monitors handle for input. Exits when child exits or pipe breaks.
/////////////////////////////////////////////////////////////////////// 
void ReadAndHandleOutput(HANDLE hPipeRead)
{
	TCHAR lpBuffer[256];
	DWORD nBytesRead;
	DWORD nCharsWritten;

	while (TRUE)
	{
		if (!ReadFile(hPipeRead, lpBuffer, sizeof(lpBuffer),
			&nBytesRead, NULL) || !nBytesRead)
		{
			if (GetLastError() == ERROR_BROKEN_PIPE)
				break; // pipe done - normal exit path.
			else
				ErrorExit(L"ReadFile"); // Something bad happened.
		}

		// Display the character read on the screen.
		if (!WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), lpBuffer,
			nBytesRead, &nCharsWritten, NULL))
			ErrorExit(L"WriteConsole");
	}
}

/////////////////////////////////////////////////////////////////////// 
// GetAndSendInputThread
// Thread procedure that monitors the console for input and sends input
// to the child process through the input pipe.
// This thread ends when the child application exits.
/////////////////////////////////////////////////////////////////////// 
DWORD WINAPI GetAndSendInputThread(LPVOID lpvThreadParam)
{
	CHAR read_buff[256];
	DWORD nBytesRead, nBytesWrote;
	HANDLE hPipeWrite = (HANDLE)lpvThreadParam;

	// Get input from our console and send it to child through the pipe.
	while (bRunThread)
	{
		if (!ReadConsole(hStdIn, read_buff, 1, &nBytesRead, NULL))
			ErrorExit(L"ReadConsole");

		read_buff[nBytesRead] = '\0'; // Follow input with a NULL.

		if (!WriteFile(hPipeWrite, read_buff, nBytesRead, &nBytesWrote, NULL))
		{
			if (GetLastError() == ERROR_NO_DATA)
				break; // Pipe was closed (normal exit path).
			else
				ErrorExit(L"WriteFile");
		}
	}

	return 1;
}

/////////////////////////////////////////////////////////////////////// 
// PrepAndLaunchRedirectedChild
// Sets up STARTUPINFO structure, and launches redirected child.
/////////////////////////////////////////////////////////////////////// 
void PrepAndLaunchRedirectedChild(HANDLE hChildStdOut,
	HANDLE hChildStdIn,
	HANDLE hChildStdErr)
{
	PROCESS_INFORMATION pi;
	STARTUPINFO si;

	// Set up the start up info struct.
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	si.hStdOutput = hChildStdOut;
	si.hStdInput = hChildStdIn;
	si.hStdError = hChildStdErr;
	// Use this if you want to hide the child:
	si.wShowWindow = SW_HIDE;
	// Note that dwFlags must include STARTF_USESHOWWINDOW if you want to
	// use the wShowWindow flags.

	// Launch the process that you want to redirect (in this case,
	// Child.exe). Make sure Child.exe is in the same directory as
	// redirect.c launch redirect from a command line to prevent location
	// confusion.
	TCHAR lpszPath[MAX_PATH] = L"ChildProcess.exe";
	if (!CreateProcess(NULL, lpszPath, NULL, NULL, TRUE,
		NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT, NULL, NULL, &si, &pi))
		ErrorExit(L"CreateProcess");

	// Set global child process handle to cause threads to exit.
	hChildProcess = pi.hProcess;

	// Close any unnecessary handles.
	if (!CloseHandle(pi.hThread)) ErrorExit(L"CloseHandle");
}
