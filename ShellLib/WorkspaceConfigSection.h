#pragma once

namespace ShellLib { namespace Configs {

	using namespace ShellLib;
	using namespace System;
	using namespace System::Configuration;
	using namespace System::Drawing;

	ref class CWorkspaceConfigSection : public ConfigurationSection {
	public:
		static CWorkspaceConfigSection ^ GetConfigSection() {
			return (CWorkspaceConfigSection ^) ConfigurationManager::GetSection("WorkspaceManager");
		}

	public:
		[ConfigurationPropertyAttribute("width", DefaultValue = 80, IsRequired = false)]
		property short	Width {
			short		get(void);
			void		set(short value);
		}
		[ConfigurationPropertyAttribute("height", DefaultValue = 25, IsRequired = false)]
		property short	Height {
			short		get(void);
			void		set(short value);
		}
		[ConfigurationPropertyAttribute("name", IsRequired = false)]
		property String ^ Name {
			String ^	get(void);
			void		set(String ^ value);
		}
		[ConfigurationPropertyAttribute("cursorSize", IsRequreid = false)]
		property CursorSize	CursorSize {
			CursorSize	get(void);
			void		set(ShellLib::CursorSize value);
		}
		[ConfigurationPropertyAttribute("windowPosition", IsRequired = false)]
		property Point	WindowPosition {
			Point		get(void);
			void		set(Point value);
		}
	};

}}