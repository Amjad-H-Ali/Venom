#pragma once

enum Type {
		VARIABLE,
		OPER,
		STR,
};

class Token {
protected:
	Type type;
	Token *Next;
	Token(Type type);
public:
	Type get_type() const;
	void set_type(Type type);
	virtual char *get_value() const = 0;
	virtual int  get_len() const = 0;
	virtual Token *next() = 0;
	virtual void set_next(Token *tok_ptr) = 0;
	virtual Token *get_left() const {};
	virtual void set_left(Token *tok_ptr) {};
	virtual void set_right(Token *tok_ptr) {};
	virtual Token *get_right() const {};
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



