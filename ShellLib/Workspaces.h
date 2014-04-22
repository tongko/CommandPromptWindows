#pragma once
#include	"Stdafx.h"
#include	"Message.h"

namespace ShellLib { namespace Workspaces {

#ifndef _WORKSPACE_TYPEDEF_
#define	_WORKSPACE_TYPEDEF_

	interface class IWorkspace;
	typedef	IWorkspace ^	HWSP;

#endif // !_WORKSPACE_TYPEDEF_

#ifndef _WORKSPACE_DECL_
#define	_WORKSPACE_DECL_
	ref class CWorkspace;
#endif // !_WORKSPACE_DECL_


	public enum EWorkspaceBorderStyle {
		None,
		Single,
		Double
	};

}}