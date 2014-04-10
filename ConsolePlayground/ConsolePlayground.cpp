// ConsolePlayground.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define		WIDTH		30
#define		HEIGHT		4

void WriteChar(CHAR_INFO info[], int x, int y, TCHAR *chs, int len) {
	int xpos = x;
	CHAR_INFO * ci;

	for (int i = 0; i < len; i++) {
		ci = &info[y * WIDTH + xpos];
		ci->Char.UnicodeChar = chs[i];
		ci->Attributes = FOREGROUND_GREEN | FOREGROUND_RED;
		xpos++;
	}

}

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE _stdin = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE _stdout = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hNewScreenBuffer = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL);
	if (_stdout == INVALID_HANDLE_VALUE || hNewScreenBuffer == INVALID_HANDLE_VALUE) {
		printf("Create console screen buffer failed - (%d)\n", GetLastError());
		Sleep(10000);
		return 1;
	}

	if (!SetConsoleActiveScreenBuffer(hNewScreenBuffer)) {
		printf("Set console screen buffer failed - (%d)\n", GetLastError());
		Sleep(10000);
		return 1;
	}

	SMALL_RECT srctReadRect;
	SMALL_RECT srctWriteRect;
	CHAR_INFO chiBuffer[WIDTH * HEIGHT]; // [4][30]; 
	COORD coordBufSize;
	COORD coordBufCoord;
	BOOL fSuccess;

	srctReadRect.Top = srctWriteRect.Top = 1;				//	top left: row 1, col 1
	srctReadRect.Left = srctWriteRect.Left = 1;
	srctReadRect.Right = srctWriteRect.Right = 30;				//	bot, right: row 4, col 30
	srctReadRect.Bottom = srctWriteRect.Bottom = 4;

	coordBufSize.Y = 4;
	coordBufSize.X = 30;

	coordBufCoord.X = coordBufCoord.Y = 0;

	if (!ReadConsoleOutput(
		_stdout,
		chiBuffer,
		coordBufSize,
		coordBufCoord,
		&srctReadRect)) {
		printf("Read console output failed - (%d)\n", GetLastError());
		Sleep(10000);
		return 1;
	}

	WriteChar(chiBuffer, 0, 0, TEXT("Mouse POS X: "), 13);
	WriteChar(chiBuffer, 0, 1, TEXT("Mouse POS Y: "), 13);
	if (!WriteConsoleOutput(_stdout, chiBuffer, coordBufSize, coordBufCoord, &srctWriteRect)) {
		printf("Write console input failed - (%d)\n", GetLastError());
		Sleep(10000);
		return 1;
	}

	BOOL stop = FALSE;
	INPUT_RECORD ir[120];
	DWORD read;

	while (!stop)
	{
		if (!ReadConsoleInput(_stdin, ir, 120, &read)) {
			printf("Read console input failed - (%d)\n", GetLastError());
			Sleep(10000);
			return 1;
		}
		
		for (DWORD i = 0; i < read; i++)
		{
			switch (ir[i].EventType)
			{
			case KEY_EVENT:
				if (ir[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
					stop = TRUE;
				}
				break;
			case MOUSE_EVENT:
				COORD pos = ir[i].Event.MouseEvent.dwMousePosition;
				TCHAR s[4];
				_itow_s(pos.X, s, 10);
				int count = _tcslen(s);
				WriteChar(chiBuffer, 13, 0, s, count);
				_itow_s(pos.Y, s, 10);
				count = _tcslen(s);
				WriteChar(chiBuffer, 13, 1, s, count);

				if (!WriteConsoleOutput(_stdout, chiBuffer, coordBufSize, coordBufCoord, &srctWriteRect)) {
					printf("Write console input failed - (%d)\n", GetLastError());
					Sleep(10000);
					return 1;
				}
			}
		}
	}

	return 0;
}

