#ifndef PREPARSER_H

#define PREPARSER_H


class Preparser {

private:

	const Queue<Token> *tokensQ;

	/*	
		*
		* Returns a callable that returns whether at end of a BLOCK or LIST range.
		* Lambda wrapped in function for reuse by LIST and BLOCK.
		*
	*/
	auto callFlagForListAndBlock(Token *tokenPtr);

public:

	Preparser(Queue<Token> *tokensQ);

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
	ast_t parseToken(const SharedPtr<Token> &tokenPtr);

}; // Preparser

#endif