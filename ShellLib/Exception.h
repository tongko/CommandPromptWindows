#pragma once
#include	"Stdafx.h"
#include	"Constants.h"

namespace shllib {

#define		_NOEXCEPT_		throw ()

	class CException
	{
	public:
		CException(void) _NOEXCEPT_;
		CException(const CException &) _NOEXCEPT_;
		CException & operator=(const CException &) _NOEXCEPT_;
		virtual ~CException(void);
		virtual const TCHAR * Message(void) const _NOEXCEPT_;

	protected:
		virtual void CleanUp(void) _NOEXCEPT_;

	private:
		void CopyString(const TCHAR *);

		TCHAR * m_message;
		bool m_dofree;
	};

	CException::CException()
		: m_message(NULL), m_dofree(false) { }

	CException::CException(const CException & exception)
		: m_message(NULL), m_dofree(false)
	{
		*this = exception;
	}

	CException & CException::operator=(const CException & exception)
	{
		if (this != &exception)
		{
			CleanUp();

			if (exception.m_dofree)
				CopyString(exception.m_message);
			else
				m_message = exception.m_message;
		}

		return *this;
	}

	CException::~CException() _NOEXCEPT
	{
		CleanUp();
	}

	const TCHAR * CException::Message() const
	{
			return m_message ? m_message : _T("Unknown exception");
	}

	// assumes that *this is already tidy.
	void CException::CopyString(const TCHAR * pmessage) {
		if (pmessage != NULL) {
			size_t buf_size;
			StringCchLength(pmessage, ShellLib::MAX_STR_LENGTH, &buf_size);
			++buf_size;

			m_message = new TCHAR[buf_size];

			if (m_message != NULL) {
				StringCchPrintf(m_message, buf_size, pmessage);
				m_dofree = true;
			}
		}
	}

	void CException::CleanUp(void)
	{
		if (m_dofree)
			delete[] m_message;

		m_message = NULL;
		m_dofree = false;
	}

}