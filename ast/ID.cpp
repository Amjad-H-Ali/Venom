#include "ID.h"

/*
 +++++ C'Tor for moving std::string value from token to ID +++++
 */
ID::ID(Token &&token)	
	:value(std::move(token.getValue()))
{}

/*
 +++++ Move C'Tor +++++
 */
ID::ID(ID&& idObj)
	:value(std::move(idObj.value))
{}
