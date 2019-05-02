#include <iostream>
#include <fstream>
#include "lexer.h"
// #include "parser.h"


namespace utils = Lexer::Utility;



// Lexer::Tokens *node = new Lexer::Tokens;




// void utils::lexer(char *file_name) {

// 	ifstream in(file_name);
// 	char c;


// 	node->next = NULL;
// 	node->token_head = Lexer::get_statements(c, in);


// 	parser(node->token_head, NULL);


// };


// Token *utils::get_statements(char &c, ifstream &in) {

// 	in >> noskipws;
// 	while(in >> c){}
	
// };

char *utils::chompString(char &c, std::ifstream &in) {

	 
	// Either a Single Quote or Double Quote.
	char quote = c;

	// Function that will be passed into rangeToChomp.
	bool(*func)(const char) = (quote == '"' ? &isClosingDoubleQT : &isClosingSingleQT);

	// Skip Quote so rangeToChomp can continue
	in >> c;

	// Range to Chomp 								
	int range = utils::rangeToChomp(c, in, func);

	return utils::makeC_String(in, range);
};


char *utils::chompOperator(char &c, std::ifstream &in) {

	// Range to Chomp
	int range = utils::rangeToChomp(c, in, &isOperator);

	return utils::makeC_String(in, range);
}


// Gets whole AlphaNumeric from beginning to end.
char *utils::chompAlphaNumeric(char &c, std::ifstream &in) {

	// Range to Chomp
	int range = utils::rangeToChomp(c, in, &isAlphaNumeric);

	return utils::makeC_String(in, range);
};

// Creates a C-String. Parameters are an ifstream object
// from which it will read in characters from current state
// of this file object, and the range of characters to read.
char *utils::makeC_String(std::ifstream &in, int range) {
	// Make a C String.
	char *name = new char[range];

	// Read in to name.
	in.read(name, range);

	name[range] = '\0';

	return name;
};  




// Determines the length of stream to chomp based on the 
// Bool Function passed in as argument. Restores file pointer
// to original position when finished.
int utils::rangeToChomp(char &c, std::ifstream &in, bool(*greenLight)(const char)) {
	int startPos = in.tellg(), offset = 0, endPos, range;

	while(greenLight(c) && !in.eof()) {
		offset++;
		in>>c;
	}

	endPos = startPos + offset;
	range = endPos - startPos;

	// Reset file pointer to original position.
	in.clear();
	in.seekg(startPos-1, in.beg);

	return range;
};


bool utils::isOperator(char c) {
	if(c == '=' || c == '+' || c == '-' || c == '*' || c == '/' 
		|| c == '%' || c == '>' || c == '<') return true;
	return false;
};

// Checks if current charachter is a number
bool utils::isNumeric(char c) {
	if(c >= '0' || c <= '9') return true;
	return false;
}

// Checks if current character is a letter.
bool utils::isAtoZ(char c) {
	if((c >= 'a' && c <= 'z') || (c >='A' && c <= 'Z')) return true;
	return false;
};

// Checks if character is Alphanumeric (A-Z, 0-9, or _)
bool utils::isAlphaNumeric(char c) {
	if(utils::isAtoZ(c) || utils::isNumeric(c) || c == '_') return true;
	return false;
}

// Checks if character is an eligible beggining for AlphaNumeric.
bool utils::isEligibleStartToAlphaNum(char c) {
	if(utils::isAtoZ(c) || c == '_') return true;
	return false;
};

// Checks if c is Quotes
bool utils::isQuote(char c) {
	if(c == '"' || c == '\'') return true;
	return false;
};

bool utils::isClosingSingleQT(char c) {
	if(c == '\'') return true;
	return false;
};
bool utils::isClosingDoubleQT(char c) {
	if(c == '"') return true;
	return false;
};
 
// Checks if one of the singly named Tokens (eg. `, |, (, ), etc.)
bool utils::isSinglyNamed(char c) {
	if(c == '`' || c == '|' || c == '(' || c == ')' || c == ',') return true;
	return false;
};

// To Peek multiple characters Ahead
// Params: ifstream object and Amount 
// of places to Peek Ahead.
char utils::peekAhead(std::ifstream &in, int places) {
	char result;

	// To remember starting position
	std::streampos startPos = in.tellg();

	// Jump ahead and peek
	for(int i = 0; i < places; i ++)
		in >> std::ws >> result;

	// Return to start position
	in.seekg(startPos);

	return result;
};







