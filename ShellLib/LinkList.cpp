#include "stdafx.h"
#include "Node.h"
#include "LinkList.h"

namespace Unmanaged {

	template <typename T>
	CLinkList<T>::CLinkList(void) {
		m_head = NULL;
	}

	template <typename T>
	CLinkList<T>::CLinkList(const T & value) {
		m_head = CreateNode(value);
	}

	//
	//	Push - link a node to the end of list;
	//
	template <typename T> 
	void CLinkList<T>::Push(const T & value) {
		PushValue(value);
	}

	//
	//	Pop - Retrieve a value from list;
	//
	template <typename T>
	T & CLinkList<T>::Pop() {
		return PopValue();
	}

	//
	//	GetTrailNode - Get node at end of list;
	//
	template <typename T>
	CNode<T> * CLinkList<T>::GetTrailNode() {
		if (m_head == NULL) return m_head;

		CNode<T> * temp = m_head;
		while (temp->next != NULL)
			temp = temp->next;

		return temp;
	}
}