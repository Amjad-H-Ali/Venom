#include <iostream>
#include "Token.h"

namespace utils = token::utility;
namespace tk = token;


// Destructor
tk::Token::~Token() {
	// Delete Dynamically Allocated Array
	if(this->name != nullptr) delete [] this->name;
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

// Set next Token in the Linked List
void tk::Token::setNext(Token *tokenPtr) {
	this->next = tokenPtr;
};
	
// Getter Methods
char *tk::Token::getName() const {
	return this->name; 
};


tk::Symbol tk::Token::getType() const {
	return this->type;
};
	
tk::Token *tk::Token::getNext() const {
	return this->next;
};



// Utility function that compares two strings
bool utils::isMatch(char *s1, char *s2) {
	std::cout << "isMatch got called"  << s1 << ' '<< s2 << std::endl;
	if(s1 && s2) {
		int indx = 0;
		while(s1[indx] == s2[indx]) {
			if(s1[indx]== '\0' && s2[indx] == '\0') return true;
			indx++;
		}
	}		
	return false;
};


bool utils::isIF(char *stream) {
	std::cout << "isIF got called" << std::endl;
	return isMatch(stream,(char *) "if");
};				
bool utils::isEQ(char *stream) {
	std::cout << "isEQ got called" << std::endl;
	return isMatch(stream,(char *) "=");
};				
bool utils::isBAR(char *stream) {
	std::cout << "isBAR got called" << std::endl;
	return isMatch(stream,(char *) "|");
};			
bool utils::isEQEQ(char *stream) {
	std::cout << "isEQEQ got called" << std::endl;
	return isMatch(stream,(char *) "==");
};			
bool utils::isELSE(char *stream) {
	std::cout << "isELSE got called" << std::endl;
	return isMatch(stream,(char *) "else");
};			
bool utils::isCOMMA(char *stream) {
	std::cout << "isCOMMA got called" << std::endl;
	return isMatch(stream,(char *) ",");
};		
bool utils::isSTRING(char *stream) {
	std::cout << "isSTRING got called" << std::endl;
	
};		
bool utils::isOUTPUT(char *stream) {
	std::cout << "isOUTPUT got called" << std::endl;
	return isMatch(stream,(char *) "output");
};	
bool utils::isBACKTICK(char *stream) {
	std::cout << "isBACKTICK got called" << std::endl;
	return isMatch(stream,(char *) "`");
};	
bool utils::isIDENTIFIER(char *stream) {
	std::cout << "isIDENTIFIER got called" << std::endl;
	
};
bool utils::isSKINNYARROW(char *stream) {
	std::cout << "isSKINNYARROW got called" << std::endl;
	return isMatch(stream,(char *) "->");
};