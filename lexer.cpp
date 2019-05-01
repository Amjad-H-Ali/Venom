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
	Token *head = NULL;
	Token *new_token_node;

	in >> noskipws;
	while(in >> c){
		if(!not_quotes(c))	
			new_token_node = new Token(Lexer::get_string(c, in), STRING);
		else if(is_AtoZ(c)) {
			char *identifier = get_identifier(c, in);
			Type type = which_identifier(identifier, c, in);
			if(type == ARRAY)
				new_token_node = new Identifier(Lexer::get_array_values(c, in), identifier, type);
			else if(type == FUNCTION) 
				new_token_node = new Function(identifier, Lexer::get_parameters(c, in), Lexer::get_block(c, in), type);
			else if(type == FUNCTIONCALL) 
				new_token_node = new FunctionCall(identifier, Lexer::get_arguments(c, in), type);
			else
				new_token_node = new Identifier(identifier, type);	
		}
		// Closing block. Retrieving statements is complete.
		else if(c == '`') {  
			cout << "Closing Block \n"; 
			in >> c; // Skip it. 
			break;
		}
		else if(is_operator(c)) {
			char *_operator = Lexer::get_operator(c, in);
			new_token_node = new Token(_operator, Lexer::which_operator(_operator));	
		}
		else 
			continue;
		new_token_node->set_next(head);
		head = new_token_node;		
	}
	return head;
};

char *utils::get_string(char &c, ifstream &in) {
	// Skip Quotes.
	in >> c;

	int length = Lexer::length_of_type(c, in, &not_quotes);

	char *_string = new char[length];
	

	in.read(_string, length);
	_string[length] = '\0';
	// Skip closing Quotes
	in>>c;

	return _string;

};


char *utils::get_identifier(char &c, ifstream &in) {
	
	int length = Lexer::length_of_type(c, in, &is_AtoZ);


	char *identifier = new char[length];

	in.read(identifier, length);
	identifier[length] = '\0';
	return identifier; 
};

char *utils::get_operator(char &c, ifstream &in) {
	int length = Lexer::length_of_type(c, in, &is_operator);

	char *_operator = new char[length];
	in.read(_operator, length);
	_operator[length] = '\0';
	return _operator;
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

Type utils::which_identifier(char *identifier_ptr, char &c, ifstream &in, bool in_array) {
	if(Lexer::names_match(identifier_ptr, (char*)"write"))
		return WRITE;
	else if(Lexer::names_match(identifier_ptr, (char*)"output"))
		return OUTPUT;
	else if((in>>ws).peek() == '|' && !in_array) {
		cout << "ARRAY\n";
		// Skip leading '|' to get into array.
		in >> ws >> c >> ws >> c;
		return ARRAY;
	}
	else if((in>>ws).peek() == '-' && multi_peek(in, 2) == '>') {
		// Skip -> 
		in >> ws >> c >> ws >> c >> ws >> c;
		return FUNCTION;
	}
	else if((in>>ws).peek() == '(') {
		// Skip (.
		in >> ws >> c >> ws >> c;
		return FUNCTIONCALL;
	}
	else
		return VARIABLE;
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

int utils::length_of_type(char &c, ifstream &in, bool(*green_light)(const char &)) {
	int start_pos = in.tellg(),
		   offset = 0,
		  end_pos,
		   length;
	while(green_light(c) && !in.eof()) {
		offset++;
		in>>c;
	}
	
	end_pos = start_pos+offset;
	cout << "END POS: " << end_pos << endl;
	length = end_pos - start_pos;
	// Reset file pointer to original position.
	in.clear();
	in.seekg(start_pos-1, in.beg);

	
	return length;
};



bool utils::isMatch(char *s1, char *s2) {
	int indx = 0;
	while(s1[indx] == s2[indx]) {
		if(s1[indx] == s2[indx] == '\0') return true;
		indx++;
	}
	return false;
};

bool utils::is_operator(const char &c) {
	if (c == '=' || c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
		return true;
	return false;
};

bool utils::is_AtoZ(const char &c) {
	if ((c >= 'a' && c <= 'z') || (c >='A' && c <= 'Z')) 
		return true;
	return false;
};

bool utils::not_quotes(const char &c) {
	if(c == '"' || c == '\'')
		return false;
	return true;
};


char utils::peekAhead(ifstream &in, int places) {
	char result;

	// To remember starting position
	streampos start_pos = in.tellg();

	// Jump ahead and peek
	for(int i = 0; i < places; i ++)
		in >> ws >> result;

	// Return to start position
	in.seekg(start_pos);

	return result;
};



// Utiltiy Functions To Help Determine Type of Tokens
bool utils::isIF(char *stream) {
	return isMatch(stream, "if");
};				
bool utils::isEQ(char *stream) {
	return isMatch(stream, "=");
};				
bool utils::isBAR(char *stream) {
	return isMatch(stream, "|");
};			
bool utils::isEQEQ(char *stream) {
	return isMatch(stream, "==");
};			
bool utils::isELSE(char *stream) {
	return isMatch(stream, "else");
};			
bool utils::isCOMMA(char *stream) {
	return isMatch(stream, ",");
};		
bool utils::isSTRING(char *stream) {
	
};		
bool utils::isOUTPUT(char *stream) {
	return isMatch(stream, "output");
};	
bool utils::isBACKTICK(char *stream) {
	return isMatch(stream, "`");
};	
bool utils::isIDENTIFIER(char *stream) {
	
};
bool utils::isSKINNYARROW(char *stream) {
	return isMatch(stream, "->");
};






