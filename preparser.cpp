#include "Preparser.h"
#include "Queue.h"
#include "Token.h"
#include "AST.h"		// For astPtr_t
#include "AST_BinOp.h"
#include "AST_List.h"
#include "AST_Block.h"
#include "AST_STR.h"
#include "AST_ID.h"
#include <utility>		// For move()




// namespace utils = preparser::utility;


Preparser::Preparser(Queue<Token> *tokensQ)
	:tokensQ(tokensQ)
{};



/*	
	*
	* Returns a callable that returns whether if at end of BLOCK or LIST range.
	* Lambda wrapped in function for reuse by LIST and BLOCK.
	*
*/
auto Preparser::callFlagForListAndBlock(Token *tokenPtr) {

	return [tokenPtr, tokensQ] {

		return (

			tokenPtr->matchingCloseToken != tokensQ->current();
		);
	};
};


/*
	*
	* Overload () operator. Creates a Queue of astPtr_t(s). 
	* Return: Lambda that takes in a conditional and parses Queue of tokenPtr(s)
	* and pushes parsed items into Queue of astPtr_t(s).
	*
*/
auto Preparser::operator()() {

	Queue<astPtr_t> *parsedAst = new Queue<astPtr_t>;

	/*
		*
		* callableFlag: conditional to know when to stop iterating through
		* tokensQ member variable.
		*
	*/
	return [](auto callableFlag) {

		while(callableFlag()) {

			/*
				*
				* Parse token and receive astPtr_t.
				*
			*/
			astPtr_t parsedAstPtr = parseToken(tokensQ->current());

			parsedAst->push(parsedAstPtr); 

			/*
				*
				* Move "_current" pointer one step ahead.
				*
			*/
			tokensQ->jump(1); 
		};

		return parsedAst;
	};
};


/*
	*
	* Parse token object and return an astPtr_t.
	*
*/
astPtr_t Preparser::parseToken(Token *tokenPtr) {


	if(*tokenPtr == token::ID)

		/*
			*
			* Steal Identifier name from token object.
			*
		*/
		return new AST_ID(ast::ID, std::move(*tokenPtr));

	/*
		*
		* Start to BLOCK.
		*
	*/
	if(*tokenPtr == token::ARROW) {

		tokensQ->jump(1);

		/*
			*
			* Call to this Functor.
			* Returns a Lambda that parses the tokensQ data member .
			*
		*/
		auto parseBlock = (*this)();

		/*
			*
			* Conditional for parsing the range of tokens that is the Block.
			*
		*/
		auto callFlag = callFlagForListAndBlock(tokenPtr);

		/*
			*
			* Recursively parsing block. 
			*
		*/
		return new AST_BLOCK(ast::BLOCK, parseBlock(callFlag));
	};


	else if(*tokenPtr == token::IS)

		return new AST_BinOp(ast::ASSIGN);


	/*
		*
		* For array LIST and function parameter LIST.
		*
	*/
	else if(*tokenPtr == token::LBRACKET || (*tokenPtr == token::BAR && !tokenPtr->closing)) {

		tokensQ->jump(1);

		/*
			*
			* Call to this Functor.
			* Returns a Lambda that parses the tokensQ data member .
			*
		*/
		auto parseList = (*this)();

		/*
			*
			* Conditional for parsing the range of tokens that is the List.
			*
		*/
		auto callFlag = callFlagForListAndBlock(tokenPtr); 

		return new AST_List(ast::LIST, parseList(callFlag));

	};

	else if(*tokenPtr == token::STRING)

		/*
			*
			* Steal STRING value from token object.
			*
		*/
		return new AST_STR(ast::STR, std::move(*tokenPtr));

	return nullptr;

}; // parserToken








