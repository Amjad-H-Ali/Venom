#ifndef ID_H

#define ID_H


class ID {

private:

	std::string value;

public:
	
	/*
	 +++++ C'Tor for moving std::string value from token to ID +++++
	 */

	ID(Token &&token)	
		:value(std::move(token.value))
	{}


}; // ID


#endif