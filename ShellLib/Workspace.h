#pragma once

namespace ShellLib { namespace Workspaces {

	using namespace ShellLib::Drawing;
	using namespace System::Collections::Generic;

	ref class CWorkspace
	{
	public:
		CWorkspace();

	public:		//	Properties
		property CCoord		Location { CCoord get(void); void set(CCoord value); }
		property CSize		Size { CSize get(void); void set(CSize value); }
		property CRectangle	ClientArea { CRectangle get(void); void set(CRectangle value); }
		property EWorkspaceBorderStyle BorderStyle { EWorkspaceBorderStyle get(void); void set(EWorkspaceBorderStyle value); }
		property String ^	Caption { String ^ get(void); void set(String ^ value); }
		property int		ZOrder { int get(void); void set(int value); }
		property bool		MinimizeBox { bool get(void); void set(bool value); }
		property bool		RestroreBox { bool get(void); void set(bool value); }

	protected:		//	Operations
		virtual void		OnActivate(void);
		virtual void		OnLoad(void);
		virtual void		OnFocus(bool focus);
		virtual void		OnMouseEnter(bool leave);
		virtual void		OnMouseMove(void);
		virtual void		OnMouseButtonClicked(int buttonId);
		virtual void		OnKeyDown();	// <== needs argument
		virtual void		OnKeyUp();
		virtual void		OnKeyPress();
		virtual void		OnSizeChanged(void);	
		virtual void		WndProc(CMessage % message);

	private:
		CCoord				m_location;
		CSize				m_size;
		CRectangle			m_clientArea;
		EWorkspaceBorderStyle m_borderStyle;
		String ^			m_caption;
		int					m_zorder;
		int					m_controlBox;
	};

}}