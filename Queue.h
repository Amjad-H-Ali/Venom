#ifndef QUEUE_H

#define QUEUE_H

#include "Node.h"

template<typename T>

class Queue {

private:

	Node<T> *head, 
			*tail, 
			*current;

public:

	Queue();

	/*
		*
		* Pushes a pointer to an object at the end of the Queue.
		*
	*/
	void push(T *objPtr);


	/*
		*
		* Moves "current" pointer a number of places ahead.
		* Params: Number of places to move in the Queue.
		*
	*/
	void jump(unsigned places);

	/*
		*
		* Returns Node in Queue that "current" is pointing to.
		*
	*/
	Node<T> *current();


}; // Queue

#endif