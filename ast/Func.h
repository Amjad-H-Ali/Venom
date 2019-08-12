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

	template<typename ListArg, typename BlockArg>

	/*
	 +++++ Forward arguments to List and Block to construct params and body emplace +++++
	 */

	Func(ListArg&& listVal, BlockArg&& blockVal);


	Func(Func&& funcObj);

}; // Func

#endif