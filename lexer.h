#ifndef LEXER_H

#define LEXER_H

#include <iostream>
#include "Token.h"



// Alias for ifstream&
typedef std::ifstream &INFILE;

// Forward Declaration of token::Token and token::TokenNode classes.
namespace token {
	class Token;
	struct TokenNode;
} // End.

namespace lexer {

namespace utility	{


	// UTILITY FUNCTIONS
		
	// Gets entire potential string.
	char *chompString(char &c, INFILE in);
	char *chompOperator(char &c, INFILE in);
	// Gets whole AlphaNumeric from beginning to end.
	char *chompAlphaNumeric(char &c, INFILE in);
	// Chomp Single Token
	char *chompSingleChar(char &c, INFILE in);
	// Creates a C-String. Parameters are an ifstream object
	// from which it will read in characters from current state
	// of this file object, and the range of characters to read.
	char *makeC_String(INFILE in, std::streampos range);
	// Determines the length of stream to chomp based on the 
	// Bool Function passed in as argument. Restores file pointer
	// to original position when finished.
	std::streampos rangeToChomp(char &c, INFILE in, bool(*greenLight)(const char));
	// Checks if char is one of the operators.
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
	/*
		Checks if Token Node is part of an array or block,
		which is Dimensional.
	*/
	bool isDimensional(INFILE in, token::TokenNode *tn);
	// Checks if Token Node is last in block.
	bool isClosingBlock(INFILE in, token::TokenNode *tn);
	// Checks if range ahead contains only given character.
	bool rangeOnlyHas(INFILE in, int places, char c);
	// To Peek multiple characters Ahead
	// Params: ifstream object and Amount 
	// of places to Peek Ahead.
	char peekAhead(INFILE in, int places);



}; // utility
	
	// LEXER FUNCTIONS

	// Tokenizes input file and adds to Linked List of Tokens.
	token::TokenNode *lexer(char *fileName);

	// Inserts start/end to block or array in 
	// respective Object.
	void insertDimension(token::TokenNode *tn);
	
	
}; // lexer 

#endif
