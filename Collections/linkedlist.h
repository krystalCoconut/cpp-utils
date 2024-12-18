#pragma once
#include <iostream>
#include <cassert>
// This warning is just me using a second argument in an assert. Thats just normal! Annoying
#pragma warning (disable : 4002)

template <typename T>
class Node {

	T value;
public:
	Node* next;
	Node* prev;
	Node(T);
	~Node();
	Node* getNext() { return next; }
	const Node* getNext() const { return next; }
	T getValue();
};

template <typename T>
class LinkedList {
public:
	Node<T>* head;
	Node<T>* tail;
	LinkedList();
	void insert(T);
	void pushBack(T);
	void link(Node<T>*, Node<T>*);
	void unlink(Node<T>*);
};


template <typename T>
Node<T>::Node(T inValue) {
	value = inValue;
	next = nullptr;
	prev = nullptr;
}

template <typename T>
Node<T>::~Node() { }

template <typename T>
T Node<T>::getValue() {
	return this->value;
}



template <typename T>
LinkedList<T>::LinkedList() {}




template <typename T>
//[[depreciated("Use link(Node<T> a,T b) instead")]]
void LinkedList<T>::insert(T value) {
	Node<T>* insertedNode = new Node<T>(value);
	link(head, insertedNode);
}

template <typename T>
void LinkedList<T>::link(Node<T>* originalNode, Node<T>* newNode) {
	assert(originalNode == nullptr, "LinkedList<T>::link : node is empty!");
	assert(newNode == nullptr, "LinkedList<T>::link : newNode is empty!");

	newNode->next = originalNode->next;
	if (originalNode->next != nullptr) {
		originalNode->next->prev = newNode;
	}
	originalNode->next = newNode;
	newNode->prev = originalNode;
}

template <typename T>
void LinkedList<T>::pushBack(T value) {
	Node<T>* insertedNode = new Node<T>(value);
	link(tail, insertedNode);
}


template <typename T>
void LinkedList<T>::unlink(Node<T>* nodeToRemove) {
	assert(nodeToRemove == nullptr, "nodeToRemove is empty!");

	// two nodes (left node , prev = nullptr)
	if (head == nodeToRemove)
	{
		if (head->next != nullptr)
		{
			head = nodeToRemove->next;
			head->prev = nullptr;
		}
		else
		{
			head = nullptr;
			tail = nullptr;
		}
		delete nodeToRemove;

	}
	else
		// two nodes (right node, next = nullptr)
		if (tail == nodeToRemove)
		{
			tail = nodeToRemove->prev;
			tail->next = nullptr;
			delete nodeToRemove;
		}
		else
		{
			// general case
			if (nodeToRemove->prev != nullptr) { nodeToRemove->prev->next = nodeToRemove->next; }
			if (nodeToRemove->next != nullptr) { nodeToRemove->next->prev = nodeToRemove->prev; }
			delete nodeToRemove;
		}
}

template <typename T>
void printAllList(LinkedList<T>* list)
{
	assert(list->head == nullptr, "list is empty");

	Node<T>* node = list->head;
	while (node != nullptr) {
		std::cout << node->getValue() << ",";
		node = node->getNext();

	}
	std::cout << "\nHEAD: " << list->head->getValue();
	std::cout << " TAIL: " << list->tail->getValue();
	std::cout << "\n";
}

