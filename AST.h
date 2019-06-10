#ifndef AST_H

#define AST_H


// Forward Declaration
class AST_Node;

struct AST {

	AST_Node *node;

	AST *next, *prev;

	AST()
		:node(nullptr), next(nullptr), prev(nullptr)
	{};
};

#endif


