#include "AST.h"
#include "AST_Node.h"
#include "AST_STR.h"
#include "AST_List.h"
#include "AST_ID.h"
#include "AST_Block.h"
#include "AST_BinOp.h"
#include "AST_Func.h"



/*
	The following allows for overload of the "Logical Not" operator to work 
	with astPtr_t (the std::variant declared in AST.h).

	Start:

	***

	
	"NotOperatorOverloads" is a templated struct that takes an arbitrary amount of types. 
	Search (variadic template<>). In this case, the types will be an arbitrary number of
	Lambdas (syntactic sugar for Functors). Our struct will inherit from each Lambda. 
	In this case, we are inheriting an operator() method from each Lambda. That is what
	is seen below in the first line right of the colon.
*/
template<typename ... Params> struct Overloads : Params ... {using Params::operator() ...;};

/*
	This is a deduction guide for the compiler. We are telling the compiler, "When you see this
	signature (The constructor call with an arbitrary number of parameters left of the colon), 
	deduce it as what is right of the colon (ie. NotOperatorOverloads(foo, bar, zoo) means
	NotOperatorOverloads<foo, bar, zoo>). This will instantiate an object that inherits from foo,
	bar, and zoo (which should be Lambdas). "
*/
template<typename ... Params> Overloads(Params ...) -> Overloads<Params ... >;

// Takes in the std::variant type as param.
bool operator!(astPtr_t astPtrType) {

	/*
		Our struct's constructor is being called with Lambdas passed as 
		arguments (This will then be deduced to what is above). Now
		"NotOperatorOverloads" is a functor with overloaded operator()s.
		So when std::visit calls our functor with the std::variant (astPtrType)
		passed as argument, we get the correct return value.
	*/
	return std::visit(Overloads {

		[](auto) {return false;},

		[](std::nullptr_t) {return true;}

	}, astPtrType);
};

/*
	***

	:END.
*/


AST::AST()
	:node(nullptr), next(nullptr), prev(nullptr)
{};



char* AST::getTypeName() {
	return std::visit(Overloads {

			[](auto n){return n->getTypeName();},

			[](std::nullptr_t){return (char *)"nullptr";}

		}, this->node);
};



AST *AST::getValueOfNode() {

	return std::visit(Overloads {

		[](AST_Block *block){return block->getValue();},

		[](AST_List *list){return list->getValue();},

		[](AST_Func *func){return func->getBody();},

		[](auto){return (AST *) nullptr;}

	}, this->node);
};

// Overload operator
bool AST::operator==(ast::AST_SYMBOL type) {

	return std::visit(Overloads {

		[type](auto astPtr) {return *astPtr == type;},

		[](std::nullptr_t){return false;}

	}, this->node);

};