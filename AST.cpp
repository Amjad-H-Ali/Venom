#include "AST.h"


AST_Node::AST_Node(AST_SYMBOL type) 
	:type(type), next(nullptr)
{};


// Overload comparison operator to compare unique 
// symbols of AST_Node
bool AST_Node::operator==(AST_SYMBOL type) const {
	return (this->type == type);
};

// Accessors

AST_SYMBOL AST_Node::getType() const {
	return this->type;
};


char *AST_Node::getTypeName(AST_SYMBOL type) const {
	
 	switch(type) {

#define N(symbol) case symbol: return (char *)#symbol;
		AST_LIST(N)
#undef N

	}
};


AST_Node *AST_Node::getNext() const {
	return this->next;
};



// Setter

void AST_Node::setNext(AST_Node *ASTPtr) {
	this->next = ASTPtr;
};


