#include "AST_Node.h"


AST_Node::AST_Node(AST_SYMBOL type) 
	:type(type)
{};


// STRINGS and IDs will probably use this...
// Since they have unique names.
// This constructor highjacks the name from an 
// expiring object of type Token.
// AST::AST(AST_SYMBOL type, token::Token &&tokenObj)
// 	:type(type), name(tokenObj.getName()), value(nullptr)
// {tokenObj.setName();};


// LIST and BLOCKs will use this since they have 
// a Linked-List of their own.
// AST_Node::AST_Node(AST_SYMBOL type, ASTNode *value)
// 	:type(type), value(value), name(nullptr)
// {};

// Overload comparison operator to compare unique symbols 
bool AST_Node::operator==(AST_SYMBOL type) const {
	return (this->type == type);
};

// Accessors

AST_SYMBOL AST_Node::getType() const {
	return this->type;
};


char *AST_Node::getTypeName() const {
	
	switch(this->type) {

#define N(symbol) case symbol: return (char *)#symbol;
		AST_LIST(N)
#undef N

	}

};


// char *AST::getName() const {
// 	return name;
// };

// ASTNode *AST::getValue() const {
// 	return value;
// };



