#include "Dimension.h"


/*
	Each instance of this class will contain a Token Node
	that either is an opening to a new dimension or closing
	of an existing one. Each instance will be chained together 
	in a Linked-List.
*/
struct Dimension::Node {

	token::TokenNode *tn;

	Node *next, *prev;

	Node() 
		:tn(nullptr), next(nullptr), prev(nullptr)
	{std::cout << "Node Was Created!" << " Address: " << this << std::endl;}

	/* 
		Destructor: Deletes Chain.
		Do not delete tn, as tn is pointer to TokenNode
		that is in use by other components.
	*/
	~Node() {
		if(next) delete next;
		std::cout << "Node Was Deleted!" << " Address: " << this <<  std::endl;
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
	 	 *openingT, *closingT, // Tail pointers.
	 	 *matchingOpenNode; 
	NodeOfNodes *next, *prev;

	// Current opening Token Node.
	// Node *currentNode;

	NodeOfNodes()
		:
			opening(nullptr), closing(nullptr), openingT(nullptr), 
			closingT(nullptr), next(nullptr), prev(nullptr), matchingOpenNode(nullptr)
	{std::cout << "NodeOfNodes Was Created!" << " Address: " << this <<  std::endl;};


	~NodeOfNodes() {

		std::cout << "NodeOfNodes Was Deleted!" << " Address: " << this <<  std::endl;

		// Delete Linked-List of Nodes.
		if(opening) delete opening;
		if(closing) delete closing;

		// Delete chain of objects of NodeOfNodes Type.
		if(next) delete next;

		opening = nullptr, closing = nullptr,
		openingT = nullptr, closingT = nullptr,
		next = nullptr, prev = nullptr;
	}

	// Gets the corresponding open Node of a closing Node
	Node *getMatchingOpenNode() {
		Node *temp = matchingOpenNode;

		matchingOpenNode = matchingOpenNode->next;

		return temp;
	}

	// Updates current Node pointer to represent next opening Token Node.
	// NodeOfNodes *shift() {
	// 	// Return next NodeOfNodes.
	// 	if(!currentNode->prev)
	// 		return prev;

	// 	currentNode = currentNode->prev;

	// 	// Return current NodeOfNodes with updated current Node.
	// 	return this;
	// }


};




Dimension::~Dimension() {
	// Delete Linked-List of NodeOfNodes.
	if(head) delete head;
	head = nullptr, tail = nullptr;

	std::cout<<"Dimension was Deleted" << " Address:: " << this << std::endl;
};



// const token::TokenNode *Dimension::getMatchingOpen() {
// 	// Store current state of NodeOfNodes.
// 	NodeOfNodes *currNodeOfNodes = currentNodeOfNodes;

// 	// Update to represent next opening Token Node.
// 	currentNodeOfNodes = currentNodeOfNodes->shift();

// 	std::cout << "CURRENT NODEOFNODE: " <<currentNodeOfNodes << std::endl;

// 	return currNodeOfNodes->currentNode->tn;
// };


// Insert Opening to a new Dimension into a Linked-List.
void Dimension::insertOpen(token::TokenNode *tn) {

	std::cout << "TN OPEN ADDRESS: " << tn << std::endl;

	if(D == 0) { // New Block or Array

		NodeOfNodes *newNodeOfNodes = new NodeOfNodes(); 

		// Insert newNodeOfNodes into Linked-List.
		// Start...

		newNodeOfNodes->next = head; 

		// Set neighbor prev (if exist) to point to newNodeOfNodes node.
		if(head) newNodeOfNodes->next->prev = newNodeOfNodes;

		else {
			tail = newNodeOfNodes;    // It's the first (will be last) one, so set Tail.

			// currentNodeOfNodes = newNodeOfNodes; // This NodeOfNodes must be the first (will be last) node.

		}

		head = newNodeOfNodes; // Set Head.

		// Finish
	}


	Node *newOpen = new Node();

	
	// Insert newOpen into Linked-List.
	// Start...

	newOpen->tn = tn;

	newOpen->next = head->opening;

	// Set neighbor prev (if exist) to point to newOpen node.
	if(head->opening) newOpen->next->prev = newOpen;

	else {
		head->openingT = newOpen; // It's the first (will be last) one, so set Tail.

		// Since first (will be last via LIFO) Node,
		// assign currentOpen to point to it.
		// head->currentNode = newOpen; 
	}
	


	head->opening = newOpen; // Set Head

	head->matchingOpenNode = newOpen; // Set to first node in Linked-List.

	// Finish.

	D++; // Increment Dimension

};



// Insert Closing to a new Dimension into a Linked-List.
void Dimension::insertClose(token::TokenNode *tn) {

	// This Token node closes a Dimension.
	tn->closing = true;


	Node *matchingOpenNode = head->getMatchingOpenNode();

	// Assign closing node's corresponding open node.
	tn->matchingPair = matchingOpenNode->tn;

	// Assign opening node's corresponding close node.
	matchingOpenNode->tn->matchingPair = tn;

	// TODO. Throw error if head DNE.

	Node *newClose = new Node();

	
	// Insert newClose into Linked-List.
	// Start...

	newClose->tn = tn;

	newClose->next = head->closing;

	// Set neighbor prev (if exist) to point to newClose node.
	if(head->closing) newClose->next->prev = newClose;
	else head->closingT = newClose; // It's the first (will be last) one, so set Tail.

	head->closing = newClose; // Set Head

	// if(D <= 0) throw error

	// Finish.

	D--; // Decrement Dimension

};


// Accessor
unsigned Dimension::getD() const {
	return this->D;
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