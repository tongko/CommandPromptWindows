#pragma once
#include	"Stdafx.h"
#include	"Workspaces.h"

namespace ShellLib { namespace Workspaces {

	using namespace ShellLib::Drawing;

	interface struct IWorkspace
	{
	public:
		//	Properties
		property CCoord		Location { CCoord get(void); void set(CCoord value); }
		property CSize		Size { CSize get(void); void set(CSize value); }
		property CRectangle	ClientArea { CRectangle get(void); void set(CRectangle value); }
		property EWorkspaceBorderStyle BorderStyle { EWorkspaceBorderStyle get(void); void set(EWorkspaceBorderStyle value); }
		property String ^	Caption { String ^ get(void); void set(String ^ value); }
		property int		ZOrder { int get(void); void set(int value); }
		property bool		MinimizeBox { bool get(void); void set(bool value); }
		property bool		RestroreBox { bool get(void); void set(bool value); }

		//	Operations
		void				Activate(void);
		void				Focus(void);
	};

}}