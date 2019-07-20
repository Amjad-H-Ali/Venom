#include <iostream>
#include "Token.h"
#include <vector>

namespace utils = token::utility;
namespace tk = token;

/*
	*
	* Used to map input file text (C-Style strings)  
	* to their corresponding Symbol in O(n) time complexity.
	*
*/
Trie<Token::Symbol> *Token::mapToSymbol = new Trie<Token::Symbol>;


/*
	*
	* Load Trie with all Symbols.
	*
*/
#define T(symbol, name) Token::mapToSymbol->push(name, new token::Symbol(token::symbol));
	
	TOKEN_LIST(T)

#undef T




/*
	*
	* All Token symbols in string form for logging.
	*
*/
std::vector<std::string> Token::typeName;

Token::typeName.reserve(Token::NUM_OF_TOKENS);

/*
	*
	* Populate vector with all Token types in string form.
	*
*/
#define T(symbol, name) Token::typeName.emplace_back(#symbol);

	TOKEN_LIST(T)

#undef T



/*
	*
	* Overload operator to compare by symbol type.
	*
*/
bool Token::operator==(Symbol type) const {
	return (this->type == type);
};


	
/*
	*
	* Symbol type of Token.
	*
*/
Symbol Token::getType() const {
	return this->type;
};

/*
	*
	* Does this Token close off an array, block, or parameter list?
	*
*/
bool isClosing() const {
	return closing;
};
	
void setClosing(bool isClosing) {
	closing = isClosing;
};

/*
	*
	* Gets the Token's symbol type in string form.
	*
*/
static const std::string &Token::getTypeName() {

	return typeName[type];
};





