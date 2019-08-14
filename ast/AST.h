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

	const T& tempGetVal() const {
		return value;
	}

	/*
	 +++++ MAIN C'TOR +++++
	 */
	/*
	 +++++ Construct T object emplace +++++
	 */
	template<typename ... Params>
	AST(Params&& ... argsOfT)

		:value(std::forward<Params>(argsOfT)...)
	{}

	/*
	 +++++ COPY C'TOR  +++++
	 */
	AST(const AST& astObj) = delete;
	// 	:value(astObj.value)
	// {}

	/*
	 +++++ MOVE C'TOR  +++++
	 */
	AST(AST&& astObj)
		
		:value(std::move(astObj.value))
	{}



	/*
	 +++++ MOVE ASSIGN  +++++
	 */
	AST& operator=(AST&& astObj) {

		value = std::move(astObj.value);

		return *this;
	}


}; // AST






#endif


