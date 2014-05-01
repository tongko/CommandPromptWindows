#include	"stdafx.h"
#include	"Exception.h"
#include	"ArgumentException.h"

namespace conlib {

	CArgumentException::CArgumentException() {
	}

	CArgumentException::CArgumentException(LPCTSTR pmessage) {
		CException::SetMessage(pmessage);
	}

	CArgumentException::CArgumentException(LPCTSTR pmessage, LPCTSTR parg) {
		CException::SetMessage(pmessage);

		SetArgumentName(parg);
	}

	CArgumentException::~CArgumentException(void)
	{
		if (m_lpszArgument != NULL)
			delete[] m_lpszArgument;

		CException::~CException();
	}

}