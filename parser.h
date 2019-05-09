#pragma once
#include "AST.h"
#include "AST_List.h"
#include "AST_ID.h"
#include "Token.h"


namespace parser {

namespace utility {

	bool validStartToList(token::Token *tokenPtr);

}; // utility



void parser(token::Token *current);


}; // parser