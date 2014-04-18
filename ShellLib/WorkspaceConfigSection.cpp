#include "stdafx.h"
#include "WorkspaceConfigSection.h"

namespace ShellLib { namespace Configs {

#pragma region Properties

	//CursorSize	CWorkspaceConfigSection::CursorSize::get(void) { return (ShellLib::CursorSize) this["cursorSize"]; }
	//void	CWorkspaceConfigSection::CursorSize::set(ShellLib::CursorSize value) { this["cursorSize"] = value; }

	short	CWorkspaceConfigSection::Height::get(void) { return (short)this["height"]; }
	void	CWorkspaceConfigSection::Height::set(short value) { this["height"] = value; }

	String ^	CWorkspaceConfigSection::Name::get(void) { return (String ^)this["name"]; }
	void		CWorkspaceConfigSection::Name::set(String ^ value) { this["name"] = value; }

	short	CWorkspaceConfigSection::Width::get(void) { return (short)this["width"]; }
	void	CWorkspaceConfigSection::Width::set(short value) { this["width"] = value; }

	Point	CWorkspaceConfigSection::WindowPosition::get(void) { 
		String ^ value = (String ^)this["point"];
		if (String::IsNullOrWhiteSpace(value)) return Point::Empty;
		
		array<Char> ^ splitter = { ',' };
		array<String^> ^ values = value->Split(splitter);
		int x, y;
		x = Int32::Parse(values[0]);
		y = Int32::Parse(values[1]);

		return Point(x, y); 
	}
	void	CWorkspaceConfigSection::WindowPosition::set(Point value) { this["point"] = String::Format("{0},{1}", value.X, value.Y); }

#pragma endregion


}}