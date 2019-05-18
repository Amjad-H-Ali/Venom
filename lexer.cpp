#include <iostream>
#include <fstream>
#include "lexer.h"
#include "Token.h"
#include "ActionMap.h"



namespace utils = lexer::utility;


// Head and Tail to Doubly-Linked-List of ActionMap Nodes.
// See lexer::setMap
actMap::ActionMap *actMap::head = nullptr;
actMap::ActionMap *actMap::tail = nullptr; 


// LEXER FUNCTIONS

// Tokenizes input file and adds to Linked List.
token::TokenNode *lexer::lexer(char *fileName) {

	std::ifstream in(fileName);
	char c;

	// Head to Doubly-Linked-List of Token Nodes.
	token::TokenNode *headNode = nullptr;


	// Pointer to new Token object
	// that may be Instantiated soon.
	token::Token *newTokenPtr;



	// Read input file char by char
	// Do not skip white space otherwise
	// cannot differentiate between adjacent 
	// AlphaNumeral characters belonging to 
	// separate Tokens.
	in >> std::noskipws;
	while(in >> c) { 

		// Single Character Token
		if(utils::isSinglyNamedToken(c)) 
			newTokenPtr = new token::Token(utils::chompSinglyNamedToken(c, in));
		// AlphaNumeric(eg. Identifier, Keyword, etc.)
		else if(utils::isEligibleStartToAlphaNum(c)) 
			newTokenPtr = new token::Token(utils::chompAlphaNumeric(c, in), &utils::isEligibleStartToAlphaNum);
		// Potential Operator 
		else if(utils::isOperator(c)) 
			newTokenPtr = new token::Token(utils::chompOperator(c, in));
		// String
		else if(utils::isQuote(c)) 
			newTokenPtr = new token::Token(utils::chompString(c, in), &utils::isQuote);
		else continue; // Probably throw an error here, but continue for spaces.


		// Insert new TokenNode in Doubly-Linked-List...
		// After setting its value to point to new Token Object.
		token::TokenNode *newNode = new token::TokenNode;

		newNode->tokenPtr = newTokenPtr;
		newNode->next = headNode;
		if(headNode) newNode->next->prev = newNode; // Access prev property of neighbor node and point it to this newNode.
		headNode = newNode;

		if(utils::qualifiesForActionMap(newNode)) lexer::setMap(newNode);

		
	} // While



	return headNode;


}; // Lexer

// Inserts address of newNode in Link-List of ActionMaps 
void lexer::setMap(token::TokenNode *node) {


	actMap::ActionMap *newNode = new actMap::ActionMap;

	// Map to node.
	newNode->mapValue = node;

	// Insert newNode in Linked-List
	newNode->next = actMap::head;

	// If head points to nullptr, then let tail point to newNode ...
	// because newNode will be pushed to the end (LIFO or FILO).
	if(!actMap::head) actMap::tail = newNode;
	// Access prev property of neighbor node and point it to this newNode.
	else newNode->next->prev = newNode;

	actMap::head = newNode;

}

// UTILITY FUNCTIONS

// Checks if Token is valid ActionMap node.
bool utils::qualifiesForActionMap(const token::TokenNode *node) {
	return(*node == token::IS); // Much more coming soon.
}

// Gets whole Potential String from beginning to end.
char *utils::chompString(char &c, std::ifstream &in) {

	 
	// Either a Single Quote or Double Quote.
	char quote = c;


	// Function that will be passed into rangeToChomp.
	bool(*func)(const char) = (quote == '"' ? &isNotClosingDoubleQT : &isNotClosingSingleQT);

	// Skip Quote so rangeToChomp can continue
	in >> c;

	// Range to Chomp 								
	int range = utils::rangeToChomp(c, in, func);


	char *potentialString = utils::makeC_String(in, range);

	// Skip closing quote.
	in >> c;

	return potentialString;
};


// Gets Potential Operator
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

// Chomp Single Token
char *utils::chompSinglyNamedToken(char &c, std::ifstream &in) {
	// Range to Chomp
	// No need for rangeToChomp if Single Character Token

	// Set file pointer before Character to chomp
	// since read is not start inclusive.
	in.seekg(in.tellg()-(std::streampos)1, in.beg);

	std::cout << "Chomp: " <<c << std::endl;

	return utils::makeC_String(in, 1);
};

// Creates a C-String. Parameters are an ifstream object
// from which it will read in characters from current state
// of this file object, and the range of characters to read.
char *utils::makeC_String(std::ifstream &in, int range) {

	// Make a C String.
	char *name = new char[range+1];

	// Read in to name.
	in.read(name, range);

	name[range] = '\0';

	std::cout << "MakeString: " <<range << ' ' << name << std::endl;

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


// Check if character is an eligible operator.
bool utils::isOperator(char c) {
	if(c == '=' || c == '+' || c == '-' || c == '*' || c == '/' 
		|| c == '%' || c == '>' || c == '<') return true;
	return false;
};

// Checks if current charachter is a number
bool utils::isNumeric(char c) {
	if(c >= '0' && c <= '9') return true;
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

// Checks if character is a Quote
bool utils::isQuote(char c) {
	if(c == '"' || c == '\'') return true;
	return false;
};

// Returns true if not a single Quote.
bool utils::isNotClosingSingleQT(char c) {
	if(c != '\'') return true;
	return false;
};
// Returns true if not a double Quote.
bool utils::isNotClosingDoubleQT(char c) {
	if(c != '"') return true;
	return false;
};
 
// Checks if one of the singly named Tokens (eg. `, |, (, ), etc.)
bool utils::isSinglyNamedToken(char c) {
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







