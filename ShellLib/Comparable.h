#pragma once
#include	"Stdafx.h"

namespace Unmanaged { namespace btree {

	//
	//	cmp_t is an enumeration type indicating the result of a comparison.
	//
	private enum  cmp_t {
		MIN_CMP = -1,		// less than
		EQ_CMP = 0,			// equal to
		MAX_CMP = 1			// greater than
	};

	template <class T>
	private class IComparable {
	public:
		virtual cmp_t	CompareTo(const T & value) = 0;
		virtual T &		Value() const = 0;
	};

	//
	//	An arbitrary comparable element with a keyfield that has an ordering 
	//	relation. The template parameter TKey is the type of the keyfield
	//
	template <class TValue>
	private class CComparable : public IComparable<TValue> {
	public:
		CComparable(const TValue & value) : m_value(value) {};

		// Compare this item against the given key & return the result
		virtual cmp_t	Compare(const TValue & value) const {
			return (value == m_value)
				? EQ_CMP
				: ((value < m_value)
					? MIN_CMP
					: MAX_CMP);
		}

		// Get the key-field of an item
		virtual TValue &	Value() const { return  m_key; }

	private:
		TValue &	m_value;
	};

}}