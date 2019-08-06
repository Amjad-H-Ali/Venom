#ifndef AST_H

#define AST_H


template<typename T>

class AST {

private:

	const T &value;

public:

	AST(const T &tObject);

};

typedef std::variant< AST<Str>, AST<ID>, AST<List> , AST<Block>, AST<Func>, AST<BinOp> > ast_t;

#endif


