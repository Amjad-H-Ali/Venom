#include "Queue.h"

Queue::Queue()
	:head(nullptr), tail(nullptr), current(nullptr)
{};


/*
	*
	* Pushes a pointer to an object at the end of the Queue.
	*
*/
void Queue::push(T *objPtr) {

	Node<T> *newNode = new Node<T>;

	newNode->value = objPtr;

	// First Node in Queue. Assign all pointers to it.
	if(!head) {head = newNode; tail = newNode; current = newNode;}

	// Append Node to end of Queue.
	else {

		tail->next = newNode;

		newNode->prev = tail;

		tail = newNode;
	}

};


/*
	*
	* Moves "current" pointer a number of places ahead.
	* Params: Number of places to move in the Queue.
	*
*/
void Queue::jump(unsigned places) {

	for(unsigned i = 0; current && i < places; ++i, current = current->next);
};

/*
	*
	* Returns Node in Queue that "current" is pointing to.
	*
*/
Node<T> *Queue::current();