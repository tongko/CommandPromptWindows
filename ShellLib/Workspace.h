#pragma once

namespace ShellLib { namespace Workspaces {

	using namespace ShellLib::Drawing;
	using namespace System::Collections::Generic;

	ref class CWorkspace : public IWorkspace
	{
	public:
		CWorkspace();

	public:		//	Properties
		virtual property CCoord		Location { CCoord get(void); void set(CCoord value); }
		virtual property CSize		Size { CSize get(void); void set(CSize value); }
		virtual property CRectangle	ClientArea { CRectangle get(void); void set(CRectangle value); }
		virtual property BorderStyleType BorderStyle { BorderStyleType get(void); void set(BorderStyleType value); }
		virtual property String ^	Caption { String ^ get(void); void set(String ^ value); }
		virtual property int		ZOrder { int get(void); void set(int value); }
		virtual property bool		MinimizeBox { bool get(void); void set(bool value); }
		virtual property bool		RestroreBox { bool get(void); void set(bool value); }
		virtual property WorkspaceCollection ^ Workspaces { WorkspaceCollection ^ get(void); void set(WorkspaceCollection ^ value); }

	public:
		virtual void				Activate(void);
		virtual void				Focus(void);

		virtual void				Invalidate(void);
		virtual void				Update(void);

	protected:		//	Operations
		virtual void				OnActivate(void);
		virtual void				OnLoad(void);
		virtual void				OnFocus(bool focus);
		virtual void				OnMouseEnter(bool leave);
		virtual void				OnMouseMove(void);
		virtual void				OnMouseButtonClicked(int buttonId);
		virtual void				OnKeyDown();	// <== needs argument
		virtual void				OnKeyUp();
		virtual void				OnKeyPress();
		virtual void				OnSizeChanged(void);	
		virtual void				WndProc(CMessage % message);

	private:
		CCoord						m_location;
		CSize						m_size;
		CRectangle					m_clientArea;
		BorderStyleType				m_borderStyle;
		String ^					m_caption;
		int							m_zorder;
		int							m_controlBox;
		WorkspaceCollection ^		m_workspaces;
	};

}}