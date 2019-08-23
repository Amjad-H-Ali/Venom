

#ifndef BYTECODE_H
#define BYTECODE_H

#include <string>
#include <vector>


#define BYTECODE(I)			\
	I(DECL)					\
	I(LOAD)					\
	I(STORE)				\
	I(PRAM)					\
	I(EVAL)					\
	I(ADD)					\
	I(RET)				    \
	I(ARG)				   	\
	I(CALL)					\
	I(PRINT)					    	




/*
 +++++ Holds Bytecode Instruction and its Parameter +++++
 */
struct Bytecode {

   /*
	+++++ All Bytecode instructions +++++
	*/
#define I(instruction) instruction,

	enum Instruct {BYTECODE(I) NUM_OF_INSTRUCTS};

#undef I

	static const char *typeName[NUM_OF_INSTRUCTS];

	const char *getTypeName() const;


	Instruct instruction;

	/*
	 +++++ Bytecode will have either one of the following +++++
	 *
	 +++++ two parameters Depending on the Instruction    +++++
	 */

	/*
	 +++++ ID name parameter for some Instructions, otherwise nullptr +++++
	 */
	const std::string *param1;

	/*
	 +++++ Address in memory vector +++++
	 */
	std::vector<size_t>::size_type param2;



	/*
	 +++++ Main C'Tors +++++
	 *
	 +++++ Param1 C'Tor +++++
	 */
	Bytecode(Instruct command, const std::string *idNamePtr);

	/*
	 +++++ Param2 C'Tor +++++
	 */
	Bytecode(Instruct command, std::vector<size_t>::size_type address);

	/*
	 +++++ Instruction only C'Tor +++++
	 */
	Bytecode(Instruct command);

}; // Bytecode

#endif