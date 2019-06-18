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

/*
 	To create Linked-List of objects of different types. Why not use their parent since they all share the same
 	one? The reason: Due to some objects having different member variables than their siblings, overloaded 
 	set_value/get_value methods were needed. I did not want to add all the various methods as virtual methods 
 	in the Base class. Using std::variant allows me to call   
*/
typedef std::variant< std::nullptr_t, AST_STR *, AST_List *, AST_ID *, AST_Func *, AST_Block *, AST_BinOp *> astPtr_t;

// See AST.cpp
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


