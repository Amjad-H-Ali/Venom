#include "Queue.h"
#include "Node.h"

Queue::Queue()
	:head(nullptr), tail(nullptr), _current(nullptr)
{};


/*
	*
	* Pushes a pointer to an object at the end of the Queue.
	*
*/
void Queue::push(T objPtr) {

	Node<T> *newNode = new Node<T>;

	newNode->value = objPtr;

	// First Node in Queue. Assign all pointers to it.
	if(!head) {head = newNode; tail = newNode; _current = newNode;}

	// Append Node to end of Queue.
	else {

		tail->next = newNode;

		newNode->prev = tail;

		tail = newNode;
	}

};


/*
	*
	* Moves "_current" pointer a number of places ahead.
	* Params: Number of places to move in the Queue.
	*
*/
void Queue::jump(unsigned places) {

	for(unsigned i = 0; _current && i < places; ++i, _current = _current->next);
};


/*
	*
	* Returns Node in Queue that "_current" is pointing to.
	*
*/
Node<T> *Queue::current() {
	return _current;
};