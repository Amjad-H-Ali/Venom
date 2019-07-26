#ifndef QUEUE_H

#define QUEUE_H

#include "Node.h"

template<typename T>

class Queue {

private:

	Node<T> *head, 
			*tail, 
			*_current;

public:

	/*
	 ++++++ Main C'tor ++++++
	 */

	Queue();

	/*
	 ++++++++++++ Inserts an object at end of the Queue.     ++++++++++++
	 ++++++++++++ Params: variable number of arguments that  ++++++++++++
	 ++++++++++++ will be forwarded to T object constructor. ++++++++++++
	 ++++++++++++ Creates T objects emplace.				 ++++++++++++
	 */

	template<typename ... Params>

	void enqueue(Params&& ... params);


	/*
	 ++++++++ Moves "_current" pointer a number of places ahead. ++++++++++
	 ++++++++ Params: Number of places to move in the Queue.     ++++++++++
	 */

	void jump(unsigned places);

	/*
	 ++++++ Returns Ptr to current object in Queue +++++++
	 */

	SharedPtr<T> &current() const;

	/*
	 ++++++ Returns Ptr to last object in Queue +++++++
	 */

	SharedPtr<T> &end() const;


}; // Queue

#endif