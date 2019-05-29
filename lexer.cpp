#include <iostream>
#include <fstream>
#include "lexer.h"
#include "Token.h"


namespace utils = lexer::utility;


// Represents Current Dimension of LIST or BLOCK.
Dimension *const D = Dimension::getInstance();


// Head and Tail to Doubly-Linked-List of ActionMap Nodes.
// See lexer::setMap
// actMap::ActionMap *actMap::head = nullptr;
// actMap::ActionMap *actMap::tail = nullptr; 


// LEXER FUNCTIONS

// Tokenizes input file and adds to Linked List.
token::TokenNode *lexer::lexer(char *fileName) {

	std::ifstream in(fileName);
	bool inBlock;
	bool inList;
	char c;

	// Head to Doubly-Linked-List of Token Nodes.
	token::TokenNode *headNode = nullptr;


	// Pointer to new Token object
	// that may be Instantiated soon.
	token::Token *newTokenPtr = nullptr;



	// Read input file char by char
	// Do not skip white space otherwise
	// cannot differentiate between adjacent 
	// AlphaNumeral characters belonging to 
	// separate Tokens.
	in >> std::noskipws;
	while(in >> c) { 

		// Single Character Token
		if(utils::isSinglyNamedToken(c)) 
			newTokenPtr = new token::Token(utils::chompSingleChar(c, in));
		// AlphaNumeric(eg. Identifier, Keyword, etc.)
		else if(utils::isEligibleStartToAlphaNum(c)) 
			newTokenPtr = new token::Token(utils::chompAlphaNumeric(c, in), &utils::isEligibleStartToAlphaNum);
		// Potential Operator 
		else if(utils::isOperator(c)) 
			newTokenPtr = new token::Token(utils::chompOperator(c, in));
		// String
		else if(utils::isQuote(c)) 
			newTokenPtr = new token::Token(utils::chompString(c, in), &utils::isQuote);
		// TAB
		else if(utils::isEscSeq(c))
			newTokenPtr = new token::Token(utils::chompSingleChar(c, in));
		else continue; // Probably throw an error here, but continue for spaces.


		// Insert new TokenNode in Doubly-Linked-List...
		// after setting its value to point to new Token Object.
		token::TokenNode *newNode = new token::TokenNode;

		newNode->tokenPtr = newTokenPtr;
		newNode->next = headNode;
		if(headNode) newNode->next->prev = newNode; // Access prev property of neighbor node and point it to this newNode.
		headNode = newNode;

		// Tag the end-of-block Esc character or the BAR
		// to identify where a BLOCK or LIST ends.
		if(inBlock && *newNode == token::NEWLINE && utils::peekAhead(in,1) != '\t') {
			newNode->end = true;
			inBlock = false;
		}

		if(*newNode == token::SKINNY_ARROW) inBlock = true;
		

		if(*newNode == token::BAR && inList) {
			newNode->end = true;
			inList = false;
		}
		if(*newNode == token::BAR && !inList) inList = true;
		
	} // While



	return headNode;


}; // Lexer

// Determines if TokenNode Closes Dimension.
bool lexer::isClosing(token::TokenNode *tn, INFILE in) {


	if(*D == 0) return false;

	if(D->singleLine)

		for(int i = 0; *D > i; i ++) {

			char c = utils::peekAhead(in, i+1);

			if((i < 2 && c == ',') || c ==) return true;

			if(c == '\n' )
		}

		peek(D) == NewLine or EOF or in between is Comma return true

	// else if not singleLine
	// 	peek(D) != Tab or in between is comma return true

	// return false 

}

// // Inserts address of newNode in Link-List of ActionMaps 
// void lexer::setMap(token::TokenNode *node) {


// 	actMap::ActionMap *newNode = new actMap::ActionMap;

// 	// Map to node.
// 	newNode->mapValue = node;

// 	// Insert newNode in Linked-List
// 	newNode->next = actMap::head;

// 	// If head points to nullptr, then let tail point to newNode ...
// 	// because newNode will be pushed to the end (LIFO or FILO).
// 	if(!actMap::head) actMap::tail = newNode;
// 	// Access prev property of neighbor node and point it to this newNode.
// 	else newNode->next->prev = newNode;

// 	actMap::head = newNode;

// }

// // UTILITY FUNCTIONS

// // Checks if Token is valid ActionMap node.
// bool utils::qualifiesForActionMap(const token::TokenNode *node) {
// 	return(*node == token::IS); // Much more coming soon.
// }

