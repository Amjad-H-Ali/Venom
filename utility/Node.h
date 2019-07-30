/*
 ++++++ Generic Node to create Doubly Linked-Lists. ++++++
 */

#ifndef NODE_H

#define NODE_H

template<typename T>

struct Node {

	/*
	 +++++++ Ptr to actual value. Not just any ptr though (See SharedPtr.h). ++++++++++++
	 +++++++ In the case of  
	 */

	SharedPtr<T> value;

	Node<T> *next, *prev;

	/*
	 +++++++ Main C'tor. Takes in ptr to init data member named "value" . ++++++++
	 */

	Node<T>(T *ObjPtr = nullptr)

		:value(ObjPtr), next(nullptr), prev(nullptr)
	{}

	/*
	 +++++++ C'tor that takes in SharedPtr to copy. Always calls SharedPtr Copy C'tor ++++++++
	 */

	Node<T>(const SharedPtr<T>& ptrObj) // TODO: MAKE this Universal.

		:value(ptrObj), next(nullptr), prev(nullptr)
	{}


}; // Node

#endif