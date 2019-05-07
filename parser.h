#pragma once
#include "AST.h"
#include "AST_List.h"
#include "AST_ID.h"
#include "Token.h"


namespace parser {

namespace utility {

	bool validStartToList(token::Symbol tokenType);

}; // utility



void parser(token::Token *current, token::Token *previous);


}; // parser