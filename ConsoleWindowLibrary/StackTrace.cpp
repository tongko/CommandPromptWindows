#include	"stdafx.h"
#include	"DataTypes.h"
#include	"StackTrace.h"

namespace conlib {

#include	<iomanip>
#include	<iterator>
#include	<malloc.h>

#ifdef		_DEBUG
#define		_CRTDBG_MAP_ALLOC
#ifdef		UNICODE
#define		DBGHELP_TRANSLATE_TCHAR
#endif //	UNICODE
#include	<dbghelp.h>
#undef		_CRTDBG_MAP_ALLOC
#endif //	_DEBUG

#ifdef		UNICODE
#define		_tcsdup		_wcsdup
#else
#define		_tcsdup		_strdup
#endif //	UNICODE

#define		USED_CONTEXT_FLAGS	CONTEXT_FULL

	using	namespace stdext;

#pragma	region	CStackTraceInternal Implementation

	class CStackTraceInternal {
	public:
		CStackTraceInternal(CStackTrace *parent, HANDLE hProcess) {
			m_parent = parent;
			m_hDbhHelp = NULL;
			pSC = NULL;
			m_hProcess = hProcess;
			m_szSymPath = NULL;
			pSFTA = NULL;
			pSGLFA = NULL;
			pSGMB = NULL;
			pSGMI = NULL;
			pSGO = NULL;
			pSGSFA = NULL;
			pSI = NULL;
			pSLM = NULL;
			pSSO = NULL;
			pSW = NULL;
			pUDSN = NULL;
			pSGSP = NULL;
		};

		virtual ~CStackTraceInternal() {
			if (pSC != NULL)
				pSC(m_hProcess);  // SymCleanup
			if (m_hDbhHelp != NULL)
				FreeLibrary(m_hDbhHelp);
			m_hDbhHelp = NULL;
			m_parent = NULL;
			if (m_szSymPath != NULL)
				free(m_szSymPath);
			m_szSymPath = NULL;
		};

