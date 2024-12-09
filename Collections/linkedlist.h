#pragma once
#include <iostream>

template <class T>
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
        void remove(Node<T>*);
};


template <class T>
Node<T>::Node(T inValue) { 
    value = inValue;
    next = nullptr;
    prev = nullptr;
}

template <class T>
Node<T>::~Node() { }

template <class T>
T Node<T>::getValue() {
    return this->value;
}

template <class T>
LinkedList<T>::LinkedList(){}

template <class T>
void LinkedList<T>::insert(T value) {
    Node<T>* insertedNode = new Node<T>(value);
    if(head != nullptr)
    {
        head->prev = insertedNode;
        insertedNode->next = head;
        head = insertedNode;
        
    }
    else
    {
        head = insertedNode;
        tail = insertedNode;
    } 
}

template <class T>
void LinkedList<T>::pushBack(T value) {
    Node<T>* insertedNode = new Node<T>(value);
    if(tail != nullptr)
    {
        tail->next = insertedNode;
        insertedNode->prev = tail;
        tail = insertedNode;
        
    }
    else
    {
        head = insertedNode;
        tail = insertedNode;
    } 
}


template <class T>
void LinkedList<T>::remove(Node<T>* nodeToRemove) {
    if(nodeToRemove == nullptr)
    {
        return;
    }
    // two nodes (left node , prev = nullptr)
    if(head == nodeToRemove)
    {
        if(head->next != nullptr)
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
    if(tail == nodeToRemove)
    {
        tail = nodeToRemove->prev;
        tail->next = nullptr;
        delete nodeToRemove;
    }
    else
    {
        // general case
        if(nodeToRemove->prev != nullptr)
            nodeToRemove->prev->next = nodeToRemove->next;
        if(nodeToRemove->next != nullptr)
            nodeToRemove->next->prev = nodeToRemove->prev;
        delete nodeToRemove;
    }
    return;
}
template <class T>
void printAllList(LinkedList<T>* list)
{
    if(list->head == nullptr)
        std::cout << "list is empty\n";

    Node<T>* node = list->head;
    if(list->head == nullptr)
        return;
    while(node != nullptr) {
        std::cout << node->getValue() << ",";
        node = node->getNext();
       
    }
    std::cout << "\nHEAD: " << list->head->getValue();
    std::cout << " TAIL: " << list->tail->getValue();

    std::cout << "\n";
}

