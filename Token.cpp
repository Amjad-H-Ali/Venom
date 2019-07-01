#include <iostream>
#include "Token.h"

namespace utils = token::utility;
namespace tk = token;

/*
	*
	* Used to map input file text (C-Style strings)  
	* to their corresponding Symbol in O(n) time complexity.
	*
*/
Trie<Token::Symbol *> *Token::mapToSymbol = new Trie<Token::Symbol *>;


/*
	*
	* Load Trie with all Symbols.
	*
*/

#define T(symbol, name) Token::mapToSymbol->push(name, new token::Symbol(token::symbol));
	
	TOKEN_LIST(T)

#undef T



// Destructor
tk::Token::~Token() {
	// Delete Dynamically Allocated Array
	if(this->name != nullptr) delete [] this->name;
};

// Overload == operator to compare symbol types.
bool tk::Token::operator==(Symbol type) const {
	return (this->type == type);
};

// Setter Methods
// Set name to character stream 
void tk::Token::setName(char *name) {
	this->name = name; 
};

// Set type to appropriate symbol
void tk::Token::setType(Symbol type) {
	this->type = type;
};

// Sets typeName to Symbol Type in String Form.
void tk::Token::setTypeName(char *typeName) {
	this->typeName = typeName;
};
	
// Getter Methods
char *tk::Token::getName() const {
	return this->name; 
};


tk::Symbol tk::Token::getType() const {
	return this->type;
};
	

char *tk::Token::getTypeName() const {
	return this->typeName;
};





