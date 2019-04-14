#include <iostream>
#include <fstream>
#include "lexer.h"
#include "parser.h"

using namespace std;


Tokens *node = new Tokens;




void lexer(char *file_name) {

	node->token_head = NULL;
	node->next = NULL;

	ifstream in(file_name);
	char c;
	Token *new_token_node;


	while(in >> c){
		
		if(!not_quotes(c)) {
			
			new_token_node = new Token(get_string(c, in), STRING);
		}

		else if(is_AtoZ(c)) { 
			char *identifier = get_identifier(c, in);
			Type type = which_identifier(identifier, c, in);

			if(type == ARRAY)
				new_token_node = new Identifier(get_array_values(identifier, in), identifier, type);
			else
				new_token_node = new Identifier(identifier, type);
		}
		
		else if() 
			new_token_node = new Token(&s[0], which_operator(s));
	

		new_token_node->set_next(node->token_head);
		node->token_head = new_token_node;
	};

	parser(node->token_head, NULL);

	for(Tokens *ptr = node; ptr; ptr = node->next) {
		for(Token *ptr2 = ptr->token_head; ptr2; ptr2 = ptr2->get_next()) {
			if(ptr2->get_type()== WRITE)  
				cout << ptr2->get_value()->get_value()->get_name() << endl;
			if(ptr2->get_type()==ARRAY)
				for(Token *ptr3 = ptr2->get_value(); ptr3; ptr3=ptr3->get_next())
					cout << "From Array: " << ptr3->get_name() << endl;
			
		}
	}
};




char *get_string(char &c, ifstream &in) {
	// Skip Quotes.
	in >> c;

	int length = length_of_type(c, in, &not_quotes);

	char *_string = new char[length];
	_string[length-1] = '\0';

	in.read(_string, length);

	return _string;

};
char *get_identifier(char &c, ifstream &in) {
	
	int length = length_of_type(c, in, &is_AtoZ);


	char *identifier = new char[length];

	identifier[length-1] = '\0';
	in.read(identifier, length);

	return identifier; 
};
Token *get_array_values(string &s, ifstream &in) {

	if(s[0] == '|')
		return NULL;

	Token *new_token_in_array;

	if(s[0] == '"' || s[0] == '\'' ) {
		new_token_in_array = new Token(&s[1], STRING);
	}
	else if((s[0] >= 'a' && s[0] <= 'z') || (s[0] >='A' && s[0] <= 'Z')){
		new_token_in_array = new Identifier(&s[0], which_identifier(s));
	}
	in>>s;
	new_token_in_array->set_next(get_array(s, in));
	return new_token_in_array;
};

int length_of_type(char &c, ifstream &in, bool(*green_light)(const char)) {
	int start_pos = in.tellg();
		  end_pos,
		  length;

	while(green_light(c))
		in >> c;
	end_pos = in.tellg();
	length = end_pos - start_pos;
	// Reset file pointer to original position.
	in.clear();
	in.seekg(start_pos, in.beg);

	
	return length;
};

bool names_match(char *s1, char *s2) {
	int indx = 0;
	while(s1[indx] == s2[indx]) {
		if(s1[indx] == '\0') 
			return true;
		indx++;
	}
	return false;
};

Type which_identifier(char *identifier_ptr, char &c, ifstream &in) {
	if((in>>ws).peek() == '|') {
		in >> c;
		return ARRAY;
	}
	else if(names_match(identifier_ptr, (char*)"write"))
		return WRITE;
	else
		return VARIABLE;
};
Type which_operator(string &s) {
	if(strings_match(s, (char*)"="))
		return ASSIGNMENT;
	else if(s[0] == '+' || strings_match(s, (char*)"++")) 
		return ADDITION;
	else if(s[0] || strings_match(s, (char*)'-')) 
		return SUBTRACTION;
	else if(strings_match(s, (char*)"*")) 
		return MULTIPLICATION;
	else if(strings_match(s, (char*)"/"))
		return DIVISION;
	else if(strings_match(s, (char*)"%"))
		return MODULO;
	else if(strings_match(s, (char*)"==")) 
		return COMPARISON;

};





bool is_operator(char &c, ifstream &in) {
	if (s[0] == '=' || s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/' || s[0] == '%')
		return true;
	return false;
};

bool is_AtoZ(const char &c) {
	if ((c >= 'a' && c <= 'z') || (c >='A' && c <= 'Z'))
		return true;
	return false;
};
bool not_quotes(const char &c) {
	if(c == '"' || c == '\'')
		return false;
	return true;
}








