#include "Str.h"

/*
 +++++ MAIN C'TOR +++++
 */
/*
 +++++ C'Tor for moving std::string value from token to Str +++++
 */

Str::Str(Token &&token)	
	:value(std::move(token.getValue()))
{}

/*
 +++++ Moves for calling std::string move C'tor +++++
 */
/*
 +++++ MOVE C'TOR +++++
 */
Str::Str(Str&& strObj)
	:value(std::move(strObj.value))
{}


/*
 +++++ MOVE ASSIGN +++++
 */
Str& Str::operator=(Str&& strObj) {
	
	value = std::move(strObj.value);
}