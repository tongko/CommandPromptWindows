#pragma once

#include	"Stdafx.h"


namespace Unmanaged {

	template <typename T>
	struct CNode {
		CNode<T> *	next;
		CNode<T> *	previous;
		T *			value;
	};

	template <typename T> CNode<T> * CreateNode(const T * value) {
		CNode<T> * node = new CNode<T>;
		node->value = value;

		return node;
	};

	template <typename T> void InsertBefore(CNode<T> * node, const T * value) {
		if (node == NULL) return;

		CNode<T> * newNode = CreateNode(value);
		if (node->previous != NULL) {
			CNode<T> * temp = node->previous;
			temp->next = newNode;
			newNode->previous = temp;
		}

		node->previous = newNode;
		newNode->next = node;
	};

	template <typename T> void InsertAfter(CNode<T> * node, const T * value) {
		if (node == NULL) return;

		CNode<T> * newNode = CreateNode(value);
		if (node->next != NULL) {
			CNode<T> * temp = node->next;
			temp->previous = newNode;
			newNode->next = temp;
		}

		node->next = newNode;
		newNode->previous = node;
	};

	template <typename T> T * Remove(CNode<T> * node) {
		if (node == NULL) return NULL;

		T * value = node->value;
		CNode<T> * after = node->next;
		if (after == NULL) {
			after = node->previous;
			if (after == NULL) return NULL;
			RemoveAfter(after);
		}
		else {
			RemoveBefore(after);
		}

		return value;
	}

	template <typename T> T * RemoveBefore(CNode<T> * node) {
		if (node == NULL || node->previous == NULL) return NULL;

		CNode<T> * temp = node->previous;
		T * value = temp->value;
		if (temp->previous != NULL) {
			CNode<T> * prevTemp = temp->previous;
			prevTemp->previous = node;
			node->previous = prevTemp;
		}

		delete temp;
		return value;
	};

	template <typename T> T * RemoveAfter(CNode<T> * node) {
		if (node == NULL || node->next == NULL) return NULL;

		CNode<T> * temp = node->next;
		T * value = temp->value;
		if (temp->next != NULL) {
			CNode<T> * nextTemp = temp->next;
			nextTemp->previous = node;
			node->next = nextTemp;
		}

		delete temp;
		return value;
	};
}