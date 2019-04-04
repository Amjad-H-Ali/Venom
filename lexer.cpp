#include "lexer.h"


Stmnt *stmnt_node = new Stmnt;


void lexer(char *file_name) {
	stmnt_node->value = NULL;
	stmnt_node->next = NULL;

	ifstream in;
	in.open(file_name);
	string s;
	Token *new_tok_node;

	while(in >> s){
		
		if(s[0] == '"') {
			new_tok_node = new STRING(&s[1]);
			new_tok_node->set_next(stmnt_node->value);
			stmnt_node->value = new_tok_node;

		}
		else if((s[0] > 'a' && s[0] < 'z') || (s[0] >'A' && s[0] < 'Z')) {
			new_tok_node = new VAR(&s[0]);
			new_tok_node->set_next(stmnt_node->value);
			stmnt_node->value = new_tok_node;

		}
		else if(s[0] == '=') {
			new_tok_node = new OPERATOR(&s[0]);
			new_tok_node->set_next(stmnt_node->value);
			stmnt_node->value = new_tok_node;
		}
	};

	int eq_count = 0,
		str_count = 0,
		var_count = 0;
	for(Stmnt *ptr = stmnt_node; ptr != NULL; ptr = stmnt_node->next) {
		for(Token *ptr2 = ptr->value; ptr2 != NULL; ptr2 = ptr2->next()) {
			cout << ptr2->get_value() << endl;
			if(ptr2->get_type() == OPER)

				eq_count ++;
			else if(ptr2->get_type() == VARIABLE)
				var_count++;
			else if(ptr2->get_type()== STR)
				str_count++;
		}
	}
	cout << "EQ: " << eq_count << " STR: " << str_count << " VAR: " << var_count << endl;
};