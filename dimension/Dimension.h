#ifndef DIMENSION_H

#define DIMENSION_H

#include <vector>
#include "../lexer/token/Token.h"

class Dimension {

protected: 


	/*
     +++++ Stack of ptrs to Token Objects that represent Openings to arrays, param lists, and blocks +++++++
	 */

	std::vector<std::vector<Token>::size_type> openStack;

	/*
	 +++++ Stack "pointer" to current top ++++
	 */

	decltype(openStack.size()) sp;



	// Only inherited classes can call constructor
	Dimension();


public:


	/*
	 +++++++ Inserts Token Ptr, that represents an open to a dimension, onto openStack +++++++++++
	 */

	void insertOpen(std::vector<Token> &tokensVec);

	/*
	 ++++++++ Sets Opening/Closing Tokens' matching Opening/Closing, and pops off Open from openStack ++++++++++
	 */

	void insertClose(std::vector<Token> &tokensVec);

	// Accessor
	unsigned getD() const;


	// Overload operators

	bool operator==(int i)  const;

	bool operator<=(int i)  const;

	bool operator>=(int i)  const;

	bool operator<(int i)   const;

	bool operator>(int i)   const;

	

}; // Dimension



#endif