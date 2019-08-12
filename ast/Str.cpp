#include "Str.h"


/*
 +++++ C'Tor for moving std::string value from token to Str +++++
 */

Str::Str(Token &&token)	
	:value(std::move(token.getValue()))
{}

/*
 +++++ Move C'Tor +++++
 */
Str::Str(Str&& strObj)
	:value(std::move(strObj.value))
{}