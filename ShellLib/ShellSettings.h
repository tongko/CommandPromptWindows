#pragma once

namespace ShellLib {

	using namespace System;
	using namespace System::Drawing;
	using namespace ShellLib::Configs;
	using namespace ShellLib::Drawing;
	using namespace ShellLib::Workspaces;

	value class CShellLayout {
	public:
		property bool			MaxWindow;
		property CSize			WindowSize;
		property CSize			BufferSize;
		property CCoord			WindowLocation;

	public:
		Point					GetWindowLocation(void);
		static CShellLayout		GetDefaultLayout(void);
	};

	ref class CShellLibSettings
	{
	protected:
		CShellLibSettings(CShellLibConfigSection ^ section);

	public:
		property String ^		Caption;
		property CursorSizeEnum	CursorSize;
		property CShellLayout	Layout;

	public:		//	Operations
		static CShellLibSettings ^	Configure(CShellLibConfigSection ^ section);

	private:
		literal String ^		DefaultCaption = "ShellLib Workspace v0.1";
	};
}