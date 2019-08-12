#ifndef PARSER_H

#define PARSER_H

#include <vector>
#include "../lexer/token/Token.h"
#include "../ast/ast_t.h"

class Parser {

private:

	std::vector<Token> &tokensVec;

	decltype(tokensVec.size()) tokensVecLen;

	/*
	 +++++ For iterating tokensVec +++++
	 */

	decltype(tokensVec.size()) curr;

	/*	
		*
		* Returns a callable that returns whether at end of a BLOCK or LIST range.
		* Lambda wrapped in function for reuse by LIST and BLOCK.
		*
	*/
	decltype(auto) endOfListAndBlockCallable();

	/*
	 +++++ Recursively parses Block or List value that is used to construct a Block +++++
	 +++++ or List. May be body to a function, param list, object, array, etc.      +++++
	 */

	std::vector<ast_t> &parseRange();

	/*
	 +++++ Parse Token to an AST and Insert into Vector +++++
	 */
 	void fillAstVecWithParsedToken(std::vector<ast_t> *astVecPtr);

public:

	/*
	 +++++ Main C'Tor +++++
	 */
	Parser(std::vector<Token> &tokensVec_Param);

	/*
		*
		* Overload () operator. Creates a vector of ast_t(s). 
		* Return: Lambda that takes in a conditional and parses tokensQ
		* and pushes parsed items into vector of ast_t(s).
		*
	*/
	decltype(auto) operator()();


}; // Parser

#endif