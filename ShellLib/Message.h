#pragma once

namespace ShellLib { namespace Workspaces {

	using namespace System;

	value class CMessage {
	private:		// Constructor
		CMessage(int id, int msg, IntPtr wparam, IntPtr lparam)
		{
			m_wspId = id;
			m_msg = msg;
			m_wparam = wparam;
			m_lparam = lparam;
			m_result = IntPtr::Zero;
		}

	private:
		int			m_wspId;
		int			m_msg;
		IntPtr		m_wparam;
		IntPtr		m_lparam;
		IntPtr		m_result;

	public:			//	Properties
		property int		WorkspaceId { int get(void); void set(int value); }
		property int		Message { int get(void); void set(int value); }
		property IntPtr		WParam { IntPtr get(void); void set(IntPtr value); }
		property IntPtr		LParam { IntPtr get(void); void set(IntPtr value); }
		property IntPtr		Result { IntPtr get(void); void set(IntPtr value); }

	public:			//	Operations
		static CMessage		Create(int id, int msg, IntPtr wparam, IntPtr lparam);
		virtual bool		Equals(Object ^ obj) override;
		virtual int			GetHashCode(void) override;
		Object ^			GetLParam(Type ^ cls);
		virtual String ^	ToString(void) override;

	public:			//	Operator overloads
		static bool operator ==(CMessage a, CMessage b) { return a.Equals(b); }
		static bool operator !=(CMessage a, CMessage b) { return !a.Equals(b); }
	};

}}

namespace ShellLib {
	namespace Workspaces {

		delegate void WinProcHandler(CMessage % message);

	}
}