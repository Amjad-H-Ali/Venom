#pragma once


enum Type {
		VARIABLE,
		OPER,
		STR,
		WRITE
};

class Token {
protected:
	Type type;
	Token *Next;
	Token(Type type);
	Token(){};
public:
	virtual ~Token(){};
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
	virtual Token *get_tok_value() const {};
	virtual void  set_tok_value(Token *tok_ptr){};
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



