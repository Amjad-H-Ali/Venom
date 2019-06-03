#ifndef DIMENSION_H

#define DIMENSION_H

#include "Token.h"

#include <iostream>

class Dimension {

protected: 

	/*
		Each instance of this class will contain a Token Node
		that either is an opening to a new dimension or closing
		of an existing one. Each instance will be chained together 
		in a Linked-List.
	*/
	struct Node {

	const token::TokenNode *tn;

	Node *next, *prev;
	Node() 
		:tn(nullptr), next(nullptr), prev(nullptr)
	{std::cout << "Node Was Created!" << std::endl;}

	/* 
		Destructor: Deletes Chain.
		Do not delete tn, as tn is pointer to TokenNode
		that is in use by other components.
	*/
	~Node() {
		if(next) delete next;
		std::cout << "Node Was Deleted!" << std::endl;
		next = nullptr, prev = nullptr, tn = nullptr;
	}
};

	/*
	 	Each instance of this class will contain a Linked-List
		of Tokens that are either Opening or Closing a dimension 
		to a block or array. Each one of these instances will in 
		of itself be chained in a linked list with the purpose of
		representing separate arrays or blocks.
	*/
	struct NodeOfNodes {
	// Linked-List of Openings and 
	// Closings To Dimension.
	Node *opening,  *closing,  // Head Pointers.
		 *openingT, *closingT; // Tail pointers.

	NodeOfNodes *next, *prev;

	NodeOfNodes()
		:
			opening(nullptr), closing(nullptr), openingT(nullptr),
			closingT(nullptr), next(nullptr), prev(nullptr)
	{std::cout << "NodeOfNodes Was Created!" << std::endl;};


	~NodeOfNodes() {
		std::cout << "NodeOfNodes Was Deleted!" << std::endl;
		// Delete Linked-List of Nodes.
		if(opening) delete opening;
		if(closing) delete closing;

		// Delete chain of objects of NodeOfNodes Type.
		if(next) delete next;

		opening = nullptr, closing = nullptr,
		openingT = nullptr, closingT = nullptr,
		next = nullptr, prev = nullptr;
	}
};

	NodeOfNodes *head; // Head Pointer.
	NodeOfNodes *tail; // Tail Pointer

	// Dimension
	unsigned int D = 0;




	// Only inherited classes can call constructor
	Dimension()
		:head(nullptr), tail(nullptr)
	{};

public:

	// Overload operators

	bool operator==(int i)  const;

	bool operator<=(int i)  const;

	bool operator>=(int i)  const;

	bool operator<(int i)   const;

	bool operator>(int i)   const;

	unsigned operator>>(unsigned &i)  const;
	

}; // Dimension



#endif