// Gets whole Potential String from beginning to end.
char *utils::chompString(char &c, INFILE in) {

	 
	// Either a Single Quote or Double Quote.
	char quote = c;


	// Function that will be passed into rangeToChomp.
	bool(*func)(const char) = (quote == '"' ? &isNotClosingDoubleQT : &isNotClosingSingleQT);

	// Skip Quote so rangeToChomp can continue
	in >> c;

	// Range to Chomp 								
	auto range = utils::rangeToChomp(c, in, func);


	char *potentialString = utils::makeC_String(in, range);

	// Skip closing quote.
	in >> c;

	return potentialString;
};


// Gets Potential Operator
char *utils::chompOperator(char &c, INFILE in) {

	// Range to Chomp
	auto range = utils::rangeToChomp(c, in, &isOperator);

	return utils::makeC_String(in, range);
}


// Gets whole AlphaNumeric from beginning to end.
char *utils::chompAlphaNumeric(char &c, INFILE in) {

	// Range to Chomp
	auto range = utils::rangeToChomp(c, in, &isAlphaNumeric);

	return utils::makeC_String(in, range);
};

// Chomp Single Token
char *utils::chompSingleChar(char &c, INFILE in) {
	// Range to Chomp
	// No need for rangeToChomp if Single Character Token

	// Set file pointer before Character to chomp
	// since read is not start inclusive.
	in.seekg(in.tellg()-(decltype(in.tellg()))1, in.beg);

	std::cout << "Chomp: " << c << std::endl;

	return utils::makeC_String(in, 1);
};


// Creates a C-String. Parameters are an ifstream object
// from which it will read in characters from current state
// of this file object, and the range of characters to read.
char *utils::makeC_String(INFILE in, std::streampos range) {

	// Make a C String.
	char *name = new char[range+(decltype(in.tellg()))1];

	// Read in to name.
	in.read(name, range);

	name[range] = '\0';


	return name;
};  


// Determines the length of stream to chomp based on the 
// Bool Function passed in as argument. Restores file pointer
// to original position when finished.
std::streampos utils::rangeToChomp(char &c, INFILE in, bool(*greenLight)(const char)) {
	decltype(in.tellg()) startPos = in.tellg(), offset = 0, endPos, range;
	while(greenLight(c) && !in.eof()) {
		offset+= (decltype(in.tellg()))1;
		in>>c;

	}
	endPos = startPos + offset;
	range = endPos - startPos;

	// Reset file pointer to original position.
	in.clear();
	in.seekg(startPos-(decltype(in.tellg()))1, in.beg);

	return range;
};


// Check if character is an eligible operator.
bool utils::isOperator(char c) {
	return (c == '=' || c == '+' || c == '-' || c == '*' || c == '/' 
		|| c == '%' || c == '>' || c == '<');
};

// Checks if current charachter is a number
bool utils::isNumeric(char c) {
	return (c >= '0' && c <= '9');
}

// Checks if current character is a letter.
bool utils::isAtoZ(char c) {
	return ((c >= 'a' && c <= 'z') || (c >='A' && c <= 'Z'));
};

// Checks if character is Alphanumeric (A-Z, 0-9, or _)
bool utils::isAlphaNumeric(char c) {
	return (utils::isAtoZ(c) || utils::isNumeric(c) || c == '_');
};

// Checks if character is an eligible beggining for AlphaNumeric.
bool utils::isEligibleStartToAlphaNum(char c) {
	return (utils::isAtoZ(c) || c == '_');
};

// Checks if character is a Quote
bool utils::isQuote(char c) {
	return (c == '"' || c == '\'');
};

// Returns true if not a single Quote.
bool utils::isNotClosingSingleQT(char c) {
	return (c != '\'');
};
// Returns true if not a double Quote.
bool utils::isNotClosingDoubleQT(char c) {
	return (c != '"');
};
 
// Checks if one of the singly named Tokens (eg. `, |, (, ), etc.)
bool utils::isSinglyNamedToken(char c) {
	return (c == '`' || c == '|' || c == '(' || c == ')' || c == ',');
};

// Checks if character is one of the relevant Escape Sequences.
bool utils::isEscSeq(char c) {
	return (c == '\t' || c == '\n'); // To Add, Soon.
};

// To Peek multiple characters Ahead
// Params: ifstream object and Amount 
// of places to Peek Ahead.
char utils::peekAhead(INFILE in, int places) {
	char result;
	char container; 

	// To remember starting position
	auto startPos = in.tellg();

	// Skip ahead and peek.
	for(int i = 0; i < places; i ++) {
		in >> container;

		// To Skip Spaces ' ' 0x20, but not other ws.
		if(!in.eof() && container == ' ') {
			i--;
			continue;
		}

		result = container;
	}

	// Return to start position
	in.seekg(startPos);

	return result;
};







