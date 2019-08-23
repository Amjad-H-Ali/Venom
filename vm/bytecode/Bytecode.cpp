#include "Bytecode.h"



#define I(instruction) #instruction,

   const char *Bytecode::typeName[NUM_OF_INSTRUCTS] = {BYTECODE(I)};

#undef I


const char *Bytecode::getTypeName() const {

	return typeName[instruction];
};

/*
 +++++ Main C'Tors +++++
 *
 +++++ Param1 C'Tor +++++
 */
Bytecode::Bytecode(Instruct command, const std::string *idNamePtr)

	:instruction(command), param1(idNamePtr)
{}

/*
 +++++ Param2 C'Tor +++++
 */
Bytecode::Bytecode(Instruct command, std::vector<size_t>::size_type address)

	:instruction(command), param2(address), param1(nullptr)
{}

/*
 +++++ Instruction only C'Tor +++++
 */
Bytecode::Bytecode(Instruct command)

	:instruction(command), param1(nullptr)
{}	