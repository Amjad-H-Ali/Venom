
#ifndef STR_H

#define STR_H


#include <string>
#include "ast_t.h"
#include "../lexer/token/Token.h"




class Str {

private:

	std::string value;

public:
	
	/*
	 +++++ C'Tor for moving std::string value from token to Str +++++
	 */

	Str(Token &&token);

	/*
	 +++++ Move C'Tor +++++
	 */
	Str(Str&& strObj);


}; // Str

#endif