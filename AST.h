#pragma once

#include "Token.h"


// AST_LIST takes in a Macro(N).
// Each Macro has a signature(type),
// where type is a unique symbol of 
// an AST_Node.

// N: Unique Symbol of each Node in AST
#define AST_LIST(N) 			    \
	N(AST_ID)						\
	N(AST_IS)						\
	N(AST_STRING)					\
	N(AST_LIST)						\
	N(AST_FUNCTION)					

// All AST Symbols
#define N(symbol) symbol,
	enum AST_SYMBOL {AST_LIST(N)};
#undef N


// Base class for an AST_Node.
class AST {
private:

	// Unique Symbol for AST_Node.
	AST_SYMBOL type;

	// May or may not have value.
	// (LISTS and BLOCKS have value)
	AST *value;

	// May or may not have a name. 
	// (AST STRINGS and IDs have names)
	char *name;

public:

	AST(AST_SYMBOL type);

	// STRINGS and IDs will probably use this...
	// Since they have unique names.
	// This constructor highjacks the name from an 
	// expiring object of type Token.
	AST(AST_SYMBOL type, token::Token &&tokenObj);

	// LIST and BLOCKs will use this since they have 
	// a Linked-List of their own.
	AST(AST_SYMBOL type, AST *value);

	// Overload comparison operator to compare unique 
	// symbols of AST_Node
	bool operator==(AST_SYMBOL type) const;

	// ACCESSORS

	// AST_Node unique symbol
	AST_SYMBOL getType() const;

	// AST_Node unique String
	char *getTypeName(AST_SYMBOL type) const;

	char *getName() const;

	char *getValue() const;


	// // For BinaryOp
	// virtual AST_Node *getLeftOperand() const {return nullptr;};
	// virtual AST_Node *getRightOperand() const {return nullptr;};

	// // For List
	// virtual AST_Node *getValue() const {return nullptr;};

	// // For Function
	// virtual AST_Node *getParams() const {return nullptr;};
	// virtual AST_Node *getBlock() const {return nullptr;};

}; // AST



struct ASTNode {

	AST *value;

	ASTNode *next, *prev;

	ASTNode()
		:value(nullptr), next(nullptr), prev(nullptr)
	{};
};


