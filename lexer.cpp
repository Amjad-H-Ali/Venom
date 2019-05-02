#include <iostream>
#include <fstream>
#include "lexer.h"
#include "parser.h"
#include "Declarations.h"

using namespace std;

namespace utils = Lexer::Utility;


Lexer::Tokens *node = new Lexer::Tokens;




void utils::lexer(char *file_name) {

	ifstream in(file_name);
	char c;


	node->next = NULL;
	node->token_head = Lexer::get_statements(c, in);


	parser(node->token_head, NULL);

	for(Tokens *ptr = node; ptr; ptr = node->next) {
		for(Token *ptr2 = ptr->token_head; ptr2; ptr2 = ptr2->get_next()) {
			// if(ptr2->get_type()== WRITE)  
			// 	// cout << ptr2->get_value()->get_value()->get_name() << endl;
			// 	cout << ptr2->get_value()->get_name() << endl;
			// if(ptr2->get_type()==ARRAY) 
			// 	for(Token *ptr3 = ptr2->get_value(); ptr3; ptr3=ptr3->get_next())
			// 		cout << "From Array: " << ptr3->get_name() << endl;
			
			// if(ptr2->get_type()==FUNCTION) {
			// 	cout << "FROM FUNCTION BLOCK {\n";
			// 	for(Token *ptr3= ptr2->get_block(); ptr3; ptr3=ptr3->get_next()) {
			// 		if(ptr3->get_type() == WRITE)
			// 			cout << ptr3->get_value()->get_value()->get_name();
			// 		if(ptr3->get_type() == OUTPUT)
			// 			cout << "OUTPUT: " << ptr3->get_value()->get_value()->get_value()->get_name();
			// 	}
			// 	cout << "\n}" << endl;
			// }
			// if(ptr2->get_type()==FUNCTIONCALL) {
			// 	cout << ptr2->get_name() << " ( ";
			// 	for(Token *ptr3= ptr2->get_arguments(); ptr3; ptr3=ptr3->get_next())
			// 		cout << ptr3->get_name() << ' ';
			// 	cout << ")\n";
			// }
			cout << "Name: " <<ptr2->get_name()<< endl;
			
		}
	}
};


Token *utils::get_statements(char &c, ifstream &in) {

	in >> noskipws;
	while(in >> c){}
	
};

char *utils::chompString(char &c, ifstream &in) {

	 
	// Either a Single Quote or Double Quote.
	char quote = c;

	// Function that will be passed into rangeToChomp.
	bool(*func)(const char) = quote == '"' ? &isClosingDoubleQT : &isClosingSingleQT;

	// Skip Quote so rangeToChomp can continue
	in >> c;

	// Range to Chomp 								
	int range = utils::rangeToChomp(c, in, func);

	return utils::makeC_String(in, range);
};


char *utils::get_identifier(char &c, ifstream &in) {
	
	int length = Lexer::length_of_type(c, in, &is_AtoZ);


	char *identifier = new char[length];

	in.read(identifier, length);
	identifier[length] = '\0';
	return identifier; 
};

char *utils::chompOperator(char &c, ifstream &in) {

	// Range to Chomp
	int range = utils::rangeToChomp(c, in, &isOperator);

	return utils::makeC_String(in, range);
}


Token *utils::get_array_values(char &c, ifstream &in) {

	if(c == '|' || c == ')') {
		// Skip |
		in >> c;
		return NULL;
	}

	Token *new_token_in_array = NULL;

	if(!Lexer::not_quotes(c)) 
		new_token_in_array = new Token(Lexer::get_string(c, in), STRING);

	else if(Lexer::is_AtoZ(c)){

		char *identifier_name = Lexer::get_identifier(c, in);
		new_token_in_array = new Identifier(identifier_name, Lexer::which_identifier(identifier_name, c, in, true));
		cout << c << '\n';

	}

	in>>c;


	if(new_token_in_array == NULL)
		return Lexer::get_array_values(c, in);
	else {
		new_token_in_array->set_next(Lexer::get_array_values(c, in));
		return new_token_in_array;
	}
};

Token *utils::get_parameters(char &c, ifstream &in) {
	// If an array of Parameters, use get_array function
	if(c == '|') {
		// Skip |
		in >> c;
		return Lexer::get_array_values(c, in);
		
	}
	// For single parameter
	Token *new_token_in_param = NULL;
	char *identifier_name = Lexer::get_identifier(c, in);
	new_token_in_param = new Identifier(identifier_name, Lexer::which_identifier(identifier_name, c, in));
	return new_token_in_param;
};

Token *utils::get_block(char &c, ifstream &in) {
	// Find start of block
	while(c != '`')
		in >> ws >> c;
	// Current character is `. Get statetements in Block. End at closing `.
	Token *block = Lexer::get_statements(c, in);
	return block;
};

Token *utils::get_arguments(char &c, ifstream &in) {
	Token *arguments = Lexer::get_array_values(c, in);
	return arguments;
};

// Gets whole AlphaNumeric from beginning to end.
char *utils::chompAlphaNumeric(char &c, ifstream &in) {

	// Range to Chomp
	int range = utils::rangeToChomp(c, in, &isAlphaNumeric);

	return utils::makeC_String(in, range);
};

// Creates a C-String. Parameters are an ifstream object
// from which it will read in characters from current state
// of this file object, and the range of characters to read.
char *utils::makeC_String(ifstream &in, int range) {
	// Make a C String.
	char *name = new char[range];

	// Read in to name.
	in.read(name, range);

	name[range] = '\0';

	return name;
};  

Type utils::which_operator(char *c) {

	// Why c[0]? So functions don't get called for nothing. And still need names_macth to match ops with more than 1 character
	// and ensure something like %%% or ++++ is not Tokenized.
	if(c[0] == '=' && Lexer::names_match(c, (char *)"="))
		return ASSIGNMENT;
	else if(c[0] == '+' && (Lexer::names_match(c, (char *)"+") || Lexer::names_match(c, (char*)"++"))) 
		return ADDITION;
	else if(c[0] == '-' && (Lexer::names_match(c, (char *)"-")  || Lexer::names_match(c, (char *)"--")))
		return SUBTRACTION;
	else if(c[0] == '*' && Lexer::names_match(c, (char*)"*")) 
		return MULTIPLICATION;
	else if(c[0] == '/' && Lexer::names_match(c, (char*)"/"))
		return DIVISION;
	else if(c[0] == '%' && Lexer::names_match(c, (char*)"%"))
		return MODULO;
	else if(c[0] == '=' && Lexer::names_match(c, (char*)"==")) 
		return COMPARISON;
	else 
		return NIL;
	//TODO: Else Syntax error.

};

// Determines the length of stream to chomp based on the 
// Bool Function passed in as argument. Restores file pointer
// to original position when finished.
int utils::rangeToChomp(char &c, ifstream &in, bool(*greenLight)(const char)) {
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
	if(c == '=' || c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
		return true;
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
char utils::peekAhead(ifstream &in, int places) {
	char result;

	// To remember starting position
	streampos startPos = in.tellg();

	// Jump ahead and peek
	for(int i = 0; i < places; i ++)
		in >> ws >> result;

	// Return to start position
	in.seekg(startPos);

	return result;
};







