#include <iostream>
#include "parser.h"
using namespace std;

void parser(Token *node) {

	if(!node)
		return;

	Token *next = node->get_next();


	parser(next);

	if(node->get_type()== VARIABLE) {
		if(!is_declared(node->get_name())) declare(node);
	}
	if(next && next->get_type() == WRITE) {
		if(node->get_type()==VARIABLE) {
			Token *var_ptr = is_declared(node->get_name()); // Where defined?
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