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

	

	/*
		A stack of objects of type Open. This is where open Token 
		Nodes, waiting to be paired with a closing Token Node, live.
		Every time the "insertClose" method is invoked, an object is 
		popped off the stack.
	*/
	Node<Token> *openStack;

	// Pushes to the stack.
	void push(Node<Token> *newOpen);

	// Pops off the stack.
	void pop();

	/*
	 	Each instance of this class will contain a Linked-List
		of Tokens that are either Opening or Closing a dimension 
		to a block or array. Each one of these instances will in 
		of itself be chained in a linked list with the purpose of
		representing separate arrays or blocks.
	*/
	// struct NodeOfNodes;



	// NodeOfNodes *head; // Head Pointer.
	// NodeOfNodes *tail; // Tail Pointer



	// NodeOfNodes *currentNodeOfNodes;

	// Dimension
	unsigned int D = 0;



	// Only inherited classes can call constructor
	Dimension()
		:openStack(nullptr)
	{};

	~Dimension();

public:

	// const token::TokenNode *getMatchingOpen();


	/*
		Instantiates an Open Type object that represents a
		Token Node who opens a LIST or BLOCK. Attaches the
		new instance to a Linked-List.

		Params: Token Node that opens a LIST or BLOCK
	*/
	void insertOpen(token::TokenNode *tn);

	/*
		Assigns the "closing" member of the Token Node to true
		and its "matchingPair" member to the corresponding open 
		Token Node. That corresponding open Token Node's 
		"matchingPair" member is set to this closing Token Node
		that is passed in. Lastly. pops off that opening node 
		from the stack of Open objects.

		Params: Token Node that closed a LIST or BLOCK
	*/
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