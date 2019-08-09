#ifndef FUNC_H

#define FUNC_H


class Func {

private:

	List  params;

	Block body;


public:

	template<typename ListArgs, typename BlockArgs>

	/*
	 +++++ Forward arguments to List and Block to construct params and body emplace +++++
	 */

	Func(ListArg&& listVal, BlockArg&& blockVal)

		:params(std::forward<ListArg>(listVal)), body(std::forward<BlockArgs>(blockVal))
	{}

	Func(Func&& funcObj)

		:params(std::move(funcObj.params)), body(std::move(funcObj.body)) 
	{}

}; // Func



#endif

