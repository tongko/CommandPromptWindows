/**********************************************************************
*
*	CStackTrace.h
*
*
*	History:
*	2014-05-02			-	First draft.
*
**********************************************************************/
#pragma once

namespace conlib {

	class CStackTraceInternal;		//	Forward declaration
	class CStackTrace
	{
	public:		//	Constructors
		CStackTrace(
			StackTraceOptions	options = OptionsAll,
			LPCTSTR				szSymPath = NULL,
			DWORD				dwProcessId = GetCurrentProcessId(),
			HANDLE				hProcess = GetCurrentProcess()
			);

		CStackTrace(
			DWORD				dwProcessId,
			HANDLE				hProcess
			);

		virtual ~CStackTrace();

	public:			//	Operations
		typedef BOOL (WINAPI *PReadProcessMemoryRoutine)(
			HANDLE				hProcess,
			DWORD64				qwBaseAddress,
			PVOID				lpBuffer,
			DWORD				nSize,
			LPDWORD				lpNumberOfBytesRead,
			LPVOID				pUserData  // optional data, which was passed in "ShowCallstack"
			);

		BOOL LoadModules();

		BOOL ShowCallstack(
			HANDLE				hThread = GetCurrentThread(),
			const CONTEXT *		context = NULL,
			PReadProcessMemoryRoutine readMemoryFunction = NULL,
			LPVOID				pUserData = NULL  // optional to identify some data in the 'readMemoryFunction'-callback
			);

	protected:
		virtual void			OnSymInit(LPCTSTR szSearchPath, DWORD symOptions, LPCTSTR szUserName);
		virtual void			OnLoadModule(LPCTSTR img, LPCTSTR mod, DWORD64 baseAddr, DWORD size, DWORD result, LPCTSTR symType, LPCTSTR pdbName, ULONGLONG fileVersion);
		virtual void			OnCallstackEntry(CallstackEntryType eType, CallstackEntry &entry);
		virtual void			OnDbgHelpErr(LPCTSTR szFuncName, DWORD gle, DWORD64 addr);
		virtual void			OnOutput(LPCTSTR szText);

		CStackTraceInternal *	m_sw;
		HANDLE					m_hProcess;
		DWORD					m_dwProcessId;
		BOOL					m_modulesLoaded;
		LPTSTR					m_szSymPath;

		StackTraceOptions		m_options;

		static BOOL __stdcall	ReadProcMem(HANDLE hProcess, DWORD64 qwBaseAddress, PVOID lpBuffer, DWORD nSize, LPDWORD lpNumberOfBytesRead);

		friend					CStackTraceInternal;
	};

}