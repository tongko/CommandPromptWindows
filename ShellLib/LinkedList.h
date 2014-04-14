#pragma once

#include	"stdafx.h"
#include	"Node.h"

namespace Unmanaged {

	template <typename T>
	private class CLinkedList abstract
	{
	protected:
		CLinkedList(void) { m_head = NULL; }
		CLinkedList(const T * head) { m_head = CreateNode(value); m_count++; }
		~CLinkedList(void) {
			Clear();
		}

	public:
		void	Push(const T * value) { PushValue(value); }
		T *		Pop(void) {	return PopValue(); }
		T *		Peek(void) { return PeekValue(); }
		void	Clear(void) {
			if (m_head == NULL) return;

			CNode<T> * node = m_head;
			do
			{
				CNode<T> * temp = node->next;
				delete node;
				node = temp;
			} while (node != NULL);

			m_count = 0;
		}

	protected:
		virtual void	PushValue(const T * value) = 0;
		virtual T *		PopValue(void) = 0;
		virtual T *		PeekValue(void) = 0;

		void			SetHeadNode(const T * value) {
			Clear();
			m_head = CreateNode(value);
		}

		CNode<T> *		GetHeadNode() {
			return m_head;
		}

		CNode<T> *		GetTrailNode() {
			if (m_head == NULL) return m_head;

			CNode<T> * temp = m_head;
			while (temp->next != NULL)
				temp = temp->next;

			return temp;
		}

	protected:
		int			m_count;

	private:
		CNode<T> *	m_head;
	};
}