	public:		//	Operations
		BOOL Init(LPCTSTR szSymPath)
		{
			if (m_parent == NULL)
				return FALSE;

			// Dynamically load the Entry-Points for dbghelp.dll:
			// First try to load the newsest one from

			//TCHAR szTemp[4096];
			//// But before we do this, we first check if the ".local" file exists
			//if (GetModuleFileName(NULL, szTemp, 4096) > 0) {
			//	_tcscat_s(szTemp, _T(".local"));
			//	if (GetFileAttributes(szTemp) == INVALID_FILE_ATTRIBUTES) {
			//		// ".local" file does not exist, so we can try to load the dbghelp.dll from the "Debugging Tools for Windows"
			//		if (GetEnvironmentVariable(_T("ProgramFiles"), szTemp, 4096) > 0) {
			//			_tcscat_s(szTemp, _T("\\Debugging Tools for Windows\\dbghelp.dll"));

			//			// now check if the file exists:
			//			if (GetFileAttributes(szTemp) != INVALID_FILE_ATTRIBUTES)
			//				m_hDbhHelp = LoadLibrary(szTemp);
			//		}

			//		// Still not found? Then try to load the 64-Bit version:
			//		if ((m_hDbhHelp == NULL) && (GetEnvironmentVariable(_T("ProgramFiles"), szTemp, 4096) > 0)) {
			//			_tcscat_s(szTemp, _T("\\Debugging Tools for Windows 64-Bit\\dbghelp.dll"));

			//			if (GetFileAttributes(szTemp) != INVALID_FILE_ATTRIBUTES)
			//				m_hDbhHelp = LoadLibrary(szTemp);
			//		}
			//	}
			//}

			//if (m_hDbhHelp == NULL)  // if not already loaded, try to load a default-one
			//	m_hDbhHelp = LoadLibrary(_T("dbghelp.dll"));
			//if (m_hDbhHelp == NULL)
			//	return FALSE;

			//pSI = (tSI)GetProcAddress(m_hDbhHelp, "SymInitialize");
			//pSC = (tSC)GetProcAddress(m_hDbhHelp, "SymCleanup");
			//pSW = (tSW)GetProcAddress(m_hDbhHelp, "StackWalk64");
			//pSGO = (tSGO)GetProcAddress(m_hDbhHelp, "SymGetOptions");
			//pSSO = (tSSO)GetProcAddress(m_hDbhHelp, "SymSetOptions");
			//pSFTA = (tSFTA)GetProcAddress(m_hDbhHelp, "SymFunctionTableAccess64");
			//pSGLFA = (tSGLFA)GetProcAddress(m_hDbhHelp, "SymGetLineFromAddr64");
			//pSGMB = (tSGMB)GetProcAddress(m_hDbhHelp, "SymGetModuleBase64");
			//pSGMI = (tSGMI)GetProcAddress(m_hDbhHelp, "SymGetModuleInfo64");
			////pSGMI_V3 = (tSGMI_V3) GetProcAddress(m_hDbhHelp, "SymGetModuleInfo64" );
			//pSGSFA = (tSGSFA)GetProcAddress(m_hDbhHelp, "SymGetSymFromAddr64");
			//pUDSN = (tUDSN)GetProcAddress(m_hDbhHelp, "UnDecorateSymbolName");
			//pSLM = (tSLM)GetProcAddress(m_hDbhHelp, "SymLoadModule64");
			//pSGSP = (tSGSP)GetProcAddress(m_hDbhHelp, "SymGetSearchPath");

			//if (pSC == NULL || pSFTA == NULL || pSGMB == NULL || pSGMI == NULL ||
			//	pSGO == NULL || pSGSFA == NULL || pSI == NULL || pSSO == NULL ||
			//	pSW == NULL || pUDSN == NULL || pSLM == NULL)
			//{
			//	FreeLibrary(m_hDbhHelp);
			//	m_hDbhHelp = NULL;
			//	pSC = NULL;
			//	return FALSE;
			//}

			// SymInitialize
			if (szSymPath != NULL)
				m_szSymPath = _tcsdup(szSymPath);

			if (SymInitializeW(m_hProcess, m_szSymPath, FALSE) == FALSE)
				this->m_parent->OnDbgHelpErr(_T("SymInitialize"), GetLastError(), 0);

			DWORD symOptions = SymGetOptions();
			symOptions |= SYMOPT_LOAD_LINES;
			symOptions |= SYMOPT_FAIL_CRITICAL_ERRORS;
			//symOptions |= SYMOPT_NO_PROMPTS;
			// SymSetOptions
			symOptions = SymSetOptions(symOptions);

			TCHAR * buf = new TCHAR[STACKWALK_MAX_NAMELEN];
			if (SymGetSearchPathW(m_hProcess, buf, STACKWALK_MAX_NAMELEN) == FALSE)
				m_parent->OnDbgHelpErr(_T("SymGetSearchPath"), GetLastError(), 0);
			delete[] buf;

			TCHAR * szUserName = new TCHAR[1024];
			DWORD dwSize = 1024;
			GetUserName(szUserName, &dwSize);
			m_parent->OnSymInit(buf, symOptions, szUserName);
			delete[] szUserName;

			return TRUE;
		}

		CStackTrace *			m_parent;

		HMODULE					m_hDbhHelp;
		HANDLE					m_hProcess;
		LPTSTR					m_szSymPath;

	public:
		tSC						pSC;
		tSFTA					pSFTA;
		tSGLFA					pSGLFA;
		tSGMB					pSGMB;
		tSGMI					pSGMI;
		tSGO					pSGO;
		tSGSFA					pSGSFA;
		tSI						pSI;
		tSLM					pSLM;
		tSSO					pSSO;
		tUDSN					pUDSN;
		tSGSP					pSGSP;

