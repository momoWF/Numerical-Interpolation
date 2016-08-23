#ifndef _DLLIST_H_
#define _DLLIST_H_

#include <iostream>

using namespace std;

template <class Type> class DLListInteractor;

template <class Type>
class Node{
public:
	Type data;
	Node<Type> *next;
	Node<Type> *prev;
};

//---------------------------------------------------------------------//
template <class Type>
class DoublyLinkedList{
private:
	Node<Type> *head;
	Node<Type> *tail;
	int size;

	bool isEmpty(void){ return (head == NULL); };
	Node<Type> *search(Type *data);

public:
	DoublyLinkedList(void);
	DoublyLinkedList(Node<Type> *copy);
	~DoublyLinkedList(void);

	void insert(Node<Type> *node);
	void insert(Type *data);

	void insertBack(Node<Type> *node);
	void insertBack(Type *data);

	void insertAfter(Node<Type> *bfr, Node<Type> *aft);
	void insertAfter(Node<Type> *bfr, Type *data);
	void insertAfter(Type *bfr, Type *aft);

	void remove(Node<Type> *node);
	void remove(Type *data);
	void reset(void);

	void printList(void) const;
	inline int getSize(void) const { return size; };
	inline Node<Type>* getHead(void) const { return head; };
	inline Node<Type>* getTail(void) const { return tail; };

	friend  class DLListInteractor<Type>;

};

//-------------------------------------------------------------------//
// Apparently the compiler request that constructors and destructor 
// must be in header file;
template <class Type>
DoublyLinkedList<Type>::DoublyLinkedList(void){
	head = NULL;
	tail = NULL;
	size = 0;
}

//-------------------------------------------------------------------//
template <class Type>
DoublyLinkedList<Type>::DoublyLinkedList(Node<Type> *copy){
	head = copy;
	tail = copy;
	size = 0;

	while(tail->next != NULL){
		tail = tail->next;
		size ++;
	}
}

//-------------------------------------------------------------------//
template <class Type>
DoublyLinkedList<Type>::~DoublyLinkedList(void){
	Node<Type> *tmp, *curNode = head;

	while(curNode){
		tmp     = curNode->next;
		delete  curNode;
		curNode = tmp;
	}
}

//-------------------------------------------------------------------//
template <class Type>
void DoublyLinkedList<Type>::insert(Type *data){

	Node<Type> *node = new Node<Type>;
	node->data = *data;

	insert(node);
}
//-------------------------------------------------------------------//
template <class Type>
void DoublyLinkedList<Type>::insert(Node<Type> *node){

	Node<Type> *curNode = head;

	if( isEmpty() ){
		head = node;
		head->next = NULL;
		head->prev = NULL;

		tail = head;
		size = 1;
		return;
	}

	while( curNode && curNode->data < node->data ){
		curNode = curNode->next;
	}

	if( curNode == head ){

		curNode->prev = node;
		node->next = curNode;
		node->prev = NULL;

		head = node;
		size ++;
		return;
	}

	if(curNode){

		curNode->prev->next = node;	
		node->prev = curNode->prev;

		node->next = curNode;
		curNode->prev = node;

		size ++;
		return;

	}

	tail->next = node;
	node->prev = tail;
	node->next = NULL;
	tail = node;

	size++;
	return;
}
//-------------------------------------------------------------------//
template <class Type>
void DoublyLinkedList<Type>::insertBack(Type *data){

	Node<Type> *node = new Node<Type>;
	node->data = *data;

	insertBack(node);
}
//-------------------------------------------------------------------//
template <class Type>
void DoublyLinkedList<Type>::insertBack(Node<Type> *node){

	if( isEmpty() ){
		head = node;
		head->next = NULL;
		head->prev = NULL;

		tail = head;
		size = 1;
		return;
	}

	tail->next = node;
	node->prev = tail;
	tail       = node;
	tail->next = NULL;

	size++;
}

//-------------------------------------------------------------------//
template <class Type>
Node<Type>* DoublyLinkedList<Type>::search(Type *data){

	Node<Type> *curNode = head;

	while(curNode){

		if(curNode->data == *data)
			return curNode;

		curNode = curNode->next;

	}

	return NULL;
}

//-------------------------------------------------------------------//
template <class Type>
void DoublyLinkedList<Type>::insertAfter(Node<Type> *bfr, Node<Type> *aft){
	bfr->next->prev = aft;
	aft->next = bfr->next;

	bfr->next = aft;
	aft->prev = bfr;

	size++;
}
//-------------------------------------------------------------------//
template <class Type>
void DoublyLinkedList<Type>::insertAfter(Node<Type> *bfr, Type *dat){

	Node<Type> *aft = new Node<Type>;
	aft->data = *dat;

	insertAfter(bfr,aft);

}

//-------------------------------------------------------------------//
template <class Type>
void DoublyLinkedList<Type>::insertAfter(Type *bfr, Type *aft){

	Node<Type> *Bfr = search(bfr);

	if(Bfr) insertAfter(Bfr,aft);

}

//-------------------------------------------------------------------//
template <class Type>
void DoublyLinkedList<Type>::remove(Node<Type> *node){

	if(node == head){
		if(tail = head) tail = node->next;
		head = node->next;
		head->prev = NULL;

		size--;
		delete node;
		return;
	}

	if(node == tail){
		tail = tail->prev;
		tail->next = NULL;

		size--;
		delete node;
		return;
	}

	node->next->prev = node->prev;
	node->prev->next = node->next;

	size --;
	delete node;
}

//-------------------------------------------------------------------//
template <class Type>
void DoublyLinkedList<Type>::remove(Type *data){

	Node<Type> *key = search(data);

	if(key)	remove(key);

}

//-------------------------------------------------------------------//
template <class Type>
void DoublyLinkedList<Type>::printList(void) const{
	Node<Type> *curNode = head;
	int i = 0;

	while(curNode){
		curNode = curNode->next;
		cout<<"# "<<i<<"\n";
		i++;
	}
}

//-------------------------------------------------------------------//
template <class Type>
void DoublyLinkedList<Type>::reset(void){

	Node<Type> *tmp, *curNode = head;

	while(curNode){
		tmp     = curNode->next;
		delete  curNode;
		curNode = tmp;
	}

	head = NULL;
	tail = NULL;
	size = 0;

}

//-------------------------------------------------------------------//


#endif
