#include <iostream>
#include "Definitions.h"


Defined *head = new Defined;

void define(Token *token_ptr) {
	char *name = token_ptr->get_value();
	int i = 0;
	Defined *current_ptr = head;
	while(name[i] != '\0') {
		int indx = hash(name[i]);
		current_ptr->paths[indx] = new Defined;
		current_ptr = current_ptr->paths[indx];
		i ++;
	}
	current_ptr->token_address = token_ptr;
};

Token *is_defined(char *name) {
	// std::cout << "NAME: " << name << '\n' << std::endl;
	int i = 0;
	Defined *current_ptr = head;

	while(name[i] != '\0') {
		int indx = hash(name[i]);
		// std::cout << "HASH FOR LETTER: " << name[i] << " is " << hash(name[i]) << '\n' << std::endl;
		if(!current_ptr->paths[indx])
			return NULL;
		current_ptr = current_ptr->paths[indx];
		i++;
	}
	// std::cout << "Found AN EXISTING NAME: " << current_ptr->token_address->get_value() << '\n' << std::endl;
	return current_ptr->token_address;
};

int hash(char letter) {
	int indx = (letter >= 'A' && letter <= 'Z') ? letter - 'A' : letter - 'a';
	return indx;
};
