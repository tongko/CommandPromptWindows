#include "stdafx.h"
#include "Workspaces.h"
#include "WorkspaceManager.h"


namespace ShellLib { namespace Workspaces {

	CWorkspaceManager::CWorkspaceManager() {
	}

	CWorkspaceManager::~CWorkspaceManager() {
	}


#pragma region Properties

#pragma endregion


#pragma region Methods

	void	CWorkspaceManager::Initialize(CShellLibConfigSection ^ configSection) {
		if (configSection == nullptr)
			throw gcnew ArgumentNullException("configSection");

		Settings = CShellSettings::Configure(configSection);

		CursorSize = Settings->CursorSize;
		Height = Settings->Layout.WindowSize.Height;
		Name = Settings->Caption;
		Width = Settings->Layout.WindowSize.Width;
		WindowPosition = Settings->Layout.GetWindowLocation();
	}

#pragma endregion

}}