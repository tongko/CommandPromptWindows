#include "Stdafx.h"
#include "Size.h"
#include "Coord.h"

namespace ShellLib { namespace Drawing {

#pragma region Constructor
	/*********************
	*	Constructor
	**********************/

	CCoord::CCoord(CSize sz) {
		x = sz.Width;
		y = sz.Height;
	}

	CCoord::CCoord(short x, short y) {
		this->x = x;
		this->y = y;
	}

	CCoord::CCoord(int dw) {
		x = LOWORD(dw);
		y = HIWORD(dw);
	}

#pragma endregion


#pragma region Properties
	/******************
	* Properties
	*******************/

	bool	CCoord::IsEmpty::get(void) {
		return x == 0 && y == 0;
	}

	short	CCoord::X::get(void) {
		return x;
	}
	void	CCoord::X::set(short value) {
		x = value;
	}

	short	CCoord::Y::get(void) {
		return y;
	}
	void	CCoord::Y::set(short value) {
		y = value;
	}

#pragma endregion


#pragma	region	Operations

	CCoord::operator ShellLib::Drawing::CSize(CCoord c) {
		return CSize(c.x, c.y);
	}

	CCoord CCoord::operator+ (CCoord c, CSize sz) {
		return CCoord::Add(c, sz);
	}

	CCoord CCoord::operator- (CCoord c, CSize sz) {
		return CCoord::Subtract(c, sz);
	}

	bool CCoord::operator== (CCoord left, CCoord right) {
		return (left.x == right.x && left.y == right.y);
	}

	bool CCoord::operator!= (CCoord left, CCoord right) {
		return !(left == right);
	}

	CCoord	CCoord::Add(CCoord c, CSize sz) {
		return CCoord(c.x + sz.Width, c.y + sz.Height);
	}

	CCoord	CCoord::Subtract(CCoord c, CSize sz) {
		return CCoord(c.x - sz.Width, c.y - sz.Height);
	}

	bool	CCoord::Equals(Object ^ obj) {
		if (obj == nullptr || !obj->GetType()->Equals(CCoord::typeid))
			return false;
		CCoord c = (CCoord)obj;
		
		return (c.x == x && c.y == y);
	}

	int		CCoord::GetHashCode(void) {
		static int hash = x ^ y;	//	Hopefully this will remain unchange

		return hash;
	}

	void	CCoord::Offset(CCoord c) {
		Offset(c.x, c.y);
	}

	void	CCoord::Offset(short dx, short dy) {
		x += dx;
		y += dy;
	}

	String ^	CCoord::ToString(void) {
		return "{X=" + x.ToString(System::Globalization::CultureInfo::CurrentCulture)
			+ ",Y=" + y.ToString(System::Globalization::CultureInfo::CurrentCulture)
			+ "}";
	}

	CCoord::operator int(CCoord c) {
		int result = c.x;
		result << 16;
		result += c.y;
	}

#pragma endregion

}}