#include	"Stdafx.h"
#include	"Message.h"

namespace ShellLib { namespace Workspaces {

	using namespace System::Runtime::InteropServices;

#pragma region Properties
	//////////////////////
	//    Properties    //
	//////////////////////

	int		CMessage::WorkspaceId::get(void) { return m_wspId; }
	void	CMessage::WorkspaceId::set(int value) { m_wspId = value; }

	int		CMessage::Message::get(void) { return m_msg; }
	void	CMessage::Message::set(int value) { m_msg = value; }

	IntPtr	CMessage::WParam::get(void) { return m_wparam; }
	void	CMessage::WParam::set(IntPtr value) { m_wparam = value; }

	IntPtr	CMessage::LParam::get(void) { return m_lparam; }
	void	CMessage::LParam::set(IntPtr value) { m_lparam = value; }

	IntPtr	CMessage::Result::get(void) { return m_result; }
	void	CMessage::Result::set(IntPtr value) { m_result = value; }
	
#pragma endregion


#pragma region	Operations
	//////////////////////
	//    Operations    //
	//////////////////////

	Object ^ CMessage::GetLParam(Type ^ cls) {
		return Marshal::PtrToStructure(m_lparam, cls);
	}

	CMessage	CMessage::Create(int id, int msg, IntPtr wparam, IntPtr lparam) {
		return CMessage(id, msg, wparam, lparam);
	}

	bool	CMessage::Equals(Object ^ obj) {
		if (obj == nullptr || !obj->GetType()->Equals(CMessage::typeid))
			return false;

		CMessage m = (CMessage)obj;
		return m.m_wspId == m_wspId && m.m_msg == m_msg && m.m_wparam == m_wparam
			&& m.m_lparam == m_lparam && m.m_result == m_result;
	}

	int		CMessage::GetHashCode(void) {
		return (int)m_wspId << 4 | m_msg;
	}

	String ^	CMessage::ToString(void) {
		return Object::ToString();
	}


#pragma endregion

}}
