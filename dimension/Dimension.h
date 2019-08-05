#ifndef DIMENSION_H

#define DIMENSION_H

#include "Token.h"

#include <iostream>

class Dimension {

protected: 


	/*
     +++++ Stack of ptrs to Token Objects that represent Openings to arrays, param lists, and blocks +++++++
	 */

	std::vector<Token *> openStack;

	/*
	 +++++ Stack "pointer" to current top ++++
	 */

	decltype(openStack.size()) sp;



	// Dimension
	unsigned int D = 0;



	// Only inherited classes can call constructor
	Dimension();


public:


	/*
	 +++++++ Inserts Token Ptr, that represents an open to a dimension, onto openStack +++++++++++
	 */

	void insertOpen(Token &openingToken);

	/*
	 ++++++++ Sets Opening/Closing Tokens' matching Opening/Closing, and pops off Open from openStack ++++++++++
	 */

	void Dimension::insertClose(Token &closingToken);

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