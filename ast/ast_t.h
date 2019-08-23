
#ifndef AST_T_H
#define AST_T_H

#include <variant>


template<typename T>
class AST;

class Str;

class ID;

class List;

class Block;

class Func;

class Assign;

class Add;

class Output;

class Num;

class Call;

class Write;

typedef std::variant< AST<Str>, AST<ID>, AST<List> , AST<Block>, AST<Func>, AST<Assign>, AST<Add>, AST<Output>, AST<Num>, AST<Call>, AST<Write> > ast_t;


#endif