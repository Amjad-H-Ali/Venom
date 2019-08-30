#include "VM.h"


/*
 +++++ {DECL, "foo", LOAD, 24, STORE, "foo", LOAD, 14, LOAD, 15, CALL, "foo"} +++++
 *
 +++++ 24::{PRAM, "num1", PRAM, "num2", EVAL, "num1", EVAL, "num2", ADD, RET} +++++
 */

/*
 +++++ Vector containing indices of free space in definitions vector +++++
 */
std::vector< std::vector<size_t>::size_type > VM::freeSpace;

/*
 +++++ Global and Local variable definitions stored here +++++
 */
std::vector<VM::type_t> VM::memory;
 


/*
 +++++ Registers such as stack pointer, base pointer, instruction pointer, etc +++++
 */
struct VM::Register {

	/*
	 ++++++ Stack Pointer ++++++++
	 */
	std::vector<size_t>::size_type esp;

	/*
     ++++++ Base Pointer +++++++++
	 */
	std::vector<size_t>::size_type ebp;

	/*
     ++++ Instruction Pointer ++++
	 */
	std::vector<size_t>::size_type eip;

	/*
	 ++++ Accumulator Register ++++
	 */
	std::vector<size_t>::size_type eax;

	/*
	 +++++ Data Register +++++
	 */
	std::vector<size_t>::size_type edx;

	/*
	 +++++ Main C'tor +++++++
	 */
	Register()

		:esp(0), ebp(0), eip(0), eax(0), edx(0)
	{}

}; // Register


/* 
 ++++++ Main C'tor ++++++++
 */

VM::VM(std::vector<Bytecode>* bytecodeToExec)

	:execVecPtr(bytecodeToExec)
{};


/*
 ++++++ Executes the ByteCode in execVecPtr +++++++++
 */

void VM::operator()() {

	Register rgstr;


	/*
	 +++++ Iterate vector of Bytecode ++++++++
	 */
	while(rgstr.eip < execVecPtr->size()) {

		std::vector<Bytecode>& execVec = *execVecPtr;

		/*
		 +++++ Declare variable (push to declTree) +++++++
		 */
		if(execVec[rgstr.eip].instruction == Bytecode::DECL) {			

			declTree.push(*(execVec[rgstr.eip++].param1));     													// Declare name of variable.

		}											

		/*
	     +++++ Push value onto stack ++++++
		 */
		else if(execVec[rgstr.eip].instruction == Bytecode::LOAD) {

			stack[rgstr.esp++] = execVec[rgstr.eip++].param2;													// Push address of value onto stack.

		

		}	

		/*
		 +++++ Store value on top of stack into variable. ++++++
		 */			
			// TODO: setValue() method for Trie.
		else if(execVec[rgstr.eip].instruction == Bytecode::STORE) {

			declTree.setValue(*(execVec[rgstr.eip++].param1), stack[--rgstr.esp]);								// Map variable name and store value from top of stack.

		

		}		

		/*
		+++++ Evaluate a variable +++++
		*/		

		else if(execVec[rgstr.eip].instruction == Bytecode::EVAL) {
		
			std::cout << "ID NAME:: " << *(execVec[rgstr.eip].param1) << std::endl;
		  	rgstr.edx = *declTree.map(*(execVec[rgstr.eip++].param1));											// Map to value in string. Temporarly store value.
		  	std::cout << "EVAL:: " << rgstr.edx << std::endl;
		  	stack[rgstr.esp++] = rgstr.edx;																		// Push address of value onto stack.
		}			

		/*
		 +++++ Add +++++
		 */ 
		else if(execVec[rgstr.eip].instruction == Bytecode::ADD) {
		  	std::cout << "GET in ADD ..." << std::endl;

		  	rgstr.eax = std::get<size_t>(VM::memory[stack[--rgstr.esp]]);										// Temporarly store value from stack into eax and pop.
		  	
			rgstr.eax += std::get<size_t>(VM::memory[stack[--rgstr.esp]]);										// Add value from stack to value in eax and pop.
		  	std::cout << "GET in ADD WORKED" << std::endl;

			VM::memory.emplace_back(std::in_place_type<size_t>, rgstr.eax);										// Store Summed value in VM::memory.

			stack[rgstr.esp++] = VM::memory.size() - 1;															// Push address of summed value on stack.

      		++rgstr.eip;																						// Increment eip to next instruction. 
		
		}

		/*
		 +++++ Function Call +++++
		 */
		else if(execVec[rgstr.eip].instruction == Bytecode::CALL) {

			rgstr.edx = *declTree.map(*(execVec[rgstr.eip].param1));											// Temporarly store function-to-call address.

			VM::memory.emplace_back(std::in_place_type< std::vector<Bytecode>* >, &execVec);					// Store current function in VM::memory.

			stack[rgstr.esp++] = execVec[rgstr.eip++].param2;													// Push number of arguments.

			rgstr.eax = stack[rgstr.esp-1];																		// Store number of arguments in eax for PRAM.

			stack[rgstr.esp++] = rgstr.ebp;																		// Push old base pointer.

			stack[rgstr.esp++] = VM::memory.size() - 1;															// Push address of current function on stack.	
								
			stack[rgstr.esp++] = rgstr.eip;																		// Push return address.

			rgstr.ebp = rgstr.esp;																				// Store return address in ebp.

			execVecPtr = std::get< std::vector<Bytecode>* >(VM::memory[rgstr.edx]);								// Branch To Function Definition.

			rgstr.eip = 0;																						// Set instruction pointer to beginning of function definition.

		

		}																								

		/*
		 +++++ Returning +++++
		 */

		else if(execVec[rgstr.eip].instruction == Bytecode::RET) {

		  	rgstr.edx = std::get<size_t>(VM::memory[stack[--rgstr.esp]]); 																	// Temporarly Store return value in edx.

		  	rgstr.esp = rgstr.ebp;																				// Set stack pointer to return address stored in stack.

		  	rgstr.eip = stack[--rgstr.esp]; 																	// Restore instruction pointer.
		  	std::cout << "GET in RET ..." << std::endl;
		  	execVecPtr = std::get< std::vector<Bytecode>* >(VM::memory[stack[--rgstr.esp]]);					// Restore to Caller function definition.
		  	std::cout << "GET in RET WORKED" << std::endl;
		  	rgstr.ebp = stack[--rgstr.esp];																		// Restore base pointer.

		  	rgstr.eax = stack[--rgstr.esp];																		// Store number of arguments.

		  	rgstr.esp = rgstr.esp - rgstr.eax;																	// Pop arguments.

			stack[rgstr.esp++] = rgstr.edx;																		// Push return value onto stack.

		}

		/*
		 +++++ Function Parameters +++++
		 */
		else if(execVec[rgstr.eip].instruction == Bytecode::PRAM) {


			rgstr.edx = stack[(rgstr.ebp - 5) - (rgstr.eax--)];													// VM::Memory of Corresponding Argument .
			

			declTree.push(*(execVec[rgstr.eip++].param1), rgstr.edx);							            	// Map variable name and store argument in stack.

		}

		/*
		 +++++ Printing to Standard Output +++++
		 */
		else if(execVec[rgstr.eip].instruction == Bytecode::PRINT) {

			std::cout << stack[--rgstr.esp] << std::endl;														// Print value on stack and pop
		
			++rgstr.eip;																						// Next instruction
		}					

	}



};




