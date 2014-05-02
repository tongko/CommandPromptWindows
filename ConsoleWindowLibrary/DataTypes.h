#pragma once
#include	"Stdafx.h"

namespace conlib {

	//	Entry for each Callstack-Entry
	typedef struct CallstackEntry {
		DWORD64			offset;  // if 0, we have no valid entry
		CHAR			name[STACKWALK_MAX_NAMELEN];
		CHAR			undName[STACKWALK_MAX_NAMELEN];
		CHAR			undFullName[STACKWALK_MAX_NAMELEN];
		DWORD64			offsetFromSmybol;
		DWORD			offsetFromLine;
		DWORD			lineNumber;
		CHAR			lineFileName[STACKWALK_MAX_NAMELEN];
		DWORD			symType;
		LPCSTR			symTypeString;
		CHAR			moduleName[STACKWALK_MAX_NAMELEN];
		DWORD64			baseOfImage;
		CHAR			loadedImageName[STACKWALK_MAX_NAMELEN];
	} CallstackEntry;

	typedef enum tagStackTraceOptions {
		// No addition info will be retrived 
		// (only the address is available)
		RetrieveNone		= 0x00,
		// Try to get the symbol-name
		RetrieveSymbol		= 0x01,
		// Try to get the line for this symbol
		RetrieveLine		= 0x02,
		// Try to retrieve the module-infos
		RetrieveModuleInfo	= 0x04,
		// Also retrieve the version for the DLL/EXE
		RetrieveFileVersion	= 0x08,
		// Contains all the abouve
		RetrieveVerbose		= RetrieveSymbol | RetrieveLine | RetrieveModuleInfo | RetrieveFileVersion,
		// Generate a "good" symbol-search-path
		SymBuildPath		= 0x10,
		// Also use the public Microsoft-Symbol-Server
		SymUseSymSrv		= 0x20,
		// Contains all the abouve "Sym"-options
		SymAll				= SymBuildPath | SymUseSymSrv,
		// Contains all options (default)
		OptionsAll			= RetrieveVerbose | SymAll
	} StackTraceOptions;

	typedef enum CallstackEntryType {
		firstEntry, 
		nextEntry, 
		lastEntry 
	};

	//typedef struct tagIMAGEHLP_MODULE64T_V2 {
	//	DWORD		SizeOfStruct;				// set to sizeof(IMAGEHLP_MODULE64)
	//	DWORD64		BaseOfImage;				// base load address of module
	//	DWORD		ImageSize;					// virtual size of the loaded module
	//	DWORD		TimeDateStamp;				// date/time stamp from pe header
	//	DWORD		CheckSum;					// checksum from the pe header
	//	DWORD		NumSyms;					// number of symbols in the symbol table
	//	SYM_TYPE	SymType;					// type of symbols loaded
	//	TCHAR		ModuleName[32];			// module name
	//	TCHAR		ImageName[256];			// image name
	//	TCHAR		LoadedImageName[256];		// symbol file name
	//} IMAGEHLP_MODULE64T_V2, *PIMAGEHLP_MODULE64T_V2, far* LPIMAGEHLP_MODULE64T_V2;

	//// SymCleanup()
	//typedef BOOL(__stdcall *tSC)(IN HANDLE hProcess);

	//// SymFunctionTableAccess64()
	//typedef PVOID(__stdcall *tSFTA)(HANDLE hProcess, DWORD64 AddrBase);

	//// SymGetLineFromAddr64()
	//typedef BOOL(__stdcall *tSGLFA)(IN HANDLE hProcess, IN DWORD64 dwAddr,
	//	OUT PDWORD pdwDisplacement, OUT PIMAGEHLP_LINE64 Line);

	//// SymGetModuleBase64()
	//typedef DWORD64(__stdcall *tSGMB)(IN HANDLE hProcess, IN DWORD64 dwAddr);

	//// SymGetModuleInfo64()
	//typedef BOOL(__stdcall *tSGMI)(IN HANDLE hProcess, IN DWORD64 dwAddr, OUT IMAGEHLP_MODULE64T_V2 *ModuleInfo);

	////  // SymGetModuleInfo64()
	////  typedef BOOL (__stdcall *tSGMI_V3)( IN HANDLE hProcess, IN DWORD64 dwAddr, OUT IMAGEHLP_MODULE64_V3 *ModuleInfo );
	////  tSGMI_V3 pSGMI_V3;

	//// SymGetOptions()
	//typedef DWORD(__stdcall *tSGO)(VOID);

	//// SymGetSymFromAddr64()
	//typedef BOOL(__stdcall *tSGSFA)(IN HANDLE hProcess, IN DWORD64 dwAddr,
	//	OUT PDWORD64 pdwDisplacement, OUT PIMAGEHLP_SYMBOL64 Symbol);

	//// SymInitialize()
	//typedef BOOL(__stdcall *tSI)(IN HANDLE hProcess, IN PSTR UserSearchPath, IN BOOL fInvadeProcess);

	//// SymLoadModule64()
	//typedef DWORD64(__stdcall *tSLM)(IN HANDLE hProcess, IN HANDLE hFile,
	//	IN PSTR ImageName, IN PSTR ModuleName, IN DWORD64 BaseOfDll, IN DWORD SizeOfDll);

	//// SymSetOptions()
	//typedef DWORD(__stdcall *tSSO)(IN DWORD SymOptions);

	//// StackWalk64()
	//typedef BOOL(__stdcall *tSW)(
	//	DWORD MachineType,
	//	HANDLE hProcess,
	//	HANDLE hThread,
	//	LPSTACKFRAME64 StackFrame,
	//	PVOID ContextRecord,
	//	PREAD_PROCESS_MEMORY_ROUTINE64 ReadMemoryRoutine,
	//	PFUNCTION_TABLE_ACCESS_ROUTINE64 FunctionTableAccessRoutine,
	//	PGET_MODULE_BASE_ROUTINE64 GetModuleBaseRoutine,
	//	PTRANSLATE_ADDRESS_ROUTINE64 TranslateAddress);
	//tSW pSW;

	//// UnDecorateSymbolName()
	//typedef DWORD(__stdcall WINAPI *tUDSN)(PCSTR DecoratedName, PSTR UnDecoratedName,
	//	DWORD UndecoratedLength, DWORD Flags);

	//typedef BOOL(__stdcall WINAPI *tSGSP)(HANDLE hProcess, PSTR SearchPath, DWORD SearchPathLength);


}