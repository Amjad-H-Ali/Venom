#include "AST_List.h"


AST_List::AST_List(AST_SYMBOL type, AST *ASTPtr)
	:AST(type), value(ASTPtr)
{};

AST* AST_List::getValue() const {
	return this->value;
};