#include "Token.h"

using utils = Token::Utility;

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


bool utils::isMatch(char *s1, char *s2) {
	int indx = 0;
	while(s1[indx] == s2[indx]) {
		if(s1[indx] == s2[indx] == '\0') return true;
		indx++;
	}
	return false;
};

// Utiltiy Functions To Help Determine Type of Tokens
bool utils::isIF(char *stream) {
	return isMatch(stream, "if");
};				
bool utils::isEQ(char *stream) {
	return isMatch(stream, "=");
};				
bool utils::isBAR(char *stream) {
	return isMatch(stream, "|");
};			
bool utils::isEQEQ(char *stream) {
	return isMatch(stream, "==");
};			
bool utils::isELSE(char *stream) {
	return isMatch(stream, "else");
};			
bool utils::isCOMMA(char *stream) {
	return isMatch(stream, ",");
};		
bool utils::isSTRING(char *stream) {
	
};		
bool utils::isOUTPUT(char *stream) {
	return isMatch(stream, "output");
};	
bool utils::isBACKTICK(char *stream) {
	return isMatch(stream, "`");
};	
bool utils::isIDENTIFIER(char *stream) {

};
bool utils::isSKINNYARROW(char *stream) {
	return isMatch(stream, "->");
};