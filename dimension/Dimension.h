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

	/*
     +++++ Stack of ptrs to Token Objects that represent Openings to arrays, param lists, and blocks +++++++
	 */

	Stack<Token> openStack;

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
	Dimension() {};

	~Dimension();

public:

	// const token::TokenNode *getMatchingOpen();


	/*
	 +++++++ Inserts Token Ptr, that represents an open to a dimension, onto openStack +++++++++++
	 */

	void insertOpen(const SmartPtr<Token> &tokenPtr);

	/*
	 ++++++++ Sets Opening/Closing Tokens' matching Opening/Closing, and pops off Open from openStack ++++++++++
	 */

	void Dimension::insertClose(SmartPtr<Token> &tokenPtr);

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