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
	 +++++ MAIN C'TOR +++++
	 */
	
	/*
	 +++++ C'Tor for moving std::string value from token to ID +++++
	*/
	ID(Token &&token);

	/*
	 +++++ Moves for calling std::string move C'tor +++++
	 */
	/*
	 +++++ MOVE C'TOR +++++
	 */
	ID(ID&& idObj);


	/*
	 +++++ MOVE ASSIGN +++++
	 */
	ID& operator=(ID&& idObj);


}; // ID

#endif