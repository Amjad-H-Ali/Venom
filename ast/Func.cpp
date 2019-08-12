#include "Func.h"

/*
 +++++ Forward arguments to List and Block to construct params and body emplace +++++
 */
template<typename ListArg, typename BlockArg>

Func::Func(ListArg&& listVal, BlockArg&& blockVal)

	:params(std::forward<ListArg>(listVal)), body(std::forward<BlockArg>(blockVal))
{}


Func::Func(Func&& funcObj)

	:params(std::move(funcObj.params)), body(std::move(funcObj.body)) 
{}