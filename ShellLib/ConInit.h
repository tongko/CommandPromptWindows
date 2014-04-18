#pragma once

namespace ShellLib {

	using namespace Configs;

	private class CConInit
	{
	public:
		CConInit();
		~CConInit();

	public:
		void			Initialize(CWorkspaceConfigSection ^ configSection);
		void			ResetScreenBufferInfo(void);
		PCONSOLE_SCREEN_BUFFER_INFOEX	GetScreenBufferInfo(void) const;

	private:
		void			ResetScreenBufferInfoInternal(void);
		static HANDLE	CreateScreenBuffer(void);

	public:
		const LPCTSTR	CONINIT_MUTEX = TEXT("CONINITSYNCOBJ");
		HANDLE			StdOut;
		HANDLE			StdIn;
		HANDLE			StdErr;

	private:
		PCONSOLE_SCREEN_BUFFER_INFOEX m_pcsbi;
		HANDLE			m_hSync;
	};

}