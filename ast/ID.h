#ifndef ID_H

#define ID_H

#include <string>
#include "ast_t.h"
#include "../lexer/token/Token.h"



class ID {

private:

	std::string value;

public:
	
	/*
	 +++++ C'Tor for moving std::string value from token to ID +++++
	*/
	ID(Token &&token);

	/*
	 +++++ Move C'Tor +++++
	 */
	ID(ID&& idObj);


}; // ID

#endif