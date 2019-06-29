#ifndef PREPARSER_H

#define PREPARSER_H

#include "AST.h"    // For astPtr_t
#include "Token.h"
#include "Queue.h"



// Alias for const token::TokenNode *
// typedef const token::TokenNode *tNode;


class Preparser {

private:

	Queue<Token *> *unParsedTokens;

	/*	
		*
		* Returns a callable that returns whether if at end of BLOCK or LIST range.
		* Lambda wrapped in function for reuse by LIST and BLOCK.
		*
	*/
	auto callFlagForListAndBlock(Token *tokenPtr);

public:

	Preparser(Queue<Token *> *unParsedTokens);

	/*
		*
		* Overload () operator. Creates a Queue of astPtr_t(s). 
		* Return: Lambda that takes in a conditional and parses Queue of tokenPtr(s)
		* and pushes parsed items into Queue of astPtr_t(s).
		*
	*/
	auto operator()();

	/*
		*
		* Parse token object and return an astPtr_t.
		*
	*/
	astPtr_t parseToken(Token *tokenPtr);

}; // Preparser

#endif