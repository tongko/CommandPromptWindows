#pragma once

namespace ShellLib { namespace Drawing {

	value class CSize
	{
	public:		//	Constructor
		CSize(short x, short y);

	public:		//	Attributes
		static initonly CSize 	Empty = { 0, 0 };
		
	private:
		short	m_height;
		short	m_width;

	public:		//	Properties
		property short		Height { short get(void); void set(short value); }
		property bool		IsEmpty { bool get(void); }
		property short		Width { short get(void); void set(short value); }

	public:		//	Methods
	};

}}