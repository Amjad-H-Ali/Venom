#ifndef NODE_H

#define NODE_H

template<typename Ptr_t>

struct Node {

	Ptr_t value;

	Node<Ptr_t> *next, *prev;

	Node<Ptr_t>()
		:value(nullptr), next(nullptr), prev(nullptr)
	{};
};

#endif