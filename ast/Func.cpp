#include "Func.h"



/*
 +++++ Accessors +++++
 */

const List& Func::getParamList() const {
	return params;
}

const Block& Func::getBody() const {
	return body;
}

/* 
 +++++ COPY C'TOR +++++
 */

// Func::Func(const Func& funcObj)

// 	:params(funcObj.params), body(funcObj.body)
// {}


/*
 +++++ Move C'tors for calling Move C'tors of List and Block type data members +++++
 */

/* 
 +++++ MOVE C'TOR +++++
 */

Func::Func(Func&& funcObj)

	:params(std::move(funcObj.params)), body(std::move(funcObj.body)) 
{}



/* 
 +++++ MOVE ASSIGN +++++
 */

Func& Func::operator=(Func&& funcObj) {

	params = std::move(funcObj.params);

	body = std::move(funcObj.body);

	return *this;

}

