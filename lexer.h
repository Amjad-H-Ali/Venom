#pragma once
#include "Token.h"


namespace lexer {



namespace utility	{
		


	char *chompString(char &c, std::ifstream &in);
	char *chompOperator(char &c, std::ifstream &in);
	// Gets whole AlphaNumeric from beginning to end.
	char *chompAlphaNumeric(char &c, std::ifstream &in);
	// Chomp Single Token
	char *chompSinglyNamedToken(char &c, std::ifstream &in);
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
	bool isClosingSingleQT(char c);
	bool isClosingDoubleQT(char c);

	// To Peek multiple characters Ahead
	// Params: ifstream object and Amount 
	// of places to Peek Ahead.
	char peekAhead(std::ifstream &in, int places);



}; // utility Namespace

	void lexer(char *fileName);

	// struct Tokens {
	// 	Token *token_head;
	// 	Tokens *next;
	// }; // Tokens Struct
	
}; // lexer Namespace
