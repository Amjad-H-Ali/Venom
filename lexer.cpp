#include <iostream>
#include <fstream>
#include "lexer.h"
#include "Definitions.h"

using namespace std;


Tokens *node = new Tokens;


void parser(Token *node);

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
			if(ptr2->get_type()==WRITE) {
				cout << ptr2->get_value()->get_value()->get_name() << endl;
			}
		}
	}
};


void parser(Token *node) {

	if(!node)
		return;

	Token *next = node->get_next();


	parser(next);

	if(node->get_type()== VARIABLE) {
		if(!is_defined(node->get_name())) define(node);
	}
	if(next && next->get_type() == WRITE) {
		if(node->get_type()==VARIABLE) {
			Token *var_ptr = is_defined(node->get_name()); // Where defined?
			next->set_value(var_ptr);
		}
		else
			next->set_value(node);
	}

	// If next node equal operator, set this node to variable on the other side of the equal.
	// Then this node should point at variable and now safely delete equal operator from LL.
	if(next && next->get_type()== ASSIGNMENT) {
		Token *var_ptr = next->get_next();

		var_ptr->set_value(node);
			

		node->set_next(var_ptr);
		delete next;
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
	if(s[0] == '=')
		return ASSIGNMENT;
	else if(s[0] == '+') 
		return ADDITION;
	else if(s[0] == '-') 
		return SUBTRACTION;
	else if(s[0] == '*') 
		return MULTIPLICATION;
	else if(s[0] == '/')
		return DIVISION;
	else if(s[0] == '%')
		return MODULO;
	else if(strings_match(s, (char*)"==")) 
		return COMPARISON;

};







