#include <iostream>
#include <fstream>

using namespace std;

void lexer(ifstream &in_file);

int main() {

	ifstream in_file;

	in_file.open("new.grim");

	lexer(in_file);


	return 0;
}


void lexer(ifstream &in_file) {
	char data;
	while(in_file >> data) {
		cout << data;
	}

	cout << endl;
}