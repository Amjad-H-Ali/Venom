#include "Token.h"


// Destructor
Token::~Token() {
	// Delete Dynamically Allocated Array
	if(this->name != nullptr) delete [] this->name;
};

// Setter Methods
// Set name to character stream 
void Token::setName(char *name) {
	this->name = name; 
};

// Set type to appropriate symbol
void Token::setType(Symbol type) {
	this->type = type;
};

// Set next Token in the Linked List
void Token::setNext(Token *tokenPtr) {
	this->next = tokenPtr;
};
	
// Getter Methods
char *Token::getName() const {
	return this->name; 
};


Symbol Token::getType() const {
	return this->type;
};
	
Token *Token::getNext() const {
	return this->next;
};