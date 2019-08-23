
#ifndef NUM_H

#define NUM_H

#include "ast_t.h"
#include "../lexer/token/Token.h"




class Num {

private:

	size_t value;

public:


	/*
	 +++++ Accessors +++++
	 */
	size_t getValue() const;


	/*
	 +++++ MAIN C'TOR +++++
	 */
	
	/*
	 +++++ C'Tor for copying number value from token +++++
	 */

	Num(const Token &token);

	/*
	 +++++ COPY C'TOR +++++
	 */
	// Num(const Num &numObj) = delete;

	/*
	 +++++ Moves for calling std::Numing move C'tor +++++
	 */

	/*
	 +++++ MOVE C'TOR +++++
	 */
	// Num(Num&& numObj);

	/*
	 +++++ MOVE ASSIGN +++++
	 */
	// Num& operator=(Num&& numObj);


}; // Num

#endif