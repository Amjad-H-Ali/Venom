#include <iostream>
#include "Declarations.h"


Declared *head = new Declared;

void declare(Token *token_ptr) {
	char *name = token_ptr->get_name();
	int i = 0;
	Declared *current_ptr = head;
	while(name[i] != '\0') {

		int indx = hash(name[i]);
		current_ptr->paths[indx] == NULL ? current_ptr->paths[indx] = new Declared : NULL; //Do Nothing
		current_ptr = current_ptr->paths[indx];
		i ++;
	}
	std::cout<< name << " was Declared.\n";
	current_ptr->token_address = token_ptr;
};

Token *is_declared(char *name) {
	int i = 0;
	Declared *current_ptr = head;
	std::cout<<"Checking if  " << name << " is in Dictionary.\n";
	while(name[i] != '\0') {
		int indx = hash(name[i]);
		std::cout << name[i] << ": " << indx << " " << current_ptr->paths[indx] << '\n'<< std::endl;
		if(!current_ptr->paths[indx]) {
			std::cout<< name << " is NOT in Dictionary.\n";
			return NULL;
		}
		current_ptr = current_ptr->paths[indx];
		i++;
	}
	std::cout<<"Checked " << name << " in Dictionary and it's in here..\n";
	return current_ptr->token_address;
};

int hash(const char &letter) {
	int indx = (letter >= 'A' && letter <= 'Z') ? letter - 'A' : letter - 'a';
	return indx;
};

