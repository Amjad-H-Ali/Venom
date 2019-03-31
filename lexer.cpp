#include <iostream>
#include <fstream>
#include "lexer.h"

using namespace std;

int main() {

	lexer("new.grim");


	return 0;
}


void lexer(char *file_name) {
	char data;
	ifstream in_file;
	in_file.open(file_name);

	STRLIST str_list;

	while(in_file >> data) {
		if(data == '\"'){
			for(int i = 0; in_file >> data; i ++) {
				if(data == '\"') {
					str_list.string[i] = '\0';
					break;
				}
				str_list.string[i] = data;
			}

		}


	}
	

	cout << str_list.string << endl;
}