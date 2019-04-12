#pragma once


enum Type {
	STRING,
	NUMBER,
	ADDITION,
	SUBTRACTION,
	DIVISION,
	MULTIPLICATION,
	MODULO,
	ASSIGNMENT,
	VARIABLE,
	FUNCTION,
	WRITE
		
};	

class Token {
private:
	Type type;
	char *name;
	int name_len;
	Token *next;
public:
	Token(char *name, Type type);
	~Token();
	void set_type(Type type);
	Type get_type() const;
	void set_name(char *name);
	char *get_name() const;
	void set_name_len(char *name);
	int get_name_len() const;
	void *set_next(Token *tok_ptr);
	Token *get_next() const;

	// virtual char *get_value() const = 0;
	// virtual int  get_len() const = 0;
	// virtual Token *next() = 0;
	// virtual void set_next(Token *tok_ptr) = 0;
	// virtual Token *get_left() const {};
	// virtual void set_left(Token *tok_ptr) {};
	// virtual void set_right(Token *tok_ptr) {};
	// virtual Token *get_right() const {};
	// virtual Token *get_tok_value() const {};
	// virtual void  set_tok_value(Token *tok_ptr){}; 
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



