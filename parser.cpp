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
	
	if(current_type == ASSIGNMENT) {
		// The Variable
		is_declared(next->get_name())->set_value(previous);
		// Another datatype (eg. STRING)
		previous->set_next(next);
		// Delete the Operator from the Linked List.
		delete current;

	}
	
	else if (current_type == WRITE) 
		current->set_value(is_declared(previous->get_name()));


};