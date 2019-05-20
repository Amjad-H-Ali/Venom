#pragma once
#include <iostream>
#include "Token.h"

// Forward Declaration of token::Token and token::TokenNode classes.
namespace token {
	class Token;
	struct TokenNode;
} // End of forward delaration of Token class.

namespace lexer {

namespace utility	{


	// UTILITY FUNCTIONS
		
	// Checks if Token is valid ActionMap node.
	bool qualifiesForActionMap(const token::TokenNode *node);
	// Gets entire potential string.
	char *chompString(char &c, std::ifstream &in);
	char *chompOperator(char &c, std::ifstream &in);
	// Gets whole AlphaNumeric from beginning to end.
	char *chompAlphaNumeric(char &c, std::ifstream &in);
	// Chomp Single Token
	char *chompSingleChar(char &c, std::ifstream &in);
	// Creates a C-String. Parameters are an ifstream object
	// from which it will read in characters from current state
	// of this file object, and the range of characters to read.
	char *makeC_String(std::ifstream &in, int range);
	// Determines the length of stream to chomp based on the 
	// Bool Function passed in as argument. Restores file pointer
	// to original position when finished.
	int rangeToChomp(char &c, std::ifstream &in, bool(*greenLight)(const char));
	bool isOperator(char c);
	// Checks if current charachter is a number
	bool isNumeric(char c);
	// Checks if current character is a letter.
	bool isAtoZ(char c);
	// Checks if character is Alphanumeric (A-Z, 0-9, or _)
	bool isAlphaNumeric(char c);
	// Checks if character is an eligible beggining for AlphaNumeric.
	bool isEligibleStartToAlphaNum(char c);
	// Checks if one of the singly named Tokens (eg. `, |, (, ), etc.)
	bool isSinglyNamedToken(char c);
	// Checks if c is Quotes
	bool isQuote(char c);
	// Returns true if character is not a single quote.
	bool isNotClosingSingleQT(char c);
	// Returns true if character is not a double quote.
	bool isNotClosingDoubleQT(char c);
	// Checks if character is a relevant Escape Sequence.
	bool isEscSeq(char c);
	// To Peek multiple characters Ahead
	// Params: ifstream object and Amount 
	// of places to Peek Ahead.
	char peekAhead(std::ifstream &in, int places);



}; // utility Namespace
	
	// LEXER FUNCTIONS

	// Tokenizes input file and adds to Linked List of Tokens.
	token::TokenNode *lexer(char *fileName);
	// Inserts address of newNode in Link-List of ActionMaps 
	void setMap(token::TokenNode *node);
	
}; // lexer Namespace
