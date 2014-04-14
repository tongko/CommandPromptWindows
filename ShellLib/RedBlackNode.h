#pragma once
#include	"Stdafx.h"
#include	"Comparable.h"

namespace Unmanaged { namespace RedBlackTree {

#define		PARENT_NODE			0
#define		LEFT_NODE			1
#define		RIGHT_NODE			2
#define		MAX_NODE_RELATION	3

	using namespace Unmanaged::btree;

	template <class TKey>
	private class CRedBlackNode : public CComparable<Tkey>
	{
	public:
		CRedBlackNode(const TKey & key)
			: CComparable(key) {
			m_relation = new CRedBlackNode<TKey>[MAX_NODE_RELATION];
		}
		virtual ~CRedBlackNode() {
			if (m_relation != NULL) {
				for (int i = 0; i < MAX_NODE_RELATION; i++) {
					m_relation[i] = NULL;
				}

				delete[] m_relation;
			}
		}

	private:
		CRedBlackNode<TKey> *	m_relation[MAX_NODE_RELATION];
		BOOL					m_red;		//	0 = Black, !0 = Red
	};

} }