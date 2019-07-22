#include "Dimension.h"




Dimension::~Dimension() {
	// Delete Linked-List of NodeOfNodes.
	// if(head) delete head;

	// Deletes remaining Open objects, if any.
	if(openStack) delete openStack;

	// head = nullptr, tail = nullptr;

	std::cout<<"Dimension was Deleted" << " Address:: " << this << std::endl;
};




// Pushes to the stack.
void Dimension::push(Node<Token> *newOpen) {
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
void Dimension::insertOpen(Token *tokenPtr) {


	Open *newOpen = new Open();

	newOpen->tokenPtr = tokenPtr;

	/*
		*
		* Insert "newOpen" into Linked-List (stack).
		*
	*/
	push(newOpen);

	

	++D; // Increment Dimension

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


	
	--D; // Decrement Dimension

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