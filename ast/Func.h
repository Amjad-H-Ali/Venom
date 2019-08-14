#ifndef FUNC_H

#define FUNC_H

#include "ast_t.h"
#include "List.h"
#include "Block.h"


class Func {

private:

	List  params;

	Block body;


public:

	const List& tempGetParams() const {
		return params;
	}

	const Block& tempGetBody() const {
		return body;
	}


	/*
	 +++++ MAIN C'TOR +++++
	 */
	template<typename ListArg, typename BlockArg>

	/*
	 +++++ Forward arguments to List and Block to construct params and body emplace +++++
	 */

	Func(ListArg&& listVal, BlockArg&& blockVal)

		:params(std::forward<ListArg>(listVal)), body(std::forward<BlockArg>(blockVal))
	{}

	/* 
	 +++++ COPY C'TOR +++++
	 */

	Func(const Func& funcObj) = delete;


	/*
	 +++++ Move C'tors for calling Move C'tors of List and Block type data members +++++
	 */

	/* 
	 +++++ MOVE C'TOR +++++
	 */

	Func(Func&& funcObj);


	/* 
	 +++++ MOVE ASSIGN +++++
	 */

	Func& operator=(Func&& funcObj);


}; // Func

#endif