#include "Str.h"


/*
 +++++ Accessors +++++
 */
const std::string& Str::getValue() const {
	return value;
}

/*
 +++++ MAIN C'TOR +++++
 */
/*
 +++++ C'Tor for moving std::string value from token to Str +++++
 */

Str::Str(Token&& token)	
	:value(std::move(token.getValue()))
{}

/*
 +++++ COPY C'TOR +++++
 */
// Str::Str(const Str &strObj)
// 	:value(strObj.value)
// {}


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

	return *this;
}