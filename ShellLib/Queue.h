#pragma	once

#include "Stdafx.h"
#include "Node.h"
#include "LinkedList.h"

namespace Unmanaged {

	template <typename T>
	private class CQueue : public CLinkedList<T>
	{
	protected:
		virtual void	PushValue(const T & value) {
			CNode<T> * trailNode = GetTrailNode();

			if (trailNode == NULL) {
				SetHeadNode(value);
			}
			else {
				InsertAfter(trailNode, value);
			}

			m_count++;
		}

		virtual T &		PopValue(void) {
			CNode<T> * headNode = GetHeadNode();

			if (headNode == NULL) return NULL;
			
			T & value = Remove(headNode);
			m_count--;
			return value;
		}

		virtual T &		PeekValue(void) {
			CNode<T> * headNode = GetHeadNode();
			if (headNode == NULL) return NULL;

			return headNode->value;
		}
	};
}