#include "Queue.h"
#include "Node.h"


/*
 ++++++ Main C'tor ++++++
 */

Queue::Queue()
	:head(nullptr), tail(nullptr), _current(nullptr)
{};


/*
 ++++++++++++ Inserts an object at end of the Queue.     ++++++++++++
 ++++++++++++ Params: variable number of arguments that  ++++++++++++
 ++++++++++++ will be forwarded to T object constructor. ++++++++++++
 ++++++++++++ Creates T objects emplace.				 ++++++++++++
 */	

template<typename ... Params>

void Queue::enqueue(Params&& ... params) {

	/*
	 ++++++ Create object of type T. Parameters' l-value/r-value is preserved while passing to T's C'tor  +++++++
	 ++++++ Pass address of T object to Node, which will store it as a SharedPtr.                         +++++++
	*/
	Node<T> *newNode = new Node<T>(new T(std::forward<Params>(params)...));

	
	/*
	 +++++++ First Node in Queue. Assign all pointers to it. +++++++++
	 */

	if(!head) {head = newNode; tail = newNode; _current = newNode;}

	/*
	 +++++++ Append Node to Queue. +++++++++
	 */

	else {

		tail->next = newNode;

		newNode->prev = tail;

		tail = newNode;
	}

};


/*
 ++++++++ Moves "_current" pointer a number of places ahead. ++++++++++
 ++++++++ Params: Number of places to move in the Queue.     ++++++++++
 */

void Queue::jump(unsigned places) {

	for(unsigned i = 0; _current && i < places; ++i, _current = _current->next);
};


/*
 ++++++ Returns Ptr to current object in Queue +++++++
 */

SharedPtr<T> &Queue::current() const {
	return _current->value;
};


/*
 ++++++ Returns Ptr to last object in Queue +++++++
 */

SharedPtr<T> &Queue::end() const {

	return tail->value;
};