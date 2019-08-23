#ifndef ID_H

#define ID_H

#include <string>
#include "ast_t.h"
#include "../lexer/token/Token.h"



class ID {

private:

	std::string value;

public:

	const std::string& tempGetVal() const {
		return value;
	}

	/*
	 +++++ Accessors +++++
	 */
	const std::string& getName() const;


	/*
	 +++++ MAIN C'TOR +++++
	 */
	
	/*
	 +++++ C'Tor for moving std::string value from token to ID +++++
	*/
	ID(Token&& token);

	/*
	 +++++ COPY C'TOR +++++
	 */
	ID(const ID &idObj) = delete;

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