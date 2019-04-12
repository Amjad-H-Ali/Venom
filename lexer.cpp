#include <iostream>
#include <fstream>
#include "lexer.h"
#include "parser.h"

using namespace std;


Tokens *node = new Tokens;




void lexer(char *file_name) {

	node->token_head = NULL;
	node->next = NULL;

	ifstream in;
	in.open(file_name);
	string s;
	Token *new_token_node;

	while(in >> s){
		
		if(s[0] == '"' || s[0] == '\'') {
			get_string(s, in);

			new_token_node = new Token(&s[1], STRING);
		}
		else if((s[0] > 'a' && s[0] < 'z') || (s[0] >'A' && s[0] < 'Z')) {
			new_token_node = new Identifier(&s[0], which_identifier(s));
		}
		else if(s[0] == '=' || s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/' || s[0] == '%') {
			new_token_node = new Token(&s[0], which_operator(s));
		}

		new_token_node->set_next(node->token_head);
		node->token_head = new_token_node;
	};

	parser(node->token_head);

	for(Tokens *ptr = node; ptr; ptr = node->next) {
		for(Token *ptr2 = ptr->token_head; ptr2; ptr2 = ptr2->get_next()) {
			if(ptr2->get_type()==ADDITION) {
				cout << ptr2->get_name() << endl;
			}
		}
	}
};




void get_string(string &s, ifstream &in) {
	string left_over;
	int last_indx = s.length() - 1;

	while(s[last_indx] != '\'' && s[last_indx] != '"') {
		in >> left_over;
		s+= (' ' + left_over);
		last_indx = s.length() - 1;
	}
};

bool strings_match(string &s1, char *s2) {
	int indx = 0;
	while(s1[indx] == s2[indx]) {
		if(s1[indx] == '\0') 
			return true;
		indx++;
	}
	return false;
};

Type which_identifier(string &s) {
	if(strings_match(s, (char*)"write"))
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







