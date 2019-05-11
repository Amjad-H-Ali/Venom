#include "AST.h"

#include <iostream>

AST_Node::AST_Node(AST_SYMBOL type) 
	:type(type), next(nullptr)
{};

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


