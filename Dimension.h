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
	struct Node;

	/*
	 	Each instance of this class will contain a Linked-List
		of Tokens that are either Opening or Closing a dimension 
		to a block or array. Each one of these instances will in 
		of itself be chained in a linked list with the purpose of
		representing separate arrays or blocks.
	*/
	struct NodeOfNodes;



	NodeOfNodes *head; // Head Pointer.
	NodeOfNodes *tail; // Tail Pointer

	NodeOfNodes *currentNodeOfNodes;

	// Dimension
	unsigned int D = 0;


	// Only inherited classes can call constructor
	Dimension()
		:head(nullptr), tail(nullptr), currentNodeOfNodes(nullptr)
	{};

	~Dimension();

public:

	const token::TokenNode *getCurrentOpen();


	// Insert Opening to a new ArrayDimension into a Linked-List.
	void insertOpen(const token::TokenNode *tn);

	// Insert Closing to a new ArrayDimension into a Linked-List.
	void insertClose(token::TokenNode *tn);

	// Accessor
	unsigned getD() const;


	// Overload operators

	bool operator==(int i)  const;

	bool operator<=(int i)  const;

	bool operator>=(int i)  const;

	bool operator<(int i)   const;

	bool operator>(int i)   const;

	unsigned operator>>(unsigned &i)  const;
	

}; // Dimension



#endif