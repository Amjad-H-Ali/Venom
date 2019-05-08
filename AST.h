#pragma once

// AST_LIST takes in a Macro(N).
// Each Macro has a signature(type),
// where type is a unique symbol of 
// an AST Node.

// N: Unique Symbol of each Node in AST
#define AST_LIST(N) 			    \
	N(AST_ID)						\
	N(AST_IS)						\
	N(AST_STRING)					\
	N(AST_LIST)

// All AST Symbols
#define N(symbol) symbol,
	enum AST_SYMBOL {AST_LIST(N)};
#undef N


class AST {
private:
	AST_SYMBOL type;
	AST *next;
public:
	AST(AST_SYMBOL type);
	AST_SYMBOL getType() const;
	AST *getNext() const;
	void setNext(AST *ASTPtr);
};