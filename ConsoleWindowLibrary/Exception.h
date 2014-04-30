#pragma once

namespace conlib {

	class CException {
	public:
		CException(void) _NOEXCEPT_;
		CException(const CException &) _NOEXCEPT_;
		virtual ~CException(void);

		CException &	operator=(const CException &) _NOEXCEPT_;
		virtual LPCTSTR	Message(void) const _NOEXCEPT_;

	protected:
		void			SetMessage(LPCTSTR) _NOEXCEPT_;
		virtual void	CleanUp(void) _NOEXCEPT_;

	private:
		void			CopyString(LPCTSTR);
		void			FillStackTrace(void);

	private:
		LPTSTR		m_stackTrace;
		LPTSTR		m_message;
		bool		m_dofree;
	};
}