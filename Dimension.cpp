#include "Dimension.h"
#include "Token.h"


/*
	Each instance of this class will contain a Token Node
	that either is an opening to a new dimension or closing
	of an existing one. Each instance will be chained together 
	in a Linked-List.
*/
struct Dimension::Node {

	const token::TokenNode *tn;

	Node *next, *prev;
	Node() 
		:next(nullptr), prev(nullptr)
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
struct Dimension::NodeOfNodes {
	// Linked-List of Openings and 
	// Closings To Dimension.
	Node *opening,  *closing,  // Head Pointers.
		 *openingT, *closingT; // Tail pointers.

	NodeOfNodes *next, *prev;

	NodeOfNodes()
		:
			opening(nullptr), closing(nullptr), openingT(nullptr),
			closingT(nullptr), next(nullptr), prev(nullptr)
	{};


	~NodeOfNodes() {
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


// Deletes Linked-List properties.
Dimension::~Dimension() {
	std::cout << "Dimension Was Deleted!" << std::endl;

	// Delete Linked-List of NodeOfNodes.
	if(head) delete head;
	head = nullptr, tail = nullptr;
}

// Insert Opening of a new Dimension into Node.
void Dimension::insertOpen(const token::TokenNode *tn) {

	Node *newOpen = new Node();

	newOpen->tn = tn;

	newOpen->next = opening;

	// Set neighbor prev to point to newOpen node.
	if(opening) newOpen->next->prev = newOpen;
	else openingT = newOpen; // Set Tail pointer to Last Node.

	opening = newOpen;

	D++; // Increment Dimension
};

// Insert Closing of a Dimension into Node.
void Dimension::insertClose(const token::TokenNode *tn) {

	Node *newClose = new Node();

	newClose->tn = tn;

	newClose->next = closing;

	// Set neighbor prev to point to newClose node.
	if(closing) newClose->next->prev = newClose;
	else closingT = newClose; // Set Tail pointer to Last Node.

	closing = newClose;

	// if(D <= 0) throw error
	D--; // Decrement Dimension
};


// Overload operators

bool Dimension::operator==(int i)  const {
	return (D == i);
};

bool Dimension::operator<=(int i)  const {
	return (D <= i);
};

bool Dimension::operator>=(int i)  const {
	return (D >= i);
};

bool Dimension::operator<(int i)   const {
	return (D < i);
};

bool Dimension::operator>(int i)   const {
	return (D > i);
};

unsigned Dimension::operator>>(unsigned &i)  const {
	i = D;

	return i;
};




