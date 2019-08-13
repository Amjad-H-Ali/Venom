#include "Func.h"


Func::Func(Func&& funcObj)

	:params(std::move(funcObj.params)), body(std::move(funcObj.body)) 
{}