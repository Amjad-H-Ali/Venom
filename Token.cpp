#include <iostream>
#include "Token.h"

namespace utils = token::utility;
namespace tk = token;


// Destructor
tk::Token::~Token() {
	// Delete Dynamically Allocated Array
	if(this->name != nullptr) delete [] this->name;
};

// Overload == operator to compare symbol types.
bool tk::Token::operator==(Symbol type) {
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

// Set next Token in the Linked List
void tk::Token::setNext(Token *tokenPtr) {
	this->next = tokenPtr;
};

// Set previous Token in Linked List.
void tk::Token::setPrev(Token *tokenPtr) {
	this->prev = tokenPtr;
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
	
tk::Token *tk::Token::getNext() const {
	return this->next;
};

tk::Token *tk::Token::getPrev() const {
	return this->prev;
};

char *tk::Token::getTypeName() const {
	return this->typeName;
};



// Utility function that compares two strings
bool utils::isMatch(char *s1, char *s2) {
	if(s1 && s2) {
		int indx = 0;
		while(s1[indx] == s2[indx]) {
			std::cout << s1[indx] << ' ' << s2[indx] << std::endl;
			if(s1[indx]== '\0' && s2[indx] == '\0') return true;
			indx++;
		}
	}		
	return false;
};


bool utils::isIF(char *stream) {
	return isMatch(stream,(char *) "if");
};				
bool utils::isEQ(char *stream) {
	return isMatch(stream,(char *) "=");
};				
bool utils::isBAR(char *stream) {
	return isMatch(stream,(char *) "|");
};			
bool utils::isEQEQ(char *stream) {
	return isMatch(stream,(char *) "==");
};			
bool utils::isELSE(char *stream) {
	return isMatch(stream,(char *) "else");
};			
bool utils::isCOMMA(char *stream) {
	return isMatch(stream,(char *) ",");
};		
bool utils::isOUTPUT(char *stream) {
	return isMatch(stream,(char *) "output");
};	
bool utils::isBACKTICK(char *stream) {
	return isMatch(stream,(char *) "`");
};	

bool utils::isSKINNYARROW(char *stream) {
	return isMatch(stream,(char *) "->");
};