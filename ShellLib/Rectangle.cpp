#include	"stdafx.h"
#include	"Coord.h"
#include	"Size.h"
#include	"Rectangle.h"

namespace ShellLib { namespace Drawing {

#pragma	region	Constructor
	/********************
	*    Constructor    *
	********************/

	CRectangle::CRectangle(CCoord c, CSize sz) {
		m_x = c.X;
		m_y = c.Y;
		m_width = sz.Width;
		m_height = sz.Height;
	}

	CRectangle::CRectangle(short x, short y, short width, short height) {
		m_x = x;
		m_y = y;
		m_width = width;
		m_height = height;
	}

#pragma endregion


#pragma region Properties
	/*******************
	*    Properties    *
	*******************/

	CCoord		CRectangle::Location::get(void) {
		return CCoord(m_x, m_y);
	}
	void		CRectangle::Location::set(CCoord value) {
		m_x = value.X;
		m_y = value.Y;
	}

	CSize		CRectangle::Size::get(void) {
		return CSize(m_width, m_height);
	}
	void		CRectangle::Size::set(CSize value) {
		m_width = value.Width;
		m_height = value.Height;
	}

	short		CRectangle::X::get(void) {
		return m_x;
	}
	void		CRectangle::X::set(short value) {
		m_x = value;
	}

	short		CRectangle::Y::get(void) {
		return m_y;
	}
	void		CRectangle::Y::set(short value) {
		m_y = value;
	}

	short		CRectangle::Width::get(void) {
		return m_width;
	}
	void		CRectangle::Width::set(short value) {
		m_width = value;
	}

	short		CRectangle::Height::get(void) {
		return m_height;
	}
	void		CRectangle::Height::set(short value) {
		m_height = value;
	}

	short		CRectangle::Left::get(void) {
		return m_x;
	}

	short		CRectangle::Top::get(void) {
		return m_y;
	}

	short		CRectangle::Right::get(void) {
		return m_x + m_width;
	}

	short		CRectangle::Bottom::get(void) {
		return m_y + m_height;
	}

	bool		CRectangle::IsEmpty::get(void) {
		return m_x == m_y == m_width == m_height == 0;
	}

#pragma endregion


#pragma	region	Operations
	/*******************
	*    Operations    *
	*******************/

	bool		CRectangle::operator==(CRectangle left, CRectangle right) {
		return left.X == right.X && left.Y == right.Y && left.Width == right.Width && left.Height == right.Height;
	}

	bool		CRectangle::operator!=(CRectangle left, CRectangle right) {
		return !(left == right);
	}

	CRectangle	CRectangle::FromLTRB(short l, short t, short r, short b) {
		return CRectangle(l, t, r - l, b - t);
	}

	bool		CRectangle::Equals(Object ^ obj) {
		if (obj == nullptr || !obj->GetType()->Equals(CRectangle::typeid))
			return false;

		CRectangle rect = (CRectangle)obj;
		return rect.X == m_x && rect.Y == m_y && rect.Width == m_width && rect.Height == m_height;
	}

	bool		CRectangle::Contains(short x, short y) {
		return m_x <= x && m_x + m_width > x 
			&& m_y <= y && m_y + m_height > y;
	}

	bool		CRectangle::Contains(CCoord c) {
		return Contains(c.X, c.Y);
	}

	bool		CRectangle::Contains(CRectangle rect) {
		return m_x <= rect.X
			&& m_x + m_width >= rect.Right
			&& m_y <= rect.Y
			&& m_y + m_height >= rect.Bottom;
	}

	int			CRectangle::GetHashCode(void) {
		return m_x ^ (m_y << 6 | (short)((UInt16) m_y >> 10))
				^ (m_width << 13 | (short)((UInt16) m_width >> 3))
				^ (m_height << 4 | (short)((UInt16) m_height >> 12));
	}

	void		CRectangle::Inflate(short dx, short dy) {
		m_x -= dx;
		m_y -= dy;
		m_width += 2 * dx;
		m_height += 2 * dy;
	}

	void		CRectangle::Inflate(CSize sz) {
		Inflate(sz.Width, sz.Height);
	}

	CRectangle	CRectangle::Inflate(CRectangle rect, short dx, short dy) {
		CRectangle rectangle = rect;
		rectangle.Inflate(dx, dy);

		return rectangle;
	}

	void		CRectangle::Intersec(CRectangle rect) {
		CRectangle rectangle = CRectangle::Intersec(rect, (*this));
		m_x = rectangle.X;
		m_y = rectangle.Y;
		m_width = rectangle.Width;
		m_height = rectangle.Height;
	}

	CRectangle	CRectangle::Intersec(CRectangle a, CRectangle b) {
		short x = max(a.X, b.X);
		short w = min(a.Right, b.Right);
		short y = max(a.Y, b.Y);
		short h = min(a.Bottom, b.Bottom);

		return (w >= x && h >= y)
			? CRectangle(x, y, w - x, h - y)
			: CRectangle::Empty;
	}

	bool		CRectangle::IntersecWith(CRectangle rect) {
		return rect.X < Right && X < rect.Right && rect.Y < Bottom && Y < rect.Bottom;
	}

	CRectangle	CRectangle::Union(CRectangle a, CRectangle b) {
		short x = min(a.X, b.X);
		short w = max(a.Right, b.Right);
		short y = min(a.Y, b.Y);
		short h = max(a.Bottom, b.Bottom);
		return CRectangle(x, y, w - x, h - y);
	}

	void		CRectangle::Offset(CCoord c) {
		Offset(c.X, c.Y);
	}

	void		CRectangle::Offset(short dx, short dy) {
		m_x += dx;
		m_y += dy;
	}

	String ^	CRectangle::ToString(void) {
		return "{X=" 
			+ m_x.ToString(CultureInfo::CurrentCulture) 
			+ ",Y=" + m_y.ToString(CultureInfo::CurrentCulture) 
			+ ",Width=" + m_width.ToString(CultureInfo::CurrentCulture) 
			+ ",Height=" + m_height.ToString(CultureInfo::CurrentCulture) + "}";
	}

#pragma endregion
}}