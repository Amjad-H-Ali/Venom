#include "Token.h"


void Token::setName(char *name) {
	this->name = name; 
};


void Token::setType(Symbol type) {
	this->type = type;
};

void Token::setNext(Token *tokenPtr) {
	this->next = tokenPtr;
};
	

char *Token::getName() const {
	return this->name; 
};


Symbol Token::getType() const {
	return this->type;
};
	
Token *Token::getNext() const {
	return this->next;
};