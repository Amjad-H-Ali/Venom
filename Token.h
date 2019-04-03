#pragma once

enum Type {
		VARIABLE,
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
	virtual char *get_value() const = 0;
	virtual int  get_len() const = 0;
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



