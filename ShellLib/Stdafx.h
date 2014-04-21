// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once
#pragma comment(lib, "Kernel32.lib")

#define		WIN32_LEAN_AND_MEAN
#include	<Windows.h>
#include	<tchar.h>
#include	<strsafe.h>


//
//	Application Includes
//
#include	"LockGuard.h"
#include	"Exceptions.h"
#include	"Common.h"