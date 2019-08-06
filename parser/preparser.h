#ifndef PREPARSER_H

#define PREPARSER_H


class Preparser {

private:

	const std::vector<Token> &tokensQ;

	/*
	 +++++ For iterating tokensQ +++++
	 */

	decltype(tokensQ.size()) curr;

	/*	
		*
		* Returns a callable that returns whether at end of a BLOCK or LIST range.
		* Lambda wrapped in function for reuse by LIST and BLOCK.
		*
	*/
	auto callFlagForListAndBlock(Token *tokenPtr);

public:

	/*
	 +++++ Main C'Tor +++++
	 */
	Preparser(const std::vector<Token> &tokensQ);

	/*
		*
		* Overload () operator. Creates a Queue of ast_t(s). 
		* Return: Lambda that takes in a conditional and parses tokensQ
		* and pushes parsed items into Queue of ast_t(s).
		*
	*/
	auto operator()();

	/*
		*
		* Parse token object and return an ast_t.
		*
	*/
	void parseToken(std::vector<ast_t> *astVec);

}; // Preparser

#endif