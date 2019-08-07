#ifndef PREPARSER_H

#define PREPARSER_H


class Preparser {

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
	auto isAtEndOfListOrBlock();

	/*
	 +++++ Recursively parses Block value that is used to construct a Block. +++++
	 +++++ A Block may be a body to a function, if statement, object, etc.   +++++
	 */

	std::vector<ast_t> &parseBlockValue();

public:

	/*
	 +++++ Main C'Tor +++++
	 */
	Preparser(const std::vector<Token> &tokensVec_Param);

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

}; // Preparser

#endif