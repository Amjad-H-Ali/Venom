#ifndef PARSER_H

#define PARSER_H


class Parser {

private:

	const std::vector<Token> &tokensVec;

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
	auto Parser::endOfListAndBlockCallable();

	/*
	 +++++ Recursively parses Block or List value that is used to construct a Block +++++
	 +++++ or List. May be body to a function, param list, object, array, etc.      +++++
	 */

	std::vector<ast_t> &Parser::parseRange();

public:

	/*
	 +++++ Main C'Tor +++++
	 */
	Parser(const std::vector<Token> &tokensVec_Param);

	/*
		*
		* Overload () operator. Creates a vector of ast_t(s). 
		* Return: Lambda that takes in a conditional and parses tokensQ
		* and pushes parsed items into vector of ast_t(s).
		*
	*/
	auto operator()();

	/*
		*
		* Parse token object and return an ast_t.
		*
	*/
	void fillAstVecWithParsedToken(std::vector<ast_t> *astVecPtr);

}; // Parser

#endif