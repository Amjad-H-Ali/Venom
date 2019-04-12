#include <iostream>
#include "Definitions.h"


Defined *head = new Defined;

void define(Token *token_ptr) {
	char *name = token_ptr->get_name();
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
	int i = 0;
	Defined *current_ptr = head;

	while(name[i] != '\0') {
		int indx = hash(name[i]);
		if(!current_ptr->paths[indx])
			return NULL;
		current_ptr = current_ptr->paths[indx];
		i++;
	}
	return current_ptr->token_address;
};

int hash(char letter) {
	int indx = (letter >= 'A' && letter <= 'Z') ? letter - 'A' : letter - 'a';
	return indx;
};

