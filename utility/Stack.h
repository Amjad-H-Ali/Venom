#ifndef STACK_H

#define STACK_H

template<typename T>

class Stack {

private:

	Node<T> *head;

	size_t size = 0;

	/*
	 +++++ Uses a given index to map to Node that is located at that index.  ++++++
	 +++++ Allows for accessing a specific node in O(log n) time complexity, ++++++
	 +++++ rather than the O(n) time linked-list are known to have.		     ++++++				 
	 */ 	

	Trie< Node<T> > indexMap;  

public:

	/*
	 +++++++ Main C'tor +++++++++++
	 */

	Stack();

	/*
	 ++++++ Insert ptr to object into stack. +++++++
	 */

	void push(const SharedPtr<T> &objPtr);

	/*
	 +++++++ Pop object off stack +++++++++++
	 */

	void pop();

	/*
	 +++++++ Pop all objects above given Node in stack +++++++++++
	 */

	void popTop(Node<T> *stackPtr);

	/*
	 +++++ Pop Multiple objects on stack +++++
	 */

	void popLoop(size_t amount);

	/*
	 +++++ Overloaded subscript operator to access data in linked-list based on index +++++
	 */

	Node<T> &operator [](size_t indx) const;

	/*
	 +++++ Returns top of stack without popping it off. Return type is SharedPtr to object of type T +++++++
	 */
	SmartPtr<T> &getTop() const;

}; // Stack

#endif