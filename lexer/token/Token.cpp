#include <iostream>



/*
	*
	* Used to map input file text (C-Style strings)  
	* to their corresponding Symbol in O(1) time complexity.
	*
*/
Trie< Token::Symbol > Token::mapToSymbol;









/*
 +++++ Array of const char *, which is all Token symbols in string form +++++
 */

#define T(symbol, name) #symbol,

   const char *Token::typeName[NUM_OF_TOKENS] = {LIST(T)};

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
	:value(stream), type(symType), closing(false), matchingPair(nullptr)
{}

/*
	*
	* Constructor for Everything else like keywords, operators, etc,
	*
*/
Token::Token(Symbol symType)

	:value(nullptr), type(symType), closing(false), matchingPair(nullptr)
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
static const std::string &Token::getTypeName() {

	return typeName[type];
};

/*
	*
	* Does this Token close off an array, block, or parameter list?
	*
*/
bool isClosing() const {
	return closing;
};

SharedPtr<Token> &getMatchingPair() const {
	return matchingPair;
}; 


/*
	------------------
	  Setter methods
	------------------

*/

void setClosing(bool isClosing) {
	closing = isClosing;
};



void setMatchingPair(const SharedPtr<Token> &matchingPair) {
	matchingPair = matchingPair;
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
