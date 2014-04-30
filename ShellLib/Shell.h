#pragma once

namespace shllib {

	using namespace std;
	using namespace ShellLib::Drawing;

	static class CShell
	{
	public:
		CShell();
		~CShell();

	public:
		void	Clear(void);
		void	SetColor(WORD wColor, WORD wMASK);
		BOOL	GetInfo(PCONSOLE_SCREEN_BUFFER_INFOEX pcsbi);
		BOOL	SetBufferSize(COORD newSize);
		BOOL	SetWindowLayout(CRectangle srNew);

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