// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once
#pragma comment(lib, "Kernel32.lib")

#define		WIN32_LEAN_AND_MEAN
#include	<Windows.h>
#include	<tchar.h>
#include	<strsafe.h>
#include	<iostream>

//
//	Application definition
//
#ifndef UNICODE
#define		__FILET__			__FILE__
#define		__FUNCTIONT__		__FUNCTION__
typedef		std::ostream		_tostream;
typedef		std::iostream		_tistream;
typedef		std::fstream		_tfstream;
#define		_tcout				std::cout
#define		_tcerr				std::cerr
#define		_tcin				std::cin
#define		_tclog				std::clog
#else
#define		__FILET__			__FILEW__
#define		__FUNCTIONT__		__FUNCTIONW__
typedef		std::wostream		_tostream;
typedef		std::wiostream		_tistream;
typedef		std::wfstream		_tfstream;
#define		_tcout				std::wcout
#define		_tcerr				std::wcerr
#define		_tcin				std::wcin
#define		_tclog				std::wclog
#endif // !UNICODE

#define		EXIT_FATAL			4
#define		EXIT_ERROR			2
#define		EXIT_WARNING		1
#define		EXIT_SUCCESS		0


//
//	Application Includes
//
#include	"Constants.h"
#include	"LockGuard.h"
#include	"Exceptions.h"
#include	"Common.h"
#include	"Shell.h"
#include	"ShellSettings.h"


