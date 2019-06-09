#include <iostream>
#include "parser.h"
#include <utility>	// For move()

namespace utils = parser::utility;


AST *parser::parse(tNode tn, tNode exit) {

	if(tn == exit) return nullptr;


	// Skip BLOCK or LIST if end node is detected.
	tNode next = tn->closing ? tn->matchingPair : tn->next;

	std::cout << "PARSING:   " << tn->tokenPtr->getName() << "  " << tn << std::endl;


	// Next node in Linked-List of Tokens.
	AST *head = parse(next, exit);

	AST_Node *newAST_Node = parser::parseTNode(tn);

	if(!newAST_Node) return head; // Probably throw error?

	

	// Insert into Linked-List
	AST *newAST = new AST;

	newAST->node = newAST_Node;

	newAST->next = head;

	// Set next node's prev pointer to newNode.
	if(head) head->prev = newAST;

	head = newAST;

	return head;

};

AST_Node *parser::parseTNode(tNode tn) {
	if(*tn == token::IDENTIFIER)

		// Call R-Value Constructor: Steal the name of IDENTIFIER that will be Deleted soon.
		return new AST_ID(ast::ID, std::move(*(tn->tokenPtr)));

	else if(*tn == token::IS)

		return new AST_BinOp(ast::ASSIGN);

	else if(*tn == token::SKINNY_ARROW)

		return new AST_Block(ast::BLOCK, parser::parseBlock(tn));

	else if(*tn == token::LBRACKET || (*tn == token::BAR && !tn->closing))

		return new AST_List(ast::LIST, parser::parseList(tn));

	else if(*tn == token::STRING)

		// Call R-Value Constructor: Steal the name of STRING that will be Deleted soon.
		return new AST_STR(ast::STR, std::move((*tn->tokenPtr)));

	return nullptr;
};

AST *parser::parseList(tNode openingTN) {
	std::cout << "PARSINGLIST:   " << openingTN << "matchingPair    " << openingTN->matchingPair<< std::endl;

	return parser::parse(openingTN->matchingPair->next, openingTN);
}




AST *parser::parseBlock(tNode openingTN) {
	return parser::parse(openingTN->matchingPair->next, openingTN);
};





// UTILITIES 

// Skips to begining of LIST or BLOCK
// tNode utils::skipToOpen(tNode tn) {
// 	if(tn == token::RBRACKET)
// 		return arrayD.getCurrentOpen();
// 	return blockD.getCurrentOpen();
// };
