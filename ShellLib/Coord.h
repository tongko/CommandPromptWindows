#pragma once

namespace ShellLib { namespace Drawing {

	value class CCoord
	{
	public:		//	Constructor
		CCoord(CSize sz);
		CCoord(short x, short y);
		CCoord(int dw);

	public:		//	Attributes
		static initonly CCoord Empty = { 0, 0 };
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
		static CCoord	operator +(CCoord c, CSize sz);
		static bool		operator ==(CCoord left, CCoord right);
		static explicit operator CSize(CCoord c);
		static explicit operator int(CCoord c);
		static bool		operator !=(CCoord left, CCoord right);
		static CCoord	operator -(CCoord c, CSize sz);
	};

}}