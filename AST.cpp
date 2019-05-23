#include "AST.h"


AST::AST(AST_SYMBOL type) 
	:type(type), name(nullptr), value(nullptr)
{};


// STRINGS and IDs will probably use this...
// Since they have unique names.
// This constructor highjacks the name from an 
// expiring object of type Token.
AST::AST(AST_SYMBOL type, token::Token &&tokenObj)
	:type(type), name(tokenObj.getName()), value(nullptr)
{tokenObj.setName();};


// LIST and BLOCKs will use this since they have 
// a Linked-List of their own.
AST::AST(AST_SYMBOL type, ASTNode *value)
	:type(type), value(value), name(nullptr)
{};

// Overload comparison operator to compare unique 
// symbols of AST_Node
bool AST::operator==(AST_SYMBOL type) const {
	return (this->type == type);
};

// Accessors

AST_SYMBOL AST::getType() const {
	return this->type;
};


char *AST::getTypeName(AST_SYMBOL type) const {
	
 	switch(type) {

#define N(symbol) case symbol: return (char *)#symbol;
		AST_LIST(N)
#undef N

	}
};


char *AST::getName() const {
	return name;
};

ASTNode *AST::getValue() const {
	return value;
};