	private:		//	Operations
		// **************************************** ToolHelp32 ************************
#define MAX_MODULE_NAME32 255
#define TH32CS_SNAPMODULE   0x00000008
#pragma pack( push, 8 )
		typedef struct tagMODULEENTRY32
		{
			DWORD   dwSize;
			DWORD   th32ModuleID;       // This module
			DWORD   th32ProcessID;      // owning process
			DWORD   GlblcntUsage;       // Global usage count on the module
			DWORD   ProccntUsage;       // Module usage count in th32ProcessID's context
			BYTE  * modBaseAddr;        // Base address of module in th32ProcessID's context
			DWORD   modBaseSize;        // Size in bytes of module starting at modBaseAddr
			HMODULE hModule;            // The hModule of this module in th32ProcessID's context
			char    szModule[MAX_MODULE_NAME32 + 1];
			char    szExePath[MAX_PATH];
		} MODULEENTRY32;
		typedef MODULEENTRY32 *  PMODULEENTRY32;
		typedef MODULEENTRY32 *  LPMODULEENTRY32;
#pragma pack( pop )

		BOOL GetModuleListTH32(HANDLE hProcess, DWORD pid)
		{
			// CreateToolhelp32Snapshot()
			typedef HANDLE(__stdcall *tCT32S)(DWORD dwFlags, DWORD th32ProcessID);
			// Module32First()
			typedef BOOL(__stdcall *tM32F)(HANDLE hSnapshot, LPMODULEENTRY32 lpme);
			// Module32Next()
			typedef BOOL(__stdcall *tM32N)(HANDLE hSnapshot, LPMODULEENTRY32 lpme);

			// try both dlls...
			const TCHAR *dllname[] = { _T("kernel32.dll"), _T("tlhelp32.dll") };
			HINSTANCE hToolhelp = NULL;
			tCT32S pCT32S = NULL;
			tM32F pM32F = NULL;
			tM32N pM32N = NULL;

			HANDLE hSnap;
			MODULEENTRY32 me;
			me.dwSize = sizeof(me);
			BOOL keepGoing;
			size_t i;

			for (i = 0; i<(sizeof(dllname) / sizeof(dllname[0])); i++)
			{
				hToolhelp = LoadLibrary(dllname[i]);
				if (hToolhelp == NULL)
					continue;
				pCT32S = (tCT32S)GetProcAddress(hToolhelp, "CreateToolhelp32Snapshot");
				pM32F = (tM32F)GetProcAddress(hToolhelp, "Module32First");
				pM32N = (tM32N)GetProcAddress(hToolhelp, "Module32Next");
				if ((pCT32S != NULL) && (pM32F != NULL) && (pM32N != NULL))
					break; // found the functions!
				FreeLibrary(hToolhelp);
				hToolhelp = NULL;
			}

			if (hToolhelp == NULL)
				return FALSE;

			hSnap = pCT32S(TH32CS_SNAPMODULE, pid);
			if (hSnap == (HANDLE)-1)
				return FALSE;

			keepGoing = !!pM32F(hSnap, &me);
			int cnt = 0;
			while (keepGoing)
			{
				this->LoadModule(hProcess, me.szExePath, me.szModule, (DWORD64)me.modBaseAddr, me.modBaseSize);
				cnt++;
				keepGoing = !!pM32N(hSnap, &me);
			}
			CloseHandle(hSnap);
			FreeLibrary(hToolhelp);
			if (cnt <= 0)
				return FALSE;
			return TRUE;
		}  // GetModuleListTH32

		// **************************************** PSAPI ************************
		typedef struct _MODULEINFO {
			LPVOID lpBaseOfDll;
			DWORD SizeOfImage;
			LPVOID EntryPoint;
		} MODULEINFO, *LPMODULEINFO;

