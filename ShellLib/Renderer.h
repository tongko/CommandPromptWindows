#pragma once

namespace ShellLib { namespace Drawing {

	using namespace System;
	using namespace System::Runtime::InteropServices;

	private ref class CRenderer {
	public:
		CRenderer(HANDLE hOut);
		~CRenderer(void);

	public:
		//void		Render(void);
		//void		InvalidateRect(const SMALL_RECT & srRegion);
		//void		Invalidate(void);
		//void		ValidateRect(const SMALL_RECT & srRegion);
		//void		Clear(void);
		void		SetConsoleInfo(PCONSOLE_SCREEN_BUFFER_INFOEX pcsbi);

	private:
		PCONSOLE_SCREEN_BUFFER_INFOEX	m_pcsbi;
		HANDLE		m_hOut;
	};

}}