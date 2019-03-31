#pragma once 

struct STRLIST {
	int  len;
	char string[len];
	STRLIST *next;
};


void lexer(char *file_name);