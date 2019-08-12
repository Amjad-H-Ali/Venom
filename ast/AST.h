#ifndef AST_H

#define AST_H

#include "Str.h"
#include "ID.h"
#include "List.h"
#include "Block.h"
#include "Func.h"
#include "Assign.h"
#include "Add.h"


template<typename T>

class AST {

private:

	T value;

public:


	/*
	 +++++ Construct T object emplace +++++
	 */
	template<typename ... Params>

	AST(Params&& ... argsOfT);

	AST(AST&& astObj);

	AST& operator=(AST&& astObj);

}; // AST






#endif


