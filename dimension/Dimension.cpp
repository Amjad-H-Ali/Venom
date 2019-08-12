#include "Dimension.h"



// Only inherited classes can call constructor
Dimension::Dimension() 
	:sp(0)
{}


/*
 +++++++ Inserts Token Ptr, that represents an open to a dimension, onto openStack +++++++++++
 */

void Dimension::insertOpen(std::vector<Token> &tokensVec) {

	decltype(tokensVec.size()) indxOfToken =  tokensVec.size() - 1;


	/*
	 ++++++ Insert ptr to Token into stack. ++++++++++
	 */

	openStack.push_back(indxOfToken);

	++sp; // Increment stack pointer (Dimension).


};

/*
 ++++++++ Sets Opening/Closing Tokens' matching Opening/Closing, and pops off Open from openStack ++++++++++
 */

void Dimension::insertClose(std::vector<Token> &tokensVec) {

	decltype(tokensVec.size()) indxOfToken =  tokensVec.size() - 1;


	/*
		*
		* This Token node closes a Dimension.
		*
	*/
	tokensVec[indxOfToken].setClosing(true);


	/*
		*
		* Assign Token's corresponding Open/Closing Token.
		*
	*/


	tokensVec[indxOfToken].setMatchingPair(openStack[sp-1]); // Setting closing Token's matching pair.

	tokensVec[openStack[sp-1]].setMatchingPair(indxOfToken); // Setting opening Token's matching pair.


	--sp; // Decrement stack pointer (Dimension).

};


// Accessor
unsigned Dimension::getD() const {
	return sp;
};



// Overload operators

bool Dimension::operator==(int i)  const {
	return (sp == i);
};

bool Dimension::operator<=(int i)  const {
	return (sp <= i);
};

bool Dimension::operator>=(int i)  const {
	return (sp >= i);
};

bool Dimension::operator<(int i)   const {
	return (sp < i);
};

bool Dimension::operator>(int i)   const {
	return (sp > i);
};

