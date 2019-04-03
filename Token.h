#pragma once

enum Type {
		VAR,
		EQ,
		STR,
};

class Token {
private:
	Type type;
protected:
	Token(Type type);
public:
	Type get_type() const;
	void set_type(Type type);
};
// struct STRING {
// 	int LEN;
// 	char *VALUE;
// }

// struct VAR {
// 	char *NAME;


// }

// struct Statement {
// 	Token      *VALUE = NULL;
// 	Statement  *NEXT  = NULL;
// };



