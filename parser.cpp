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
	if((current_type == VARIABLE || current_type == FUNCTION || current_type == ARRAY) && (is_declared(current->get_name())== NULL )) {
		declare(current);
		if(current_type == FUNCTION) {
			Token *params = current->get_parameters();
			while(params != NULL) {
				declare(params);
				params = params->get_next();
			}
		}
	}
	else if(current_type == ASSIGNMENT) {
		next->set_value(previous);
		previous->set_next(next);
		delete current;

	}
	else if (current_type == WRITE)
		previous->get_type() == STRING ? current->set_value(previous) : current->set_value(is_declared(previous->get_name()));
	else if (current_type == FUNCTIONCALL) {
		Token *func_def = is_declared(current->get_name());
		Token *params = func_def->get_parameters();
		Token *args = current->get_arguments();
		while(params != NULL && args != NULL) {

			is_declared(params->get_name())->set_value(is_declared(args->get_name()));
			params = params->get_next();
			args = args->get_next();
		}
		parser(func_def->get_block(), current);
	}
	
};