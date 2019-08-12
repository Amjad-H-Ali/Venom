
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

typedef std::variant< AST<Str>, AST<ID>, AST<List> , AST<Block>, AST<Func>, AST<Assign>, AST<Add> > ast_t;


#endif