#pragma once

namespace conlib {

	class CArgumentException : public CException
	{
	public:
		CArgumentException() _NOEXCEPT_;
		CArgumentException(LPCTSTR) _NOEXCEPT_;
		CArgumentException(LPCTSTR, LPCTSTR) _NOEXCEPT_;
		virtual ~CArgumentException() _NOEXCEPT_;

	public:
		virtual const LPTSTR	ArgumentName(void) const _NOEXCEPT_;

	protected:
		void					SetArgumentName(LPCTSTR);

	private:
		LPTSTR		m_lpszArgument;
	};

}