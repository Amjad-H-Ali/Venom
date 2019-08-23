#include "Num.h"


/*
 +++++ Accessors +++++
 */
size_t Num::getValue() const {
	return value;
}

/*
 +++++ MAIN C'TOR +++++
 */
/*
 +++++ C'Tor for moving std::string value from token to Str +++++
 */

Num::Num(const Token &token)	
	:value(token.getNumber())
{}

/*
 +++++ COPY C'TOR +++++
 */
// Num::Num(const Num &numObj)
// 	:value(numObj.value)
// {}


/*
 +++++ Moves for calling std::Numing move C'tor +++++
 */
/*
 +++++ MOVE C'TOR +++++
 */
// Num::Num(Num&& numObj)
// 	:value(std::move(numObj.value))
// {}


/*
 +++++ MOVE ASSIGN +++++
 */
// Num& Num::operator=(Num&& numObj) {

// 	value = std::move(numObj.value);

// 	return *this;
// }