#pragma once
#include "AST.h"
#include "AST_List.h"
#include "AST_ID.h"
#include "Token.h"


namespace parser {

namespace utility {

	bool validStartToList(token::Token *tokenPtr);

}; // utility


// Main parser
AST *parser(token::Token *current);
// Parse right operand of an AST operator node
AST *parser::parseRightOperand(token::Token tokenPtr);
// Parse List of an AST list node
AST *parser::parseList(token::Token tokenPtr);


}; // parser