#pragma once

#include "Stdafx.h"

/*
* Message structure
*/
typedef struct _tagMSG {
	INT			hWindow;
	UINT        message;
	WPARAM      wParam;
	LPARAM      lParam;
	DWORD       time;
	POINT       pt;
} MESSAGE, FAR *LPMESSAGE;
