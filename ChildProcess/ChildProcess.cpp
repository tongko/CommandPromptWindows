// ChildProcess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void OutputString(HANDLE hOutput, COORD position, LPCTSTR lpszString) {
	size_t length = 0;
	StringCchLength(lpszString, MAX_PATH, &length);
	CHAR_INFO * ci = new CHAR_INFO[length];
	for (size_t i = 0; i < length; i++)
	{
		ci[i].Char.UnicodeChar = lpszString[i];
		ci[i].Attributes = FOREGROUND_RED | BACKGROUND_BLUE;
	}
	COORD dimension = { length, 1 };
	COORD start = { 0, 0 };
	SMALL_RECT location = { position.X, position.Y, position.X + length, position.Y };
	WriteConsoleOutput(hOutput, ci, dimension, start, &location);
}

int _tmain(int argc, _TCHAR* argv[])
{
	FILE*    fp;
	CHAR     szInput[1024];

	// Open the console. By doing this, you can send output directly to
	// the console that will not be redirected.

	fp = fopen("CON", "w");
	if (!fp) {
		printf("Error opening child console - perhaps there is none.\n");
		fflush(NULL);
	}
	else
	{

		// Write a message direct to the console (will not be redirected).

		fprintf(fp, "This data is being printed directly to the\n");
		fprintf(fp, "console and will not be redirected.\n\n");
		fprintf(fp, "Since the standard input and output have been\n");
		fprintf(fp, "redirected data sent to and from those handles\n");
		fprintf(fp, "will be redirected.\n\n");
		fprintf(fp, "To send data to the std input of this process.\n");
		fprintf(fp, "Click on the console window of the parent process\n");
		fprintf(fp, "(redirect), and enter data from it's console\n\n");
		fprintf(fp, "To exit this process send the string 'exit' to\n");
		fprintf(fp, "it's standard input\n");
		fflush(fp);
	}

	LPTSTR chrs[10] = { L"This data is being printed directly to the",
		L"console and will not be redirected.",
		L"Since the standard input and output have been",
		L"redirected data sent to and from those handles",
		L"will be redirected.",
		L"To send data to the std input of this process.",
		L"Click on the console window of the parent process",
		L"(redirect), and enter data from it's console",
		L"To exit this process send the string 'exit' to",
		L"it's standard input"};
	HANDLE _stdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int i = 0;

	while (i < 10)
	{
		COORD pos = { 0, i };
		OutputString(_stdout, pos, chrs[i++]);
	}

	char c[1];
	ZeroMemory(c, 1);
	gets_s(c, 1);

	return 0;
}

