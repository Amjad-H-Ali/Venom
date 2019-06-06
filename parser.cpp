#include <iostream>
#include "parser.h"
#include <utility>	// For move()

namespace utils = parser::utility;


ASTNode *parser::parse(tNode tn, tNode exit) {

	if(tn == exit) return nullptr;


	// Skip BLOCK or LIST if end node is detected.
	tNode next = tn->closing ? tn->matchingPair : tn->next;

	std::cout << "PARSING:   " << tn->tokenPtr->getName() << "  " << tn << std::endl;


	// Next node in Linked-List of Tokens.
	ASTNode *head = parse(next, exit);

	AST *newAST = parser::parseTNode(tn);

	if(!newAST) return head; // Probably throw error?

	

	// Insert into Linked-List
	ASTNode *newNode = new ASTNode;

	newNode->value = newAST;

	newNode->next = head;

	// Set next node's prev pointer to newNode.
	if(head) head->prev = newNode;

	head = newNode;

	return head;

};

AST *parser::parseTNode(tNode tn) {
	if(*tn == token::IDENTIFIER)
		// Call R-Value Constructor: Steal the name of IDENTIFIER that will be Deleted soon.
		return new AST(ID, std::move(*(tn->tokenPtr)));
	else if(*tn == token::IS)
		return new AST(ASSIGN);
	else if(*tn == token::SKINNY_ARROW)
		return new AST(BLOCK, parser::parseBlock(tn));
	else if(*tn == token::LBRACKET)
		return new AST(LIST, parser::parseList(tn));
	else if(*tn == token::STRING)
		// Call R-Value Constructor: Steal the name of STRING that will be Deleted soon.
		return new AST(STR, std::move((*tn->tokenPtr)));
	return nullptr;
};

ASTNode *parser::parseList(tNode openingTN) {
	std::cout << "PARSINGLIST:   " << openingTN << "matchingPair    " << openingTN->matchingPair<< std::endl;

	return parser::parse(openingTN->matchingPair->next, openingTN);
}

// Parses a LIST from a linked-list of token nodes.
// ASTNode *parser::parseList(tNode tn) {
// 	// Is this LIST a Parameter LIST of a Function?
// 	static bool isParam;

// 	if(*tn == token::BAR && tn->closing) {

// 		// Check if this LIST is a Param LIST.
// 		if(*tn->prev == token::SKINNY_ARROW) isParam = true;

// 		return nullptr;
// 	}

// 	// Iterate Left Given the LIFO order of Linked-Lists.
// 	ASTNode *head = parseList(tn->prev);

// 	if(isParam) std::cout << tn->tokenPtr->getType() << " Yes" << std::endl; 

// 	if(*tn == token::IDENTIFIER || *tn == token::STRING) {

// 		// Cannot be a Parameter LIST if contains anything other...
// 		// than an IDENTIFIER.
// 		// if(isParam && tn != token::IDENTIFIER) throw error here as params only can contain IDs

// 		AST *newAST = parseTNode(tn);

// 		// Insert into Linked-List
// 		ASTNode *newNode = new ASTNode;

// 		newNode->value = newAST;

// 		newNode->next = head;

// 		// Set next node's prev pointer to newNode.
// 		if(head) head->prev = newNode;

// 		head = newNode;

// 	}
// 	// Skip COMMA.
// 	else if(*tn == token::COMMA) return head;

// 	// TODO:
// 	// else throw error and delete head

// 	return head;

// };


ASTNode *parser::parseBlock(tNode openingTN) {
	return parser::parse(openingTN->matchingPair->next, openingTN);
};





// UTILITIES 

// Skips to begining of LIST or BLOCK
// tNode utils::skipToOpen(tNode tn) {
// 	if(tn == token::RBRACKET)
// 		return arrayD.getCurrentOpen();
// 	return blockD.getCurrentOpen();
// };
