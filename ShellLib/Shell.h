#pragma once

namespace shllib {

	using namespace std;

	static const WORD FILL_MASK(0x00);
	static const WORD BACKGROUND_MASK(0xF0);
	static const WORD FOREGROUND_MASK(0x0F);

	static const WORD FOREGROUND_BLACK(0);
	static const WORD FOREGROUND_CYAN(FOREGROUND_GREEN | FOREGROUND_BLUE);
	static const WORD FOREGROUND_MARGENTA(FOREGROUND_RED | FOREGROUND_BLUE);
	static const WORD FOREGROUND_YELLOW(FOREGROUND_RED | FOREGROUND_GREEN);
	static const WORD FOREGROUND_LIGHT_GRAY(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	static const WORD FOREGROUND_GRAY(FOREGROUND_BLACK | FOREGROUND_INTENSITY);
	static const WORD FOREGROUND_WHITE(FOREGROUND_LIGHT_GRAY | FOREGROUND_INTENSITY);
	static const WORD FOREGROUND_LIGHT_BLUE(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	static const WORD FOREGROUND_LIGHT_GREEN(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	static const WORD FOREGROUND_LIGHT_RED(FOREGROUND_RED | FOREGROUND_INTENSITY);
	static const WORD FOREGROUND_LIGHT_CYAN(FOREGROUND_CYAN | FOREGROUND_INTENSITY);
	static const WORD FOREGROUND_LIGHT_MARGENTA(FOREGROUND_MARGENTA | FOREGROUND_INTENSITY);
	static const WORD FOREGROUND_LIGHT_YELLOW(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
	static const WORD BACKGROUND_BLACK(0);
	static const WORD BACKGROUND_CYAN(BACKGROUND_GREEN | BACKGROUND_BLUE);
	static const WORD BACKGROUND_MARGENTA(BACKGROUND_RED | BACKGROUND_BLUE);
	static const WORD BACKGROUND_YELLOW(BACKGROUND_RED | BACKGROUND_GREEN);
	static const WORD BACKGROUND_LIGHT_GRAY(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	static const WORD BACKGROUND_GRAY(BACKGROUND_BLACK | BACKGROUND_INTENSITY);
	static const WORD BACKGROUND_WHITE(BACKGROUND_LIGHT_GRAY | BACKGROUND_INTENSITY);
	static const WORD BACKGROUND_LIGHT_BLUE(BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	static const WORD BACKGROUND_LIGHT_GREEN(BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	static const WORD BACKGROUND_LIGHT_RED(BACKGROUND_RED | BACKGROUND_INTENSITY);
	static const WORD BACKGROUND_LIGHT_CYAN(BACKGROUND_CYAN | BACKGROUND_INTENSITY);
	static const WORD BACKGROUND_LIGHT_MARGENTA(BACKGROUND_MARGENTA | BACKGROUND_INTENSITY);
	static const WORD BACKGROUND_LIGHT_YELLOW(BACKGROUND_YELLOW | BACKGROUND_INTENSITY);

	static class CShell
	{
	public:
		CShell();
		~CShell();

	public:
		void	Clear(void);
		void	SetColor(WORD wColor, WORD wMASK);
		void	GetInfo(PCONSOLE_SCREEN_BUFFER_INFOEX pcsbi);

	private:
		void	GetInfo(void);

	private:
		HANDLE							m_hMutex;
		DWORD							m_dwCharsWritten;
		PCONSOLE_SCREEN_BUFFER_INFOEX	m_pcsbi;
		COORD							m_dwSize;
	} shell;

	__forceinline _tostream & clr(_tostream & os);

	__forceinline _tostream & fg_red(_tostream & os);

	__forceinline _tostream & fg_green(_tostream & os);

	__forceinline _tostream & fg_ble(_tostream & os);

	__forceinline _tostream & fg_cyan(_tostream & os);

	__forceinline _tostream & fg_margenta(_tostream & os);

	__forceinline _tostream & fg_yellow(_tostream & os);

	__forceinline _tostream & fg_black(_tostream & os);

	__forceinline _tostream & fg_gray(_tostream & os);

	__forceinline _tostream & fg_white(_tostream & os);

	__forceinline _tostream & fg_light_gray(_tostream & os);

	__forceinline _tostream & fg_light_red(_tostream & os);

	__forceinline _tostream & fg_light_green(_tostream & os);

	__forceinline _tostream & fg_light_blue(_tostream & os);

	__forceinline _tostream & fg_light_cyan(_tostream & os);

	__forceinline _tostream & fg_light_margenta(_tostream & os);

	__forceinline _tostream & fg_light_yellow(_tostream & os);

	__forceinline _tostream & bg_red(_tostream & os);

	__forceinline _tostream & bg_green(_tostream & os);

	__forceinline _tostream & bg_ble(_tostream & os);

	__forceinline _tostream & bg_cyan(_tostream & os);

	__forceinline _tostream & bg_margenta(_tostream & os);

	__forceinline _tostream & bg_yellow(_tostream & os);

	__forceinline _tostream & bg_black(_tostream & os);

	__forceinline _tostream & bg_gray(_tostream & os);

	__forceinline _tostream & bg_white(_tostream & os);

	__forceinline _tostream & bg_light_gray(_tostream & os);

	__forceinline _tostream & bg_light_red(_tostream & os);

	__forceinline _tostream & bg_light_green(_tostream & os);

	__forceinline _tostream & bg_light_blue(_tostream & os);

	__forceinline _tostream & bg_light_cyan(_tostream & os);

	__forceinline _tostream & bg_light_margenta(_tostream & os);

	__forceinline _tostream & bg_light_yellow(_tostream & os);
}