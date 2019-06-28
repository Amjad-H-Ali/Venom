#include <iostream>
#include <utility>	// For move()
#include "preparser.h"

namespace utils = preparser::utility;

auto preparse(Queue<Token *> *unParsedTokens) {

	return [unParsedTokens](auto flag) {

		Queue<astPtr_t> *preparsedAst = new Queue<astPtr_t>;

		while(tokenNode = flag()) {

			preparsedAst->push(parseToken(tokenNode->value)); 
		};

		return preparsedAst;

	};
};

preparse() {

	Queue<astPtr_t> preparsedAst





	
};

parseToken(Token *tokenPtr) {

	if(*tokenPtr == token::ID)


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
