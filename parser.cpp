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
		next->set_value(previous);
		previous->set_next(next);
		delete current;

	}
	else if (current_type == WRITE) 
		current->set_value(is_declared(previous->get_name()));

};