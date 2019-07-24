#ifndef STACK_H

#define STACK_H

template<typename T>

class Stack {

private:

	Node<T> *head;

public:

	Stack();

	/*
	 ++++++ Insert ptr to object into stack. +++++++
	 */

	void Stack::push(const SharedPtr<Token> &objPtr);

	/*
	 +++++++ Pop object off stack +++++++++++
	 */
	
	void pop();

}; // Stack

#endif