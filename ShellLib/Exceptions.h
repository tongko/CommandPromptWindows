#pragma once
#include "Stdafx.h"

namespace ShellLib {

	using namespace System;
	using namespace System::Runtime::Serialization;

	ref class CAssertFailedException : public Exception
	{
	public:
		CAssertFailedException() : CAssertFailedException(nullptr) {}
		CAssertFailedException(String ^ message) : CAssertFailedException(message, 0, nullptr, nullptr, 0, nullptr) {}
		CAssertFailedException(String ^ message, int lineNumber, String ^ fileName,
			String ^ lineDescriptor, int errCode, Exception ^ innerException)
			: Exception(message, innerException) 
		{
			m_lineDesc = lineDescriptor;
			m_fileName = fileName;
			m_lineNumber = lineNumber;
			m_errorCode = errCode;
		}
		CAssertFailedException(SerializationInfo ^ info, StreamingContext context)
			: Exception(info, context) {}

	public:
		property int		LineNumber { int get(void) { return m_lineNumber; } void set(int value) { m_lineNumber = value; }}
		property String ^	FileName { String ^ get(void) { return m_fileName; } void set(String ^ value) { m_fileName = value; }}
		property String ^	LineDescriptor { String ^ get(void) { return m_lineDesc; } void set(String ^ value) { m_lineDesc = value; }}
		property int		ErrorCode { int get(void) { return m_errorCode; } void set(int value) { m_errorCode = value }}

	private:
		int					m_lineNumber;
		String ^			m_fileName;
		String ^			m_lineDesc;
		int					m_errorCode;
	};

}