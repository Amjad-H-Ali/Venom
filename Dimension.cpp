#include "Dimension.h"


/*
	Each instance of Open class type represents a Token Node
	that opens up a new dimension, or in other words, the 
	start of a new LIST or BLOCK (ie. LBRACKET, SKINNY_ARROW).
*/
struct Dimension::Open {

	Token *tokenPtr;

	// Node *next, *prev;
	Open *next;

	Open() 
		:tn(nullptr), next(nullptr)
	{}

	/* 
		Destructor: Deletes Chain of Open instances.
		Does not delete tn, as tn is a pointer to a
		Token Node that is in use by other components.
	*/
	~Open() {
		if(next) delete next;
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
	*
	* Matches the closing Token object with its corresponding opening Token
	* and vice versa.
	*
*/
void Dimension::insertClose(Token *tokenPtr) {

	/*
		*
		* This Token node closes a Dimension.
		*
	*/
	tokenPtr->setClosing(true);

	/*
		*
		* Assign Token's corresponding Open/Closing Token.
		*
	*/
	tokenPtr->setMatchingPair(openStack->tokenPtr); // Setting closing Token's matching pair.

	openStack->tokenPtr->setMatchingPair(tokenPtr); // Setting opening Token's matching pair.

	/*
		*
		* Pop the Open object off stack since Token object that it
		* represents has been matched with a closing Token object.
		*
	*/
	pop();


	/*
		*
		* Decrement Dimension.
		*
	*/
	D--;  

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