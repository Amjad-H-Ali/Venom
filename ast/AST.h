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

	AST<T>(Params&& ... argsOfT)

		:value(std::forward<Params>(argsOfT)...)

	{}

	AST<T>(AST<T>&& astObj)
		:value(std::move(astObj.value))
	{}

};

typedef std::variant< AST<Str>, AST<ID>, AST<List> , AST<Block>, AST<Func>, AST<Assign>, AST<Add> > ast_t;

#endif


