#include "Stdafx.h"
#include "Coord.h"

namespace ShellLib { namespace Drawing {

#pragma region Constructor
	/********************
	*    Constructor    *
	********************/

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
	/*******************
	*    Properties    *
	*******************/

	bool	CCoord::IsEmpty::get(void) {
		return x == y == 0;
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
	/*******************
	*    Operations    *
	*******************/

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
		return x ^ y;
	}

	void	CCoord::Offset(CCoord c) {
		Offset(c.x, c.y);
	}

	void	CCoord::Offset(short dx, short dy) {
		x += dx;
		y += dy;
	}

	String ^	CCoord::ToString(void) {
		return "{X=" + x.ToString(CultureInfo::CurrentCulture)
			+ ",Y=" + y.ToString(CultureInfo::CurrentCulture)
			+ "}";
	}

#pragma endregion

}}