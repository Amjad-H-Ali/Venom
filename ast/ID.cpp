#include "ID.h"


/*
 +++++ Accessors +++++
 */
const std::string& ID::getName() const {
	return value;
}

/*
 +++++ MAIN C'TOR +++++
 */
/*
 +++++ C'Tor for moving std::string value from token to ID +++++
 */
ID::ID(Token&& token)	
	:value(std::move(token.getValue()))
{}



/*
 +++++ COPY C'TOR +++++
 */
// ID::ID(const ID &idObj)
// 	:value(idObj.value)
// {}


/*
 +++++ Moves for calling std::string move C'tor +++++
 */
/*
 +++++ MOVE C'TOR +++++
 */
ID::ID(ID&& idObj)
	:value(std::move(idObj.value))
{}


/*
 +++++ MOVE ASSIGN +++++
 */
ID& ID::operator=(ID&& idObj) {
	value = std::move(idObj.value);

	return *this;
}
