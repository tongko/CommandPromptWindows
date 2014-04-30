#include	"Stdafx.h"
#include	"Exception.h"
#include	<DbgHelp.h>

namespace conlib {

	CException::CException()
		: m_message(NULL), m_dofree(false) { };

	CException::CException(const CException & exception)
		: m_message(NULL), m_dofree(false) {
		*this = exception;
	};

	CException & CException::operator=(const CException & exception) {
		if (this != &exception) {
			CleanUp();

			if (exception.m_dofree)
				CopyString(exception.m_message);
			else
				m_message = exception.m_message;
		}

		return *this;
	};

	CException::~CException() {
		CleanUp();
	};

	LPCTSTR CException::Message() const {
			return m_message ? m_message : _T("Unknown exception");
	};

	// assumes that *this is already tidy.
	void CException::CopyString(LPCTSTR pmessage) {
		if (pmessage != NULL) {
			size_t buf_size;
			StringCchLength(pmessage, MAX_STR_LENGTH, &buf_size);
			++buf_size;

			m_message = new TCHAR[buf_size];

			if (m_message != NULL) {
				StringCchPrintf(m_message, buf_size, pmessage);
				m_dofree = true;
			}
		}
	}

	void CException::SetMessage(LPCTSTR pmessage) {
		CleanUp();
		CopyString(pmessage);
	}

	void CException::CleanUp(void) {
		if (m_dofree)
			delete[] m_message;

		m_message = NULL;
		m_dofree = false;
	}

	void CException::FillStackTrace(void) {
		UINT			i;
		LPVOID			stack[1024];
		USHORT			frames;
		PSYMBOL_INFO 	symbol;
		HANDLE			process = GetCurrentProcess();

		SymInitialize(process, NULL, TRUE);

		frames = CaptureStackBackTrace(0, 1024, stack, NULL);
		symbol = new SYMBOL_INFO();    (PSYMBOL_INFO)calloc(sizeof(SYMBOL_INFO)+256 * sizeof(char), 1);
		symbol->MaxNameLen = 255;
		symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

		for (i = 0; i < frames; i++)
		{
			SymFromAddr(process, (DWORD64)(stack[i]), 0, symbol);

			printf("%i: %s - 0x%0X\n", frames - i - 1, symbol->Name, symbol->Address);
		}

		free(symbol);
	}
}