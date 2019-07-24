/*
 ++++++ Generic Link to create Doubly Linked-Lists. ++++++
 */

#ifndef NODE_H

#define NODE_H

template<typename T>

struct Node {

	T *value;

	Node<T> *next, *prev;

	Node<T>()
		:value(nullptr), next(nullptr), prev(nullptr)
	{};

}; // Node

#endif