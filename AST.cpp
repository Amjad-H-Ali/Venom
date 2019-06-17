#include "AST.h"


template<typename ... Params> struct NotOperatorOverloads : Params ... {using Params::operator() ...;};
template<typename ... Params> NotOperatorOverloads(Params ...) -> NotOperatorOverloads<Params ... >;

bool operator!(astPtr_t astPtrType) {

	return std::visit(NotOperatorOverloads {
		[](auto) {return false;},
		[](std::nullptr_t) {return true;}
	}, astPtrType);
};


AST::AST()
	:node(nullptr), next(nullptr), prev(nullptr)
{};