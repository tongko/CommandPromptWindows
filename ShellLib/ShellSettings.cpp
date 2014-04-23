#include "stdafx.h"
#include "ShellSettings.h"

namespace ShellLib {

	CShellLibSettings::CShellLibSettings(CShellLibConfigSection ^ section) {
		CShellConfigElement ^ shellConfig = section->ShellConfiguraiton;

		if (shellConfig == nullptr) {
			Caption = DefaultCaption;
			CursorSize = CursorSizeEnum::Small;
			Layout = CShellLayout::GetDefaultLayout();
		}
		else {
			Caption = String::IsNullOrWhiteSpace(shellConfig->Caption)
				? DefaultCaption
				: shellConfig->Caption;
			CursorSize = shellConfig->CursorSize;

			if (shellConfig->Layout == nullptr) {
				Layout = CShellLayout::GetDefaultLayout();
			}
			else {
				Layout = CShellLayout();
				CShellLayoutConfigElement ^ layoutConfig = shellConfig->Layout;
				Layout.BufferSize = CSize(layoutConfig->ScreenBufferSize->Width, layoutConfig->ScreenBufferSize->Height);
				Layout.WindowSize = CSize(layoutConfig->WindowSize->Width, layoutConfig->WindowSize->Height);
				Layout.WindowLocation = CCoord(layoutConfig->WindowLeft, layoutConfig->WindowTop);
				Layout.MaxWindow = layoutConfig->MaxWindow;
			}
		}
	}

	CShellLibSettings ^	CShellLibSettings::Configure(CShellLibConfigSection ^ section) {
		if (section == nullptr) throw gcnew ArgumentNullException("section");
		
		return gcnew CShellLibSettings(section);
	}

	CShellLayout		CShellLayout::GetDefaultLayout(void) {
		CShellLayout layout = CShellLayout();
		layout.BufferSize = CSize(80, 25);
		layout.WindowLocation = CCoord(0, 0);
		layout.WindowSize = CSize(80, 25);
		layout.MaxWindow = false;

		return layout;
	}

	Point		CShellLayout::GetWindowLocation(void) {
		return Point(WindowLocation.X, WindowLocation.Y);
	}
}