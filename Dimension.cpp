#include "Dimension.h"


/*
	Each instance of Open class type represents a Token Node
	that opens up a new dimension, or in other words, the 
	start of a new LIST or BLOCK (ie. LBRACKET, SKINNY_ARROW).
*/
struct Dimension::Open {

	token::TokenNode *tn;

	// Node *next, *prev;
	Open *next;

	Open() 
		:tn(nullptr), next(nullptr)
	{std::cout << "Open Was Created!" << " Address: " << this << std::endl;}

	/* 
		Destructor: Deletes Chain of Open instances.
		Does not delete tn, as tn is a pointer to a
		Token Node that is in use by other components.
	*/
	~Open() {
		if(next) delete next;
		std::cout << "Open Was Deleted!" << " Address: " << this <<  std::endl;
		// next = nullptr, prev = nullptr, tn = nullptr;
		next = nullptr, tn = nullptr;

	}

};



/*
 	Each instance of this class will contain a Linked-List
	of Tokens that are either Opening or Closing a dimension 
	to a block or array. Each one of these instances will in 
	of itself be chained in a linked list with the purpose of
	representing separate arrays or blocks.
*/
// struct Dimension::NodeOfNodes {

// 	// Linked-List of Openings and 
// 	// Closings To Dimension.
// 	Node *opening,  *closing,  // Head Pointers.
// 	 	 *openingT, *closingT, // Tail pointers.
// 	 	 *matchingOpenNode; 
// 	NodeOfNodes *next, *prev;

// 	// Current opening Token Node.
// 	// Node *currentNode;

// 	NodeOfNodes()
// 		:
// 			opening(nullptr), closing(nullptr), openingT(nullptr), 
// 			closingT(nullptr), next(nullptr), prev(nullptr), matchingOpenNode(nullptr)
// 	{std::cout << "NodeOfNodes Was Created!" << " Address: " << this <<  std::endl;};


// 	~NodeOfNodes() {

// 		std::cout << "NodeOfNodes Was Deleted!" << " Address: " << this <<  std::endl;

// 		// Delete Linked-List of Nodes.
// 		if(opening) delete opening;
// 		if(closing) delete closing;

// 		// Delete chain of objects of NodeOfNodes Type.
// 		if(next) delete next;

// 		opening = nullptr, closing = nullptr,
// 		openingT = nullptr, closingT = nullptr,
// 		next = nullptr, prev = nullptr;
// 	}

// 	// Gets the corresponding open Node of a closing Node
// 	Node *getMatchingOpenNode() {
// 		Node *temp = matchingOpenNode;

// 		matchingOpenNode = matchingOpenNode->next;

// 		return temp;
// 	}

// 	// Updates current Node pointer to represent next opening Token Node.
// 	// NodeOfNodes *shift() {
// 	// 	// Return next NodeOfNodes.
// 	// 	if(!currentNode->prev)
// 	// 		return prev;

// 	// 	currentNode = currentNode->prev;

// 	// 	// Return current NodeOfNodes with updated current Node.
// 	// 	return this;
// 	// }


// };




Dimension::~Dimension() {
	// Delete Linked-List of NodeOfNodes.
	// if(head) delete head;

	// Deletes remaining Open objects, if any.
	if(openStack) delete openStack;

	// head = nullptr, tail = nullptr;

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

// Pushes to the stack.
void Dimension::push(Open *newOpen) {
	newOpen->next = openStack;

	openStack = newOpen; // Set Head
};

// Pops off the stack.
void Dimension::pop() {
	Open *temp = openStack;

	openStack = openStack->next;

	temp->next = nullptr;

	delete temp;
};

/*
	Instantiates an Open Type object that represents a
	Token Node who opens a LIST or BLOCK. Attaches the
	new instance to a Linked-List.

	Params: Token Node that opens a LIST or BLOCK
*/
void Dimension::insertOpen(token::TokenNode *tn) {

	// if(D == 0) { // New Block or Array

	// 	NodeOfNodes *newNodeOfNodes = new NodeOfNodes(); 

	// 	// Insert newNodeOfNodes into Linked-List.
	// 	// Start...

	// 	newNodeOfNodes->next = head; 

	// 	// Set neighbor prev (if exist) to point to newNodeOfNodes node.
	// 	if(head) newNodeOfNodes->next->prev = newNodeOfNodes;

	// 	else {
	// 		tail = newNodeOfNodes;    // It's the first (will be last) one, so set Tail.

	// 		// currentNodeOfNodes = newNodeOfNodes; // This NodeOfNodes must be the first (will be last) node.

	// 	}

	// 	head = newNodeOfNodes; // Set Head.

	// 	// Finish
	// }


	Open *newOpen = new Open();

	newOpen->tn = tn;

	// Insert "newOpen" into Linked-List (stack).
	push(newOpen);

	// newOpen->next = head->opening;

	

	// Set neighbor prev (if exist) to point to newOpen node.
	// if(head->opening) newOpen->next->prev = newOpen;

	// else {
		// head->openingT = newOpen; // It's the first (will be last) one, so set Tail.

		// Since first (will be last via LIFO) Node,
		// assign currentOpen to point to it.
		// head->currentNode = newOpen; 
	// }
	


	// head->opening = newOpen; // Set Head



	// head->matchingOpenNode = newOpen; // Set to first node in Linked-List.

	// Finish.

	D++; // Increment Dimension

};

/*
	Assigns the "closing" member of the Token Node to true
	and its "matchingPair" member to the corresponding open 
	Token Node. That corresponding open Token Node's 
	"matchingPair" member is set to the closing Token Node
	that is passed in. Lastly, pops off that opening node 
	from the stack of Open objects.

	Params: Token Node that closed a LIST or BLOCK
*/
void Dimension::insertClose(token::TokenNode *tn) {

	// This Token node closes a Dimension.
	tn->closing = true;

	// Assign nodes' corresponding open and closing node.

	tn->matchingPair = openStack->tn; // Setting closing Token Node's matching pair.

	openStack->tn->matchingPair = tn; // Setting opening token node's matching pair.


	// Pop Open object off stack as the open Token Node that it
	// represents has been matched with a closing Token Node.
	pop();


	// Node *matchingOpenNode = head->getMatchingOpenNode();

	// Assign closing node's corresponding open node.
	// tn->matchingPair = matchingOpenNode->tn;

	// Assign nodes' corresponding open and closing node.
	// tn->matchingPair = head->opening->tn; // Setting closing token node's matching pair.

	// tn->matchingPair->matchingPair = tn; // Setting opening token node's matching pair.


	// Delete opening node from Linked-List as it has been 
	// closed off. (Dimension has been closed).

	// head->opening->

	// Assign opening node's corresponding close node.
	// matchingOpenNode->tn->matchingPair = tn;

	// TODO. Throw error if head DNE.

	// Node *newClose = new Node();

	// std::cout << "A" << std::endl;
	
	// // Insert newClose into Linked-List.
	// // Start...

	// newClose->tn = tn;

	// std::cout << "B" << std::endl;

	// newClose->next = head->closing;

	// std::cout << "C" << std::endl;

	// // Set neighbor prev (if exist) to point to newClose node.
	// if(head->closing) newClose->next->prev = newClose;
	// else head->closingT = newClose; // It's the first (will be last) one, so set Tail.

	// std::cout << "D" << std::endl;


	// head->closing = newClose; // Set Head

	// std::cout << "E" << std::endl;


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