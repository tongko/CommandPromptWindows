#include "Stdafx.h"
#include "Size.h"

namespace ShellLib { namespace Drawing {

#pragma	region	Constructor
	/*********************
	*	Constructor
	**********************/

	CSize::CSize(CCoord c) {
		m_width = c.X;
		m_height = c.Y;
	}

	CSize::CSize(short w, short h) {
		m_width = w;
		m_height = h;
	}

#pragma endregion


#pragma region Properties
	/******************
	* Properties
	*******************/

	bool	CSize::IsEmpty::get(void) {
		return m_width == m_height == 0;
	}

	short	CSize::Height::get(void) {
		return m_height;
	}
	void	CSize::Height::set(short value) {
		m_height = value;
	}

	short	CSize::Width::get(void) {
		return m_width;
	}
	void	CSize::Width::set(short value) {
		m_width = value;
	}

#pragma endregion


#pragma	region	Operations
	/*******************
	*    Operations    *
	*******************/

	CSize::operator ShellLib::Drawing::CCoord(CSize sz) {
		return CCoord(sz.m_width, sz.m_height);
	}

	CSize	CSize::operator+(CSize left, CSize right) {
		return Add(left, right);
	}

	CSize	CSize::operator-(CSize left, CSize right) {
		return Subtract(left, right);
	}

	bool	CSize::operator==(CSize left, CSize right) {
		return left.m_width == right.m_width && left.m_height == right.m_height;
	}

	bool	CSize::operator!=(CSize left, CSize right) {
		return !(left == right);
	}

	CSize	CSize::Add(CSize sz1, CSize sz2) {
		return CSize(sz1.m_width + sz2.m_width, sz1.m_height + sz2.m_height);
	}

	CSize	CSize::Subtract(CSize sz1, CSize sz2) {
		return CSize(sz1.m_width - sz2.m_width, sz1.m_height - sz2.m_height);
	}

	bool	CSize::Equals(Object ^ obj) {
		if (obj == nullptr || !obj->GetType()->Equals(CSize::typeid))
			return false;

		CSize sz = (CSize)obj;
		return m_width == sz.m_width && m_height == sz.m_height;
	}

	int		CSize::GetHashCode(void) {
		return m_width ^ m_height;
	}

	String ^ CSize::ToString(void) {
		return "{Width=" + m_width.ToString(CultureInfo::CurrentCulture) 
			+ ", Height=" + m_height.ToString(CultureInfo::CurrentCulture) + "}";
	}

#pragma	endregion

}}