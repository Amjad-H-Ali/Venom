#include <iostream>
#include <utility>		// For move()
#include "preparser.h"

namespace utils = preparser::utility;

class Preparser {

private:
	Queue<Token *> *unParsedTokens;

	/*	
		*
		* Returns a callable that returns whether if at end of BLOCK or LIST range.
		* Lambda wrapped in function for reuse by LIST and BLOCK.
		*
	*/
	auto callFlagForListAndBlock(Token *tokenPtr) {

		return [tokenPtr, unParsedTokens] {

				return (

					tokenPtr->matchingCloseToken != unParsedTokens->current()->value;
				);
			};
	};

public:

	Preparser(Queue<Token *> *unParsedTokens)
		:unParsedTokens(unParsedTokens)
	{};

	/*
		*
		* Overload () operator. Creates a Queue of astPtr_t(s). 
		* Return: Lambda that takes in a conditional and parses Queue of tokenPtr(s)
		* and pushes parsed items into Queue of astPtr_t(s).
		*
	*/

	auto operator()() {

		Queue<astPtr_t> *parsedAst = new Queue<astPtr_t>;

		/*
			*
			* callableFlag: conditional to know when to stop iterating through
			* unParsedTokens member variable.
			*
		*/
		return [](auto callableFlag) {

			while(callableFlag()) {

				/*
					*
					* Parse token and receive astPtr_t.
					*
				*/
				astPtr_t parsedAstPtr = parseToken(unParsedTokens->current()->value);

				parsedAst->push(parsedAstPtr); 

				/*
					*
					* Move "_current" pointer one step ahead.
					*
				*/
				unParsedTokens->jump(1); 
			};

			return parsedAst;
		};
	};

	/*
		*
		* Parse token object and return an astPtr_t.
		*
	*/
	astPtr_t parseToken(Token *tokenPtr) {


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

			unParsedTokens->jump(1);

			/*
				*
				* Call to this Functor.
				* Returns a Lambda that parses the unParsedTokens data member .
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

		else if(*tokenPtr == token::LBRACKET || (*tokenPtr == token::BAR && !tokenPtr->closing)) {

			unParsedTokens->jump(1);

			/*
				*
				* Call to this Functor.
				* Returns a Lambda that parses the unParsedTokens data member .
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
				* Steal STR name from token object.
				*
			*/
			return new AST_STR(ast::STR, std::move(*tokenPtr));

		return nullptr;
	};

};

auto mainPreparse(Queue<Token *> *unParsedTokens) {

	return [unParsedTokens](auto flag) {

		Queue<astPtr_t> *preparsedAst = new Queue<astPtr_t>;

		while(Node<Token *> *tokenNode = flag()) {

			preparsedAst->push(parseToken(tokenNode->value)); 
		};

		return preparsedAst;

	};
};

Queue<astPtr_t> *foo () {

	auto preparse = preparseWrapper(tokenNode);

	preparse(unParsedTokens->current());
};



preparse() {

	Queue<astPtr_t> preparsedAst





	
};

astPtr_t parseToken(Token *tokenPtr) {

	



};

AST *preparser::preparse(tNode tn, tNode exit) {

	if(tn == exit) return nullptr;


	// Skip BLOCK or LIST if end node is detected.
	tNode next = tn->closing ? tn->matchingPair : tn->next;

	std::cout << "PARSING:   " << tn->tokenPtr->getName() << "  " << tn << std::endl;


	// Next node in Linked-List of Tokens.
	AST *head = preparse(next, exit);

	astPtr_t newAstPtr = preparser::parseTNode(tn);

	if(!newAstPtr) return head; // Probably throw error?

	

	// Insert into Linked-List
	AST *newAST = new AST;

	newAST->node = newAstPtr;

	newAST->next = head;

	// Set next node's prev pointer to newNode.
	if(head) head->prev = newAST;

	head = newAST;

	return head;

};

astPtr_t preparser::parseTNode(tNode tn) {
	if(*tn == token::IDENTIFIER)

		// Call R-Value Constructor: Steal the name of IDENTIFIER that will be Deleted soon.
		return new AST_ID(ast::ID, std::move(*(tn->tokenPtr)));

	else if(*tn == token::IS)

		return new AST_BinOp(ast::ASSIGN);

	else if(*tn == token::SKINNY_ARROW) 

		return new AST_Block(ast::BLOCK, preparser::parseBlock(tn));

	else if(*tn == token::LBRACKET || (*tn == token::BAR && !tn->closing))

		return new AST_List(ast::LIST, preparser::parseList(tn));

	else if(*tn == token::STRING)

		// Call R-Value Constructor: Steal the name of STRING that will be Deleted soon.
		return new AST_STR(ast::STR, std::move((*tn->tokenPtr)));

	return nullptr;
};

AST *preparser::parseList(tNode openingTN) {
	std::cout << "PARSINGLIST:   " << openingTN << "matchingPair    " << openingTN->matchingPair<< std::endl;

	return preparser::preparse(openingTN->matchingPair->next, openingTN);
}




AST *preparser::parseBlock(tNode openingTN) {
	return preparser::preparse(openingTN->matchingPair->next, openingTN);
};





// UTILITIES 

// Skips to begining of LIST or BLOCK
// tNode utils::skipToOpen(tNode tn) {
// 	if(tn == token::RBRACKET)
// 		return arrayD.getCurrentOpen();
// 	return blockD.getCurrentOpen();
// };
