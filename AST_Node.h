#ifndef AST_NODE_H

#define AST_NODE_H


/*
	AST_LIST takes in a Macro(N).
	Each Macro has a signature(type),
	where type is a unique symbol of 
	an AST_Node.

	N: Unique Symbol of each Node in AST
*/

namespace ast {

#define AST_LIST(N) 			    \
	N(ID)							\
	N(ASSIGN)						\
	N(STR)							\
	N(LIST)							\
	N(BLOCK)						\
	N(FUNC)							

// All AST Symbols
#define N(symbol) symbol,
	enum AST_SYMBOL {AST_LIST(N)};
#undef N

}; // ast


// Base class of AST Nodes.
class AST_Node {

private:

	// Unique Symbol for AST_Node.
	ast::AST_SYMBOL type;

public:

	AST_Node(ast::AST_SYMBOL type);


	// Overload comparison operator to compare unique symbols
	bool operator==(ast::AST_SYMBOL type) const;

	// SETTERS
	virtual void setValue(ast::AST_SYMBOL type);


	// ACCESSORS

	// AST_Node unique symbol
	ast::AST_SYMBOL getType() const;

	// AST_Node unique String
	char *getTypeName() const;

	

}; // AST_Node



#endif