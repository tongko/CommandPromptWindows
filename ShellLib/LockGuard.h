#pragma once
#include	"Stdafx.h"

namespace ShellLib { namespace Threading {

	private class CLockGuard
	{
	public:
		CLockGuard(HANDLE hMutex)
		{
			m_hMutex = hMutex;
			WaitForSingleObject(m_hMutex, INFINITE);
		}

		~CLockGuard()
		{
			if (m_hMutex != NULL)
				ReleaseMutex(m_hMutex);
		}

	private:
		HANDLE		m_hMutex;
	};

}}