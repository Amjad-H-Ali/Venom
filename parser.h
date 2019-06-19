#ifndef PARSER_H

#define PARSER_H

#include "AST.h"

template<typename ... Types> struct AstOverloads : Types ... {using Types::operator() ...;};
template<typename ... Types> AstOverloads(Types ...) -> AstOverloads<Types ...>;



namespace parser {

	AST *_main(AST *astHead);

	template<typename ... Params>
	astPtr_t parse (AST *parent, Params&& ... params);
	astPtr_t  parseBlockContext(AST *parentOfBlock);
	AST_Block *parseBlock(AST_Block *block);

}; // parser


#endif