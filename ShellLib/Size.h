#pragma once

namespace ShellLib {
	namespace Drawing {
		value class CCoord;
	}
}

namespace ShellLib { namespace Drawing {

	using namespace System::Diagnostics;
	using namespace System::Globalization;
	
	[DebuggerDisplayAttribute("{Width: {Width}, Height: {Height}}")]
	value class CSize
	{
	public:		//	Constructor
		CSize(CCoord c);
		CSize(short w, short h);

	public:		//	Attributes
		static initonly CSize 	Empty = CSize( 0, 0);
		
	private:
		short	m_height;
		short	m_width;

	public:		//	Properties
		property short		Height { short get(void); void set(short value); }
		property bool		IsEmpty { bool get(void); }
		property short		Width { short get(void); void set(short value); }

	public:		//	Methods
		static CSize		Add(CSize sz1, CSize sz2);
		virtual bool		Equals(Object ^ obj) override;
		virtual int			GetHashCode(void) override;
		static CSize		Subtract(CSize sz1, CSize sz2);
		virtual String ^	ToString(void) override;

	public:		//	Operator overloads
		static CSize		operator +(CSize left, CSize right);
		static bool			operator ==(CSize left, CSize right);
		static explicit		operator CCoord(CSize sz);
		static bool			operator !=(CSize left, CSize right);
		static CSize		operator -(CSize left, CSize right);
	};

}}