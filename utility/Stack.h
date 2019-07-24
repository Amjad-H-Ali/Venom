#ifndef STACK_H

#define STACK_H

template<typename T>

class Stack {

private:

	Node<T> *head;

public:

	Stack();

	/*
	 ++++++ Insert object into stack. +++++++
	 */
	
	void push(T *objPtr);

	void pop();

}; // Stack

#endif