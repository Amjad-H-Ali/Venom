#include <iostream>
#include "Token.h"
/*
 +++++ Array of const char *, which is all Token symbols in string form +++++
 */

#define T(symbol, name) #symbol,

   const char *Token::typeName[NUM_OF_TOKENS] = {TOKEN_LIST(T)};

#undef T



/*
	----------------
	  Constructors
	----------------
*/

/*
	*
	* IDENTIFIER and STRING Constructor.
	*
*/
Token::Token(const std::string &stream, Symbol symType) 
	:value(stream), type(symType), closing(false)
{}

/*
	*
	* Constructor for Everything else like keywords, operators, etc,
	*
*/
Token::Token(Symbol symType)

	:type(symType), closing(false)
{}


/*
	------------------
	  Getter methods
	------------------

*/



/*
	*
	* Gets the Token's symbol type in string form.
	*
*/
const char *Token::getTypeName() const {

	return typeName[type];
};

/*
	*
	* Does this Token close off an array, block, or parameter list?
	*
*/
bool Token::isClosing() const {
	return closing;
};

std::vector<Token>::size_type Token::getMatchingPair() const {
	return matchingPair;
}; 

/*
 +++++ For Token::STRING or Token::ID Tokens. Everything else returns nullptr +++++
 */
std::string &Token::getValue(){

	return value;
}


/*
	------------------
	  Setter methods
	------------------

*/

void Token::setClosing(bool isClosing) {
	closing = isClosing;
};



void Token::setMatchingPair(std::vector<Token>::size_type otherPairIndx) {
	matchingPair = otherPairIndx;
};

/*
	------------------------
	  Overloaded Operators
	------------------------

*/


/*
	*
	* Overload operator to compare by symbol type.
	*
*/
bool Token::operator==(Symbol typeToCompare) const {
	return (type == typeToCompare);
};
