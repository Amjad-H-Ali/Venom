#include <iostream>
#include <fstream>
#include "lexer.h"

using namespace std;

void lexer(char *file_name);

Token *head = NULL;
int main() {

	
	lexer("new.vnm");


	return 0;
}

void lexer(char *file_name) {
	char data;
	ifstream in_file;
	in_file.open(file_name);

	
	while(in_file >> data) {
		

		if(data == '{') {
			Token *new_tok = new Token;
			new_tok->TYPE  = "RBRACE";
			new_tok->VALUE = '{';
			new_tok->NEXT  = head;
			head           = new_tok;
		}
		else if(data == 'a') {
			Token *new_tok = new Token;
			new_tok->TYPE  = "CHAR";
			new_tok->VALUE = 'a';
			new_tok->NEXT  = head;
			head           = new_tok;
		}
	}
	in_file.close();

	cout << head->VALUE << head->NEXT->VALUE << endl;

}