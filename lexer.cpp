#include <iostream>
#include <fstream>
#include "lexer.h"
#include "Definitions.h"
// #include <string>


using namespace std;


Tokens *node = new Tokens;


void parser(Tokens *node);

void lexer(char *file_name) {
	cout << "Size: " << sizeof(Stmnt) << endl;

	node->token_node = NULL;
	node->next = NULL;

	ifstream in;
	in.open(file_name);
	string s;
	Token *new_token_node;

	while(in >> s){
		
		if(s[0] == '"' || s[0] == "'") {
			parse_string(s, in);

			new_token_node = new Token(&s[1], STRING);
			// new_token_node->set_next(node->token_node);
			// node->token_node = new_token_node;

		}
		else if((s[0] > 'a' && s[0] < 'z') || (s[0] >'A' && s[0] < 'Z')) {
			new_token_node = new VAR(&s[0]);
			// new_token_node->set_next(node->token_node);
			// node->token_node = new_token_node;

		}
		else if(s[0] == '=') {
			new_token_node = new OPERATOR(&s[0]);
			// new_token_node->set_next(node->token_node);
			// node->token_node = new_token_node;
		}

		new_token_node->set_next(node->token_node);
		node->token_node = new_token_node;
	};

	parser(node->token_node);

	// int eq_count = 0,
	// 	str_count = 0,
	// 	var_count = 0;
	for(Stmnt *ptr = node; ptr; ptr = node->next) {
		for(Token *ptr2 = ptr->token_node; ptr2; ptr2 = ptr2->next()) {
			// cout << ptr2->get_token_node() << endl;
			// if(ptr2->get_type() == VARIABLE) {
			// 	cout << ptr2->get_tok_token_node()<< endl;
			// 	// cout << ptr2->get_tok_token_node()->get_token_node()<< endl;
			// }
			if(ptr2->get_type()==WRITE) {
				cout << ptr2->get_tok_token_node()->get_tok_token_node()->get_token_node() << endl;
			}
			// 
			// if(ptr2->get_type() == OPER) {
			// 	cout << ptr2->get_left()->get_token_node() << endl;
			// 	cout << ptr2->get_right()->get_token_node() << endl;
			// }
			// 	eq_count ++;
			// else if(ptr2->get_type() == VARIABLE)
			// 	var_count++;
			// else if(ptr2->get_type()== STR)
			// 	str_count++;
		}
	}
	// cout << "EQ: " << eq_count << " STR: " << str_count << " VAR: " << var_count << endl;
};


void parser(Token *node) {

	if(!node)
		return;

	Token *next = node->next();


	parser(next);

	if(node->get_type()== VARIABLE) {
		if(!is_defined(node->get_token_node())) define(node);
	}
	if(next && next->get_type() == WRITE) {
		// Token *var_ptr;
		if(node->get_type()==VARIABLE) {
			Token *var_ptr = is_defined(node->get_token_node()); // Where defined?
			next->set_tok_token_node(var_ptr);
		}
		// if(var_ptr)
		// 	next->set_tok_token_node(var_ptr);
		else
			next->set_tok_token_node(node);
	}

	// If next node equal operator, set this node to variable on the other side of the equal.
	// Then this node should point at variable and now safely delete equal operator from LL.
	if(next && next->get_type()== OPER) {
		Token *var_ptr = next->next();
		      // *exists = is_defined(var_ptr->get_token_node());

		// if(exists) 
		// 	exists->set_tok_token_node(node);
		
		// else 
		var_ptr->set_tok_token_node(node);
			

		node->set_next(var_ptr);
		delete next;


		// Token *var_ptr = next->next();
		// var_ptr->set_tok_token_node(node);
		
		// next->set_right(node);
		// next->set_left(var_ptr);
	}




};

void parse_string(string &s, ifstream &in) {
	string left_over;
	int last_indx = s.length() - 1;

	while(s[last_indx] != '\'' && s[last_indx] != '"') {
		in >> left_over;
		s+= left_over;
		last_indx = s.length() - 1;
	}
};








