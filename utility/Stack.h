#ifndef STACK_H

#define STACK_H

template<typename T>

class Stack {

private:

	Node<T> *head;

public:

	/*
	 +++++++ Main C'tor +++++++++++
	 */

	Stack();

	/*
	 ++++++ Insert ptr to object into stack. +++++++
	 */

	void Stack::push(const SharedPtr<T> &objPtr);

	/*
	 +++++++ Pop object off stack +++++++++++
	 */

	void pop();

}; // Stack

#endif