#include "AST.h"

AST_Node::AST_Node(AST_SYMBOL type) 
	:type(type), next(nullptr)
{
	switch(type) {

#define N(symbol) case symbol: this->typeName = (char *)#symbol;
		AST_LIST(N)
#undef N
	} 

};

// Accessors

AST_SYMBOL AST_Node::getType() const {
	return this->type;
};

char *AST_Node::getTypeName() const {
	return this->typeName;
};

AST_Node *AST_Node::getNext() const {
	return this->next;
};

// Setter

void AST_Node::setNext(AST_Node *ASTPtr) {
	this->next = ASTPtr;
};