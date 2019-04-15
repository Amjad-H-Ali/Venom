#include <iostream>
#include "parser.h"
using namespace std;

void parser(Token *current, Token *previous) {
	// cout<<current<<endl;
	if(!current)
		return;


	Token *next = current->get_next();

	parser(next, current);
	cout << "Good\n";
	// cout << "Next: " << next->get_name()<< "Current: " << current->get_name()<<endl;
	Type current_type = current->get_type();
	if((current_type == VARIABLE) && (is_declared(current->get_name())== NULL )) {
		declare(current);
	}
	else if(current_type == ASSIGNMENT) {
		next->set_value(previous);
		previous->set_next(next);
		delete current;

	}
	else if (current_type == WRITE) 
		current->set_value(is_declared(previous->get_name()));
	

	// if(node->get_type()== VARIABLE) {
	// 	if(!is_declared(node->get_name())) declare(node);
	// }
	// if(next && next->get_type() == WRITE) {
	// 	if(node->get_type()==VARIABLE) {
	// 		Token *var_ptr = is_declared(node->get_name()); // Where defined?
	// 		next->set_value(var_ptr);
	// 	}
	// 	else
	// 		next->set_value(node);
	// }

	// // If next node equal operator, set this node to variable on the other side of the equal.
	// // Then this node should point at variable and now safely delete equal operator from LL.
	// if(next && next->get_type()== ASSIGNMENT) {
	// 	Token *var_ptr = next->get_next();

	// 	var_ptr->set_value(node);
			

	// 	node->set_next(var_ptr);
	// 	delete next;
	// }
};