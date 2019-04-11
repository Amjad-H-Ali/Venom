#include <iostream>
#include <fstream>
#include "lexer.h"
#include "Definitions.h"
// #include <string>


using namespace std;


Stmnt *stmnt_node = new Stmnt;


void parser(Token *node);

void lexer(char *file_name) {
	cout << "Size: " << sizeof(Stmnt) << endl;

	stmnt_node->value = NULL;
	stmnt_node->next = NULL;

	ifstream in;
	in.open(file_name);
	string s;
	Token *new_tok_node;

	while(in >> s){
		
		if(s[0] == '"') {
			new_tok_node = new STRING(&s[1]);
			// new_tok_node->set_next(stmnt_node->value);
			// stmnt_node->value = new_tok_node;

		}
		else if((s[0] > 'a' && s[0] < 'z') || (s[0] >'A' && s[0] < 'Z')) {
			new_tok_node = new VAR(&s[0]);
			// new_tok_node->set_next(stmnt_node->value);
			// stmnt_node->value = new_tok_node;

		}
		else if(s[0] == '=') {
			new_tok_node = new OPERATOR(&s[0]);
			// new_tok_node->set_next(stmnt_node->value);
			// stmnt_node->value = new_tok_node;
		}

		new_tok_node->set_next(stmnt_node->value);
		stmnt_node->value = new_tok_node;
	};

	parser(stmnt_node->value);

	// int eq_count = 0,
	// 	str_count = 0,
	// 	var_count = 0;
	for(Stmnt *ptr = stmnt_node; ptr; ptr = stmnt_node->next) {
		for(Token *ptr2 = ptr->value; ptr2; ptr2 = ptr2->next()) {
			// cout << ptr2->get_value() << endl;
			// if(ptr2->get_type() == VARIABLE) {
			// 	cout << ptr2->get_tok_value()<< endl;
			// 	// cout << ptr2->get_tok_value()->get_value()<< endl;
			// }
			if(ptr2->get_type()==WRITE) {
				cout << ptr2->get_tok_value()->get_tok_value()->get_value() << endl;
			}
			// 
			// if(ptr2->get_type() == OPER) {
			// 	cout << ptr2->get_left()->get_value() << endl;
			// 	cout << ptr2->get_right()->get_value() << endl;
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
		if(!is_defined(node->get_value())) define(node);
	}
	if(next && next->get_type() == WRITE) {
		// Token *var_ptr;
		if(node->get_type()==VARIABLE) {
			Token *var_ptr = is_defined(node->get_value()); // Where defined?
			next->set_tok_value(var_ptr);
		}
		// if(var_ptr)
		// 	next->set_tok_value(var_ptr);
		else
			next->set_tok_value(node);
	}

	// If next node equal operator, set this node to variable on the other side of the equal.
	// Then this node should point at variable and now safely delete equal operator from LL.
	if(next && next->get_type()== OPER) {
		Token *var_ptr = next->next();
		      // *exists = is_defined(var_ptr->get_value());

		// if(exists) 
		// 	exists->set_tok_value(node);
		
		// else 
		var_ptr->set_tok_value(node);
			

		node->set_next(var_ptr);
		delete next;


		// Token *var_ptr = next->next();
		// var_ptr->set_tok_value(node);
		
		// next->set_right(node);
		// next->set_left(var_ptr);
	}




};








