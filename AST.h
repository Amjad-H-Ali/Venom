#ifndef AST_H

#define AST_H

#include <iostream>
#include <variant>
 

// Forward
class AST_STR; 
class AST_List; 
class AST_ID; 
class AST_Func; 
class AST_Block; 
class AST_BinOp;

typedef std::variant< std::nullptr_t, AST_STR *, AST_List *, AST_ID *, AST_Func *, AST_Block *, AST_BinOp *> astPtr_t;

extern bool operator!(astPtr_t astPtrType);

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


// extern astPtr_t;

struct AST {

	astPtr_t node;

	AST *next, *prev;

	AST();
		

	// Overload operator.
	// bool operator==(ast::AST_SYMBOL type) {
	// 	return this->node == type;
	// };
};

#endif


