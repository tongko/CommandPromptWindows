#pragma	once

#include "Stdafx.h"
#include "Node.h"
#include "LinkedList.h"

namespace Unmanaged {

#define		MUTEXNAME		TEXT("QUEUEMUTEX")

	template <typename T>
	private class CQueue : public CLinkedList<T>
	{
	public:
		CQueue() {
			m_mutex = CreateMutex(NULL, FALSE, MUTEXNAME);
		}

		~CQueue() {
			if (m_mutex != NULL)
				ReleaseMutex(m_mutex);
		}

	protected:
		HANDLE		m_mutex;

	protected:
		virtual void	PushValue(const T & value) {

			WaitForSingleObject(m_mutex, INFINITE);

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
			WaitForSingleObject(m_mutex, INFINITE);

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