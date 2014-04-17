#pragma once

namespace ShellLib { namespace Workspaces {

	using namespace ShellLib::Configs;
	using namespace System;
	using namespace System::Drawing;

	public enum CursorSize
	{
		Small,
		Medium,
		Large
	};

	ref class CWorkspaceManager
	{
	public:
		CWorkspaceManager();
		~CWorkspaceManager();

	public:
		void		Initialize(CWorkspaceConfigSection ^ configSecion);
		void		StartWorkspace();

	public:
		property short					Width {
			short		get(void);
			void		set(short value);
		}
		property short					Height {
			short		get(void);
			void		set(short value);
		}
		property String ^				Name {
			String ^	get(void);
			void		set(String ^ value);
		}
		property ShellLib::CursorSize	CursorSize {
		ShellLib::CursorSize
						get(void);
			void		set(ShellLib::CursorSize value);
		}
		property Point					WindowPosition {
			Point		get(void);
			void		set(Point value);
		}

	private:
		ShellLib::CursorSize
						m_cursorSize;
		short			m_height;
		String ^		m_name;
		short			m_width;
		Point			m_windowPosition;
	};

}}