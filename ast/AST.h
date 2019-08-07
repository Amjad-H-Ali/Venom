#ifndef AST_H

#define AST_H


template<typename T>

class AST {

private:

	T value;

public:
	/*
	 +++++ Construct T object emplace +++++
	 */
	template<typename ... Params>

	AST(Params&& ... argsOfT)

		:T(std::forward<Params>(argsOfT)...)

	{};

};

typedef std::variant< AST<Str>, AST<ID>, AST<List> , AST<Block>, AST<Func>, AST<BinOp> > ast_t;

#endif


