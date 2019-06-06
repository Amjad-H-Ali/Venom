#pragma once
#include "AST.h"
#include "Token.h"

// Alias for const token::TokenNode *
typedef const token::TokenNode *tNode;


namespace parser {

namespace utility {

// UTILITIES 

// Skips to begining of LIST or BLOCK
// tNode skipTo(tNode tn);

}; // utility

// PARSER functions

// MAIN parser function
ASTNode *parse(tNode tn, tNode exit= nullptr);

// Parses a specific token Node and returns an AST.
AST *parseTNode(tNode tn);

// Parses a LIST from a linked-list of token nodes.
// ASTNode *parseList(tNode tn);
ASTNode *parseList(tNode openingTN);

// Parses a BLOCK from a linked-list of token nodes.
ASTNode *parseBlock(tNode tn);


}; // parser