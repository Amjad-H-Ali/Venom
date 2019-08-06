#include "Dimension.h"



// Only inherited classes can call constructor
Dimension::Dimension() 
	:sp(0)
{}


/*
 +++++++ Inserts Token Ptr, that represents an open to a dimension, onto openStack +++++++++++
 */

void Dimension::insertOpen(Token &openingToken) {

	/*
	 ++++++ Insert ptr to Token into stack. ++++++++++
	 */

	openStack.push_back(&openingToken);

	++sp; // Increment stack pointer.

	++D;  // Increment Dimension

};

/*
 ++++++++ Sets Opening/Closing Tokens' matching Opening/Closing, and pops off Open from openStack ++++++++++
 */

void Dimension::insertClose(Token &closingToken) {

	/*
		*
		* This Token node closes a Dimension.
		*
	*/
	closingToken.setClosing(true);

	/*
		*
		* Assign Token's corresponding Open/Closing Token.
		*
	*/


	closingToken->setMatchingPair(openStack[sp-1]); // Setting closing Token's matching pair.

	openStack[sp-1]->setMatchingPair(closingToken); // Setting opening Token's matching pair.


	--sp; // Decrement stack pointer.

	--D;  // Decrement Dimension

};


// Accessor
unsigned Dimension::getD() const {
	return D;
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