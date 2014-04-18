#include "stdafx.h"
#include "WorkspaceConfigSection.h"
#include "WorkspaceManager.h"


namespace ShellLib { namespace Workspaces {

	CWorkspaceManager::CWorkspaceManager() 
	{
//		m_cursorSize = ShellLib::CursorSize::Small;
		m_height = 25;
		m_width = 80;
		m_windowPosition = Point(1, 1);
		m_name = String::Empty;
	}

	CWorkspaceManager::~CWorkspaceManager() {
	}


#pragma region Properties

//	CursorSize	CWorkspaceManager::CursorSize::get(void) { return m_cursorSize; }
//	void	CWorkspaceManager::CursorSize::set(ShellLib::CursorSize value) { m_cursorSize = value; }

	short	CWorkspaceManager::Height::get(void) { return m_height; }
	void	CWorkspaceManager::Height::set(short value) { m_height = value; }

	String ^	CWorkspaceManager::Name::get(void) { return m_name; }
	void		CWorkspaceManager::Name::set(String ^ value) { m_name = value; }

	short	CWorkspaceManager::Width::get(void) { return m_width; }
	void	CWorkspaceManager::Width::set(short value) { m_width = value; }

	Point	CWorkspaceManager::WindowPosition::get(void) { return m_windowPosition; }
	void	CWorkspaceManager::WindowPosition::set(Point value) { m_windowPosition = value; }

#pragma endregion


#pragma region Methods

	void	CWorkspaceManager::Initialize(CWorkspaceConfigSection ^ configSection) {
		if (configSection == nullptr)
			throw gcnew ArgumentNullException("configSection");

//		m_cursorSize = configSection->CursorSize;
		m_height = configSection->Height;
		m_name = configSection->Name;
		m_width = configSection->Width;
		m_windowPosition = configSection->WindowPosition;
	}

#pragma endregion

}}