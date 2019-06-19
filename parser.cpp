#include <iostream>
#include <variant>
#include "AST.h"
#include "AST_Node.h"
#include "AST_STR.h"
#include "AST_List.h"
#include "AST_ID.h"
#include "AST_Block.h"
#include "AST_BinOp.h"
#include "AST_Func.h"
#include "parser.h"





AST *parser::_main(AST *astHead) {

	if(!astHead) return nullptr;

	AST *head = _main(astHead->next);

	astPtr_t astPtr = parser::parse(astHead, astHead->node);

	if(!astPtr) return head;

	AST *newAST = new AST;

	newAST->node = astPtr;

	newAST->next = head;

	head = newAST;

	return head;

};

template<typename ... Params>
astPtr_t parser::parse (AST *parent, Params&& ... params) {

	return std::visit(AstOverloads{

		[parent](AST_Block *block)->astPtr_t {return parseBlockContext(parent);},

		[parent](AST_List *list, AST_Block *block)->astPtr_t {std::cout << "----------------------------------------------------------------------------------------------- (AST_List *list, AST_Block *block)->astPtr_t " << std::endl; return new AST_Func(ast::FUNC, list, parser::parseBlock(block) );},

		[parent](auto, auto)->astPtr_t {return new AST_Block(ast::FUNC, nullptr);},

		[parent](auto)->astPtr_t {return new AST_Block(ast::FUNC, nullptr);}

	}, std::forward<Params>(params)...);

};

astPtr_t  parser::parseBlockContext(AST *parentOfBlock) {

  	AST *nextParent = parentOfBlock->prev;

  	return nextParent ? parser::parse(nextParent, nextParent->node, parentOfBlock->node) : nullptr;
};

AST_Block *parser::parseBlock(AST_Block *block) {


	parser::_main(block->getValue());

	return block;

}


