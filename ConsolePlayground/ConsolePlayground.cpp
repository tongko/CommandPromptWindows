// ConsolePlayground.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define		WIDTH		30
#define		HEIGHT		4

HANDLE		gOut;
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

void ErrorExit(LPTSTR lpszFunction)
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

int _tmain(int argc, _TCHAR* argv[])
{
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



	ReadKey(GetStdHandle(STD_INPUT_HANDLE));

	//TestMutex * tm = new TestMutex();

	//HANDLE aThread[2];
	//for (int i = 0; i < 2; i++)
	//{
	//	aThread[i] = CreateThread(
	//		NULL,       // default security attributes
	//		0,          // default stack size
	//		(LPTHREAD_START_ROUTINE)ThreadProc,
	//		(LPVOID)tm,       // no thread function arguments
	//		0,          // default creation flags
	//		0); // receive thread identifier
	//}

	//WaitForMultipleObjects(2, aThread, TRUE, INFINITE);

	//for (int i = 0; i < 2; i++)
	//{
	//	CloseHandle(aThread[i]);
	//}

	//delete tm;
	//ReadKey(GetStdHandle(STD_INPUT_HANDLE));

	//printf("Press enter after attached to debugger: ");
	//ReadKey(GetStdHandle(STD_INPUT_HANDLE));

	//HANDLE hNewScreenBuffer = CreateConsoleScreenBuffer(
	//	GENERIC_READ | GENERIC_WRITE,
	//	FILE_SHARE_READ | FILE_SHARE_WRITE,
	//	NULL,
	//	CONSOLE_TEXTMODE_BUFFER,
	//	NULL);
	//if (hNewScreenBuffer == INVALID_HANDLE_VALUE) {
	//	printf("Create console screen buffer failed - (%d)\n", GetLastError());
	//	Sleep(10000);
	//	return 1;
	//}

	//if (!SetConsoleActiveScreenBuffer(hNewScreenBuffer)) {
	//	printf("Set console screen buffer failed - (%d)\n", GetLastError());
	//	Sleep(10000);
	//	return 1;
	//}

	//PCONSOLE_SCREEN_BUFFER_INFOEX pcsbi = new CONSOLE_SCREEN_BUFFER_INFOEX();
	//pcsbi->cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	//if (!GetConsoleScreenBufferInfoEx(hNewScreenBuffer, pcsbi)) {
	//	printf("Get console screen buffer info ex failed - (%d)\n", GetLastError());
	//	Sleep(10000);
	//	return 1;
	//}
	//COORD size = pcsbi->dwSize;
	//int length = size.X * size.Y;

	////
	////	Set color table;
	////
	//COLORREF * colorTable = new COLORREF[16];
	//for (int i = 0; i < 16; i++)
	//{
	//	colorTable[i] = pcsbi->ColorTable[i];
	//}


	//COLORREF newColorTable[16] = {
	//	0,									//	BLACK
	//	RGB(0, 0, 128),						//	DACK BLUE
	//	RGB(0, 128, 0),						//	DACK GREEN
	//	RGB(0, 128, 128),					//	DACK CYAN
	//	RGB(128, 0, 0),						//	DARK RED
	//	RGB(128, 0, 128),					//	DARK MARGENTA
	//	RGB(128, 128, 0),					//	DARK YELLOW
	//	RGB(192, 192, 192),					//	LIGHT GRAY
	//	RGB(128, 128, 128),					//	DARK GRAY
	//	RGB(0, 0, 255),						//	BLUE
	//	RGB(0, 255, 0),						//	GREEN
	//	RGB(0, 255, 255),					//	CYAN
	//	RGB(255, 0, 0),						//	RED
	//	RGB(255, 0, 255),					//	MARGENTA
	//	RGB(255, 255, 0),					//	YELLOW
	//	RGB(255, 255, 255)					//	WHITE
	//};

	//for (int i = 0; i < 16; i++)
	//{
	//	pcsbi->ColorTable[i] = newColorTable[i];
	//}

	//SetConsoleScreenBufferInfoEx(hNewScreenBuffer, pcsbi);

	//DWORD written;
	//FillConsoleOutputCharacter(
	//	hNewScreenBuffer,
	//	TEXT(' '),
	//	length, pcsbi->dwCursorPosition, &written);
	////FillConsoleOutputAttribute(
	////	hNewScreenBuffer,
	////	BACKGROUND_GREEN,
	////	length, csbi.dwCursorPosition, &written);
	//FillConsoleOutputAttribute(
	//	hNewScreenBuffer,
	//	FOREGROUND_RED | FOREGROUND_INTENSITY,
	//	length, pcsbi->dwCursorPosition, &written);

	//HANDLE _stdin = GetStdHandle(STD_INPUT_HANDLE);

	//SMALL_RECT srctReadRect = { 1, 1, 30, 4 };
	//SMALL_RECT srctWriteRect = { 0, 0, 29, 3 };
	//CHAR_INFO chiBuffer[WIDTH * HEIGHT]; // [4][30]; 
	//COORD coordBufSize;
	//COORD coordBufCoord;
	//BOOL fSuccess;

	//coordBufSize.Y = 4;
	//coordBufSize.X = 30;

	//coordBufCoord.X = coordBufCoord.Y = 0;

	//if (!ReadConsoleOutput(
	//	hNewScreenBuffer,
	//	chiBuffer,
	//	coordBufSize,
	//	coordBufCoord,
	//	&srctReadRect)) {
	//	printf("Read console output failed - (%d)\n", GetLastError());
	//	Sleep(10000);
	//	return 1;
	//}

	//WriteChar(chiBuffer, 0, 0, TEXT("Mouse POS X: "), 13);
	//WriteChar(chiBuffer, 0, 1, TEXT("Mouse POS Y: "), 13);
	//if (!WriteConsoleOutput(hNewScreenBuffer, chiBuffer, coordBufSize, coordBufCoord, &srctWriteRect)) {
	//	printf("Write console input failed - (%d)\n", GetLastError());
	//	Sleep(10000);
	//	return 1;
	//}

	////	Allow mouse input.
	//DWORD flag;
	//GetConsoleMode(_stdin, &flag);
	//SetConsoleMode(_stdin, flag | ENABLE_MOUSE_INPUT);

	//BOOL stop = FALSE;
	//INPUT_RECORD ir[120];
	//DWORD read;

	//while (!stop)
	//{
	//	if (!ReadConsoleInput(_stdin, ir, 120, &read)) {
	//		printf("Read console input failed - (%d)\n", GetLastError());
	//		Sleep(10000);
	//		return 1;
	//	}
	//	
	//	for (DWORD i = 0; i < read; i++)
	//	{
	//		switch (ir[i].EventType)
	//		{
	//		case KEY_EVENT:
	//			if (ir[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
	//				stop = TRUE;
	//			}
	//			break;
	//		case MOUSE_EVENT:
	//			COORD pos = ir[i].Event.MouseEvent.dwMousePosition;
	//			TCHAR s[4];
	//			_itow_s(pos.X, s, 10);
	//			int count = _tcslen(s);
	//			WriteChar(chiBuffer, 13, 0, s, count);
	//			_itow_s(pos.Y, s, 10);
	//			count = _tcslen(s);
	//			WriteChar(chiBuffer, 13, 1, s, count);

	//			if (!WriteConsoleOutput(hNewScreenBuffer, chiBuffer, coordBufSize, coordBufCoord, &srctWriteRect)) {
	//				printf("Write console input failed - (%d)\n", GetLastError());
	//				Sleep(10000);
	//				return 1;
	//			}
	//		}
	//	}
	//}

	//CloseHandle(hNewScreenBuffer);

	//for (int i = 0; i < 16; i++)
	//{
	//	pcsbi->ColorTable[i] = colorTable[i];
	//}

	//delete[] colorTable;
	//_stdin = GetStdHandle(STD_OUTPUT_HANDLE);
	//if (!SetConsoleScreenBufferInfoEx(_stdin, pcsbi))
	//{
	//	printf("Restore console buffer info failed - (%d)\n", GetLastError());
	//	return 1;
	//}
	//if (!FillConsoleOutputAttribute(_stdin, pcsbi->wAttributes, length, pcsbi->dwCursorPosition, &written)) {
	//	printf("Restore console failed - (%d)\n", GetLastError());
	//	return 1;
	//}
	//delete pcsbi;

	//SetConsoleMode(_stdin, flag);

	return 0;
}

