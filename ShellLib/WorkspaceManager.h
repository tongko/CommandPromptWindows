#pragma once

namespace ShellLib { namespace Workspaces {

	using namespace ShellLib;
	using namespace ShellLib::Configs;
	using namespace System;
	using namespace System::Drawing;

	ref class CWorkspaceManager
	{
	public:
		CWorkspaceManager();
		~CWorkspaceManager();

	public:
		void		Initialize(CShellLibConfigSection ^ configSecion);
		//void		StartWorkspace();

	public:
		property short					Width;
		property short					Height;
		property String ^				Name;
		property CursorSizeEnum			CursorSize;
		property Point					WindowPosition;
		property CShellSettings ^		Settings;

	};

}}