#include <iostream>
#include <fstream>
#include <iomanip>
#include "STRING.h"
#include "VAR.h"
#include "OPERATOR.h"


using namespace std;

// void lexer(char *file_name);

// Statement *stmnts = new Statement;


int main() {

	ifstream in("new.vnm");
	string s;
	STRING *ptr1;
	VAR    *ptr2;


	while(in >> s){
		if(s[0] == '"') {
						//Address to (H)ello
			
			ptr1 = new STRING(&s[1]);

			//0x7ffeeb3a02f8 -- That's OK
			cout << ptr1 << endl;
		}
		else if((s[0] > 'a' && s[0] < 'z') || (s[0] >'A' && s[0] < 'Z')) {
					//Address to (f)oo

			ptr2 = new VAR(&s[0]);

			// 0x7ffeeb3a02d8 -- This is OK.
			cout << ptr2 << endl;

			// Value stored at ptr2 -- Prints foo -- That's OK.
			for(int i = 0; ptr2->get_value()[i]; i ++)
				cout << ptr2->get_value()[i];
			cout << endl;
		}
	};

	// 0x7ffeeb3a02d8 -- That's OK
	cout << ptr2 << endl;


	// Printing Value stored at ptr2 -- Hello -- This is NOT OK!
	for(int i = 0; ptr2->get_value()[i]; i ++)
		cout << ptr2->get_value()[i];
	cout << endl;

	// Printing Value stored at ptr1 -- That's OK.
	for(int i = 0; ptr1->get_value()[i]; i ++)
		cout << ptr1->get_value()[i];
	cout << endl;

	delete ptr1;
	delete ptr2;
	
	
	return 0;
}

// void lexer(char *file_name) {
	
// 	ifstream  in_file;
// 	in_file.open(file_name);
// 	char data;
	

// 	while(in_file >> data) {
// 		Token *new_tok = new Token;
// 		new_tok->VALUE = data;


// 		if(data == '{')
// 			new_tok->TYPE  = "LBRACE";
// 		else if(data == '}')
// 			new_tok->TYPE  = "RBRACE";
// 		else if(data == '(') 
// 			new_tok->TYPE  = "LPARENTHESIS";
// 		else if(data == ')') 
// 			new_tok->TYPE  = "RPARENTHESIS";
// 		else if((data >= 'a' && data <= 'z') || (data >= 'A' && data <= 'Z')) 
// 			new_tok->TYPE  = "LETTER";
// 		else if(data >= '0' && data <= '9') 
// 			new_tok->TYPE  = "DIGIT";
// 		else if(data == '.') 
// 			new_tok->TYPE  = "DOT";
// 		else if(data == '<') 
// 			new_tok->TYPE  = "LESS";
// 		else if(data == '>') 
// 			new_tok->TYPE  = "GREATER";
// 		else if(data == '=') 
// 			new_tok->TYPE  = "EQUAL";
// 		else if(data == '|') 
// 			new_tok->TYPE  = "BAR";
// 		else if(data == '+') 
// 			new_tok->TYPE  = "PLUS";
// 		else if(data == '-') 
// 			new_tok->TYPE  = "MINUS";
// 		else if(data == '*') 
// 			new_tok->TYPE  = "STAR";
// 		else if(data == '/') 
// 			new_tok->TYPE  = "FSLASH";
// 		else if(data == '\\') 
// 			new_tok->TYPE  = "BSLASH";
// 		else if(data == '[') 
// 			new_tok->TYPE  = "LBRACKET";
// 		else if(data == ']') 
// 			new_tok->TYPE  = "RBRACKET";
// 		else if(data == ',') 
// 			new_tok->TYPE  = "COMMA";
// 		else if(data == '\'') 
// 			new_tok->TYPE  = "APOSTROPHE";
// 		else if(data == '\"') 
// 			new_tok->TYPE  = "QUOTATION";
// 		else if(data == '!') 
// 			new_tok->TYPE  = "EXCLAMATION";
// 		else if(data == '?') 
// 			new_tok->TYPE  = "QUESTION";
// 		else if(data == ':') 
// 			new_tok->TYPE  = "COLON";
// 		else if(data == '%') 
// 			new_tok->TYPE  = "MODULO";
// 		else if(data == '^') 
// 			new_tok->TYPE  = "CARROT";
// 		else if(data == '#') 
// 			new_tok->TYPE  = "HASH";
// 		else if(data == '@') 
// 			new_tok->TYPE  = "AT";
// 		else if(data == '$') 
// 			new_tok->TYPE  = "DOLLAR";
// 		else if(data == '_') 
// 			new_tok->TYPE  = "UNDERSCORE";
// 		else if(data == ';') {
// 			new_tok->TYPE  = "SEMICOLON";
// 			Statement *new_stmnts = new Statement;
// 			new_stmnts->NEXT = stmnts;
// 			stmnts           = new_stmnts;
			
// 		}
// 		new_tok->NEXT  = stmnts->VALUE;
// 		stmnts->VALUE  = new_tok;

// 	}
// 	in_file.close();

// 	for(Statement *ptr  = stmnts; ptr; ptr = ptr->NEXT){
// 			cout << "-----------------------------\n";
// 		for(Token *ptr2 = ptr->VALUE; ptr2; ptr2 = ptr2->NEXT) {
// 			cout << ptr2->TYPE << '\n' << endl;
// 		}
// 	}


// }