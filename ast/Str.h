#ifndef STR_H

#define STR_H


class Str {

private:

	std::string value;

public:
	
	/*
	 +++++ C'Tor for moving std::string value from token to Str +++++
	 */

	Str(Token &&token)	
		:value(std::move(token.value))
	{}


}; // Str


#endif