#include "Dimension.h"




Dimension::~Dimension() {
	// Delete Linked-List of NodeOfNodes.
	// if(head) delete head;

	// Deletes remaining Open objects, if any.
	if(openStack) delete openStack;

	// head = nullptr, tail = nullptr;

	std::cout<<"Dimension was Deleted" << " Address:: " << this << std::endl;
};





/*
 +++++++ Inserts Token Ptr, that represents an open to a dimension, onto openStack +++++++++++
 */

void Dimension::insertOpen(const SmartPtr<Token> &tokenPtr) {

	/*
	 ++++++ Insert ptr to Token into stack. SharedPtr Cp C'tor called. ++++++++++
	 */

	openStack.push(tokenPtr);


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