#pragma once

namespace ShellLib { namespace Drawing {

	using namespace System::Diagnostics;
	using namespace System::Globalization;

	[DebuggerDisplayAttribute("{X: {X}, Y: {Y}, Width: {Width}, Height: {Height}}")]
	value class CRectangle
	{
	public:		//	Constructor
		CRectangle(CCoord c, CSize sz);
		CRectangle(short x, short y, short width, short height);

	public:		//	Fields
		static initonly CRectangle	Empty = CRectangle(0, 0, 0, 0);

	private:	//	Fields
		short				m_x;
		short				m_y;
		short				m_width;
		short				m_height;

	public:		//	Properties
		property short		Bottom { short get(void); }
		property short		Height { short get(void); void set(short value); }
		property bool		IsEmpty { bool get(void); }
		property short		Left { short get(void); }
		property CCoord		Location { CCoord get(void); void set(CCoord value); }
		property short		Right { short get(void); }
		property CSize		Size { CSize get(void); void set(CSize value); }
		property short		Top { short get(void); }
		property short		Width { short get(void); void set(short value); }
		property short		X { short get(void); void set(short value); }
		property short		Y { short get(void); void set(short value); }

	public:		//	Operations
		bool				Contains(CCoord c);
		bool				Contains(CRectangle rc);
		bool				Contains(short x, short y);
		virtual bool		Equals(Object ^ obj) override;
		static CRectangle	FromLTRB(short l, short t, short r, short b);
		virtual int			GetHashCode(void) override;
		void				Inflate(CSize sz);
		void				Inflate(short dw, short dh);
		static CRectangle	Inflate(CRectangle rc, short dw, short dh);
		void				Intersec(CRectangle rc);
		static CRectangle	Intersec(CRectangle rcA, CRectangle rcB);
		bool				IntersecWith(CRectangle rc);
		void				Offset(CCoord c);
		void				Offset(short dx, short dy);
		virtual String ^	ToString(void) override;
		static CRectangle	Union(CRectangle rcA, CRectangle rcB);

	public:		//	Operators overload
		static bool operator ==(CRectangle left, CRectangle right);
		static bool operator !=(CRectangle left, CRectangle right);
	};

}}