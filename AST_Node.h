#ifndef AST_NODE_H

#define AST_NODE_H

#include "AST.h"


// Base class of AST Nodes.
class AST_Node {

private:

	// Unique Symbol for AST_Node.
	ast::AST_SYMBOL type;

public:

	AST_Node(ast::AST_SYMBOL type);


	// Overload comparison operator to compare unique symbols
	bool operator==(ast::AST_SYMBOL type) const;

	// // SETTERS
	// virtual void setValue(ast::AST_SYMBOL type);
	// virtual void setValue(AST_List *params, AST_Block *body); // For AST_Func

	// ACCESSORS

	// AST_Node unique symbol
	ast::AST_SYMBOL getType() const;

	// AST_Node unique String
	char *getTypeName() const;

	// virtual void getValue() const {};

	

}; // AST_Node



#endif