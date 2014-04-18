#pragma once

namespace ShellLib {
	namespace Drawing {
		//	To solve circular reference;
		value class CSize;
	}
}

#include	"Size.h"

namespace ShellLib { namespace Drawing {

	using namespace System::Diagnostics;
	using namespace System::Globalization;

	[DebuggerDisplayAttribute("{X: {X}, Y: {Y}}")]
	value class CCoord
	{
	public:		//	Constructor
		CCoord(CSize sz);
		CCoord(short x, short y);
		CCoord(int dw);

	public:		//	Attributes
		static initonly CCoord Empty = CCoord(0, 0);

	private:
		short x;
		short y;

	public:		// Properties
		property bool	IsEmpty { bool get(void); }
		property short	X { short get(void); void set(short value); }
		property short	Y { short get(void); void set(short value); }

	public:		// Operation
		static CCoord	Add(CCoord c, CSize size);
		virtual bool	Equals(Object ^ obj) override;
		virtual int		GetHashCode(void) override;
		void			Offset(CCoord c);
		void			Offset(short dx, short dy);
		virtual String^	ToString(void) override;
		static CCoord	Subtract(CCoord c, CSize sz);

	public:		// Operator overloads
		static CCoord	operator +(CCoord c, CSize sz) { return CCoord::Add(c, sz); };
		static bool		operator ==(CCoord left, CCoord right) { return (left.x == right.x && left.y == right.y); };
		static explicit operator CSize(CCoord c) { return CSize(c.x, c.y); };
		static explicit operator int(CCoord c) { int result = c.y; result = (result << 16) & 0xFFFF; result += c.x; return result; };
		static bool		operator !=(CCoord left, CCoord right) { return !(left == right); };
		static CCoord	operator -(CCoord c, CSize sz) { return CCoord::Subtract(c, sz); };
	};

}}