		BOOL GetModuleListPSAPI(HANDLE hProcess)
		{
			// EnumProcessModules()
			typedef BOOL(__stdcall *tEPM)(HANDLE hProcess, HMODULE *lphModule, DWORD cb, LPDWORD lpcbNeeded);
			// GetModuleFileNameEx()
			typedef DWORD(__stdcall *tGMFNE)(HANDLE hProcess, HMODULE hModule, LPSTR lpFilename, DWORD nSize);
			// GetModuleBaseName()
			typedef DWORD(__stdcall *tGMBN)(HANDLE hProcess, HMODULE hModule, LPSTR lpFilename, DWORD nSize);
			// GetModuleInformation()
			typedef BOOL(__stdcall *tGMI)(HANDLE hProcess, HMODULE hModule, LPMODULEINFO pmi, DWORD nSize);

			HINSTANCE hPsapi;
			tEPM pEPM;
			tGMFNE pGMFNE;
			tGMBN pGMBN;
			tGMI pGMI;

			DWORD i;
			//ModuleEntry e;
			DWORD cbNeeded;
			MODULEINFO mi;
			HMODULE *hMods = 0;
			char *tt = NULL;
			char *tt2 = NULL;
			const SIZE_T TTBUFLEN = 8096;
			int cnt = 0;

			hPsapi = LoadLibrary(_T("psapi.dll"));
			if (hPsapi == NULL)
				return FALSE;

			pEPM = (tEPM)GetProcAddress(hPsapi, "EnumProcessModules");
			pGMFNE = (tGMFNE)GetProcAddress(hPsapi, "GetModuleFileNameExA");
			pGMBN = (tGMFNE)GetProcAddress(hPsapi, "GetModuleBaseNameA");
			pGMI = (tGMI)GetProcAddress(hPsapi, "GetModuleInformation");
			if ((pEPM == NULL) || (pGMFNE == NULL) || (pGMBN == NULL) || (pGMI == NULL))
			{
				// we couldn´t find all functions
				FreeLibrary(hPsapi);
				return FALSE;
			}

			hMods = (HMODULE*)malloc(sizeof(HMODULE)* (TTBUFLEN / sizeof HMODULE));
			tt = (char*)malloc(sizeof(char)* TTBUFLEN);
			tt2 = (char*)malloc(sizeof(char)* TTBUFLEN);
			if ((hMods == NULL) || (tt == NULL) || (tt2 == NULL))
				goto cleanup;

			if (!pEPM(hProcess, hMods, TTBUFLEN, &cbNeeded))
			{
				//_ftprintf(fLogFile, _T("%lu: EPM failed, GetLastError = %lu\n"), g_dwShowCount, gle );
				goto cleanup;
			}

			if (cbNeeded > TTBUFLEN)
			{
				//_ftprintf(fLogFile, _T("%lu: More than %lu module handles. Huh?\n"), g_dwShowCount, lenof( hMods ) );
				goto cleanup;
			}

			for (i = 0; i < cbNeeded / sizeof hMods[0]; i++)
			{
				// base address, size
				pGMI(hProcess, hMods[i], &mi, sizeof mi);
				// image file name
				tt[0] = 0;
				pGMFNE(hProcess, hMods[i], tt, TTBUFLEN);
				// module name
				tt2[0] = 0;
				pGMBN(hProcess, hMods[i], tt2, TTBUFLEN);

				DWORD dwRes = this->LoadModule(hProcess, tt, tt2, (DWORD64)mi.lpBaseOfDll, mi.SizeOfImage);
				if (dwRes != ERROR_SUCCESS)
					this->m_parent->OnDbgHelpErr(_T("LoadModule"), dwRes, 0);
				cnt++;
			}

		cleanup:
			if (hPsapi != NULL) FreeLibrary(hPsapi);
			if (tt2 != NULL) free(tt2);
			if (tt != NULL) free(tt);
			if (hMods != NULL) free(hMods);

			return cnt != 0;
		}  // GetModuleListPSAPI

		DWORD LoadModule(HANDLE hProcess, LPCSTR img, LPCSTR mod, DWORD64 baseAddr, DWORD size)
		{
			CHAR *szImg = _strdup(img);
			CHAR *szMod = _strdup(mod);
			DWORD result = ERROR_SUCCESS;
			if ((szImg == NULL) || (szMod == NULL))
				result = ERROR_NOT_ENOUGH_MEMORY;
			else
			{
				if (pSLM(hProcess, 0, szImg, szMod, baseAddr, size) == 0)
					result = GetLastError();
			}
			ULONGLONG fileVersion = 0;
			if ((m_parent != NULL) && (szImg != NULL))
			{
				// try to retrive the file-version:
				if ((this->m_parent->m_options & StackTraceOptions::RetrieveFileVersion) != 0)
				{
					VS_FIXEDFILEINFO *fInfo = NULL;
					DWORD dwHandle;
					DWORD dwSize = GetFileVersionInfoSizeA(szImg, &dwHandle);
					if (dwSize > 0)
					{
						LPVOID vData = malloc(dwSize);
						if (vData != NULL)
						{
							if (GetFileVersionInfoA(szImg, dwHandle, dwSize, vData) != 0)
							{
								UINT len;
								TCHAR szSubBlock[] = _T("\\");
								if (VerQueryValue(vData, szSubBlock, (LPVOID*)&fInfo, &len) == 0)
									fInfo = NULL;
								else
								{
									fileVersion = ((ULONGLONG)fInfo->dwFileVersionLS) + ((ULONGLONG)fInfo->dwFileVersionMS << 32);
								}
							}
							free(vData);
						}
					}
				}

				// Retrive some additional-infos about the module
				IMAGEHLP_MODULE64_V2 Module;
				const char *szSymType = "-unknown-";
				if (this->GetModuleInfo(hProcess, baseAddr, &Module) != FALSE)
				{
					switch (Module.SymType)
					{
					case SymNone:
						szSymType = "-nosymbols-";
						break;
					case SymCoff:
						szSymType = "COFF";
						break;
					case SymCv:
						szSymType = "CV";
						break;
					case SymPdb:
						szSymType = "PDB";
						break;
					case SymExport:
						szSymType = "-exported-";
						break;
					case SymDeferred:
						szSymType = "-deferred-";
						break;
					case SymSym:
						szSymType = "SYM";
						break;
					case 8: //SymVirtual:
						szSymType = "Virtual";
						break;
					case 9: // SymDia:
						szSymType = "DIA";
						break;
					}
				}
				this->m_parent->OnLoadModule(img, mod, baseAddr, size, result, szSymType, Module.LoadedImageName, fileVersion);
			}
			if (szImg != NULL) free(szImg);
			if (szMod != NULL) free(szMod);
			return result;
		}

	public:
		BOOL LoadModules(HANDLE hProcess, DWORD dwProcessId)
		{
			// first try toolhelp32
			if (GetModuleListTH32(hProcess, dwProcessId))
				return true;
			// then try psapi
			return GetModuleListPSAPI(hProcess);
		}


		BOOL GetModuleInfo(HANDLE hProcess, DWORD64 baseAddr, PIMAGEHLP_MODULE64 pModuleInfo)
		{
			if (this->pSGMI == NULL)
			{
				SetLastError(ERROR_DLL_INIT_FAILED);
				return FALSE;
			}

			pModuleInfo->SizeOfStruct = sizeof(IMAGEHLP_MODULE64);
			LPBYTE pData = new BYTE[4096];
			//LPVOID pData = malloc(4096); // reserve enough memory, so the bug in v6.3.5.1 does not lead to memory-overwrites...
			if (pData == NULL)
			{
				SetLastError(ERROR_NOT_ENOUGH_MEMORY);
				return FALSE;
			}

			pData = reinterpret_cast<LPBYTE>(pModuleInfo);
			::std::copy(pModuleInfo, pModuleInfo + sizeof(IMAGEHLP_MODULE64), checked_array_iterator<LPBYTE>(pData, sizeof(IMAGEHLP_MODULE64)));
			//memcpy(pData, pModuleInfo, sizeof(IMAGEHLP_MODULE64));
			
			if (SymGetModuleInfo64(hProcess, baseAddr, (PIMAGEHLP_MODULE64)pData) != FALSE)
			{
				// only copy as much memory as is reserved...
				memcpy(pModuleInfo, pData, sizeof(IMAGEHLP_MODULE64));
				pModuleInfo->SizeOfStruct = sizeof(IMAGEHLP_MODULE64);
				
				delete[] pData;
				return TRUE;
			}

			delete[] pData;

			SetLastError(ERROR_DLL_INIT_FAILED);
			return FALSE;
		}
	};

#pragma	endregion

#pragma	region CStackTrace Implementation

	CStackTrace::CStackTrace(StackTraceOptions	options = OptionsAll,
		LPCTSTR				szSymPath = NULL,
		DWORD				dwProcessId = GetCurrentProcessId(),
		HANDLE				hProcess = GetCurrentProcess())
	{
	}


	CStackTrace::~CStackTrace()
	{
	}

#pragma endregion
}