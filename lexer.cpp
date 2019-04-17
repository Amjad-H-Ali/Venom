#include <iostream>
#include <fstream>
#include "lexer.h"
#include "parser.h"
#include "Declarations.h"

using namespace std;


Lexer::Tokens *node = new Lexer::Tokens;




void Lexer::lexer(char *file_name) {

	node->token_head = NULL;
	node->next = NULL;

	ifstream in(file_name);
	char c;
	Token *new_token_node;

	in >> noskipws;
	while(in >> c){
		if(!not_quotes(c))
			
			new_token_node = new Token(get_string(c, in), STRING);
			
		else if(is_AtoZ(c)) { 
			char *identifier = get_identifier(c, in);
			Type type = which_identifier(identifier, c, in);

			if(type == ARRAY)
				new_token_node = new Identifier(get_array_values(c, in), identifier, type);
			else
				new_token_node = new Identifier(identifier, type);

			if(is_declared(new_token_node->get_name()) == NULL) declare(new_token_node);
			
		}
		
		else if(is_operator(c)) {
			char *_operator = Lexer::get_operator(c, in);
			new_token_node = new Token(_operator, Lexer::which_operator(_operator));
			
		}
		else 
			continue;

		new_token_node->set_next(node->token_head);
		node->token_head = new_token_node;

				
	};

	parser(node->token_head, NULL);

	for(Tokens *ptr = node; ptr; ptr = node->next) {
		for(Token *ptr2 = ptr->token_head; ptr2; ptr2 = ptr2->get_next()) {
			if(ptr2->get_type()== WRITE)  
				cout << ptr2->get_value()->get_value()->get_name() << endl;
			if(ptr2->get_type()==ARRAY) {
				for(Token *ptr3 = ptr2->get_value(); ptr3; ptr3=ptr3->get_next())
					cout << "From Array: " << ptr3->get_name() << endl;
			}
			
		}
	}
};




char *Lexer::get_string(char &c, ifstream &in) {
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


char *Lexer::get_identifier(char &c, ifstream &in) {
	
	int length = Lexer::length_of_type(c, in, &is_AtoZ);


	char *identifier = new char[length];

	in.read(identifier, length);
	identifier[length] = '\0';
	cout << "****Identifier**** " << identifier << endl;
	return identifier; 
};

char *Lexer::get_operator(char &c, ifstream &in) {
	int length = Lexer::length_of_type(c, in, &is_operator);

	char *_operator = new char[length];
	in.read(_operator, length);
	_operator[length] = '\0';
	return _operator;
}


Token *Lexer::get_array_values(char &c, ifstream &in) {

	if(c == '|')
		return NULL;

	Token *new_token_in_array = NULL;

	if(!Lexer::not_quotes(c)) 
		new_token_in_array = new Token(Lexer::get_string(c, in), STRING);

	else if(Lexer::is_AtoZ(c)){
		char *identifier = Lexer::get_identifier(c, in);

		new_token_in_array = new Identifier(identifier, Lexer::which_identifier(identifier, c, in));
	}

	in>>c;


	if(new_token_in_array == NULL)
		return Lexer::get_array_values(c, in);
	else {
		new_token_in_array->set_next(Lexer::get_array_values(c, in));
		return new_token_in_array;
	}
};





Type Lexer::which_identifier(char *identifier_ptr, char &c, ifstream &in) {
	if((in>>ws).peek() == '|') {
		in >> c; in >>c;
		return ARRAY;
	}
	else if(Lexer::names_match(identifier_ptr, (char*)"write"))
		return WRITE;
	else
		return VARIABLE;
};
Type Lexer::which_operator(char *c) {

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

int Lexer::length_of_type(char &c, ifstream &in, bool(*green_light)(const char &)) {
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


bool Lexer::names_match(char *s1, char *s2) {
	int indx = 0;
	while(s1[indx] == s2[indx]) {
		if(s1[indx] == '\0') 
			return true;
		indx++;
	}
	return false;
};

bool Lexer::is_operator(const char &c) {
	if (c == '=' || c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
		return true;
	return false;
};

bool Lexer::is_AtoZ(const char &c) {
	if ((c >= 'a' && c <= 'z') || (c >='A' && c <= 'Z')) 
		return true;
	return false;
};
bool Lexer::not_quotes(const char &c) {
	if(c == '"' || c == '\'')
		return false;
	return true;
}








