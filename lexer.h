#pragma once 

struct Token {
	char  *TYPE;
	char   VALUE;
	Token *NEXT = NULL;
};

struct Statement {
	Token      *VALUE = NULL;
	Statement  *NEXT  = NULL;
};



