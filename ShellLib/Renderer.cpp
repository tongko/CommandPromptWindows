#include "stdafx.h"
#include "Renderer.h"

namespace ShellLib { namespace Drawing {

	CRenderer::CRenderer(HANDLE hOut) {
		if (hOut == INVALID_HANDLE_VALUE)
			throw gcnew InvalidOperationException("Attemp to create renderer on corrupted target.");
		
		PCONSOLE_SCREEN_BUFFER_INFOEX pcsbi = new CONSOLE_SCREEN_BUFFER_INFOEX();
		pcsbi->cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
		if (!GetConsoleScreenBufferInfoEx(hOut, pcsbi)) {
			int hr = Marshal::GetHRForLastWin32Error();
			Marshal::ThrowExceptionForHR(hr);
		}
				
		SetConsoleInfo(pcsbi);
	}

	CRenderer::~CRenderer(void) {
		if (m_pcsbi != NULL)
			delete m_pcsbi;
	}

	void CRenderer::SetConsoleInfo(PCONSOLE_SCREEN_BUFFER_INFOEX pcsbi) {
		if (m_pcsbi == NULL) m_pcsbi = new CONSOLE_SCREEN_BUFFER_INFOEX();

		m_pcsbi->bFullscreenSupported = pcsbi->bFullscreenSupported;
		m_pcsbi->cbSize = pcsbi->cbSize;
		for (int i = 0; i < 16; i++)
			m_pcsbi->ColorTable[i] = pcsbi->ColorTable[i];
		m_pcsbi->dwCursorPosition = pcsbi->dwCursorPosition;
		m_pcsbi->dwMaximumWindowSize = pcsbi->dwMaximumWindowSize;
		m_pcsbi->dwSize = pcsbi->dwSize;
		m_pcsbi->srWindow = pcsbi->srWindow;
		m_pcsbi->wAttributes = pcsbi->wAttributes;
		m_pcsbi->wPopupAttributes = pcsbi->wPopupAttributes;

		//	Repaint Workspace.
		//Render();
	}
}}