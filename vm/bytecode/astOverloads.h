
// #ifndef AST_OVERLOADS_H
// #define AST_OVERLOADS_H

// #include <vector>
// #include <string>
// #include "Bytecode.h"
// #include "../VM.h"
// #include "../../ast/ast_t.h"
// #include "../../ast/AST.h"

// template<typename ... Params> struct Overloads : Params ... {using Params::operator() ...;};

// template<typename ... Params> Overloads(Params ...) -> Overloads<Params...>;


// /*
//  +++++     Inherits from Lambdas in its parameter list.     +++++
//  *
//  +++++ Used in std::visit in compile methods of this class. +++++
//  */
// Overloads astOverloads {


// 	/*
// 	 +++++ Compile Assign Operator +++++
// 	 */
// 	[this, &bytecodeVec](const AST<Assign>& astAssign) {

// 		const Assign& assignObj = astAssign.getValue();

// 		/*
// 		 +++++   Compile left operand       +++++
// 		 *
// 		 +++++ ie. AST<ID> -> {DECL, "foo"} +++++
// 		 */
// 		compile(bytecodeVec, assignObj.getLeftOperand());

// 		/*
// 		 ++++ Get ID name ptr from last instruction in bytecodeVec ++++
// 		 */
// 		const std::string *idNamePtr = (--bytecodeVec.end())->param1;

// 		/*
// 		 +++++   Compile right operand      +++++
// 		 *
// 		 +++++ ie. AST<Func> -> {LOAD, 32}  +++++
// 		 */
// 		compile(bytecodeVec, assignObj.getRightOperand());

// 		/*
// 		 +++++ Instruction for Assign Operator ++++
// 		 */
// 		bytecodeVec.emplace_back(Bytecode::STORE, idNamePtr);

// 	},

// 	/*
// 	 +++++ Compile Function Definiton +++++
// 	 */
// 	[this, &bytecodeVec](const AST<Func>& astFunc) {

// 		/*
// 		 +++++ Function Definition will be separate bytecode vector +++++
// 		 */
// 		std::vector<Bytecode> *funcDefPtr = new std::vector<Bytecode>;

// 		/*
// 		 +++++ Find a place in memory vector to store funcDefPtr +++++
// 		 */

// 		/*
// 		 +++++ Check if there's unclaimed space in memory vector before creating new one +++++
// 		 */
// 		decltype(VM::freeSpace.size()) defIndx; // Index of free space in memory stored here.

// 		if((decltype(defIndx) freeSpaceLen = VM::freeSpace.size()) > 0) {

// 			/*
// 			 ++++ Get index of unused space in memory vector from freeSpace vector +++++
// 			 */
// 			defIndx = VM::freeSpace[freeSpaceLen - 1];

// 			/*
// 			 +++++ Assign free space in definitons vector +++++
// 			 */ 
// 			VM::memory[defIndx] = funcDefPtr;

// 			VM::freeSpace.pop_back(); // Remove index as it's no longer free.
// 		}
// 		else {
// 			/*
// 			 +++++ If no free space is already available, create a new one +++++
// 			 */
// 			VM::memory.emplace_back(std::in_place_type< std::vector<Bytecode>* >,funcDefPtr);

// 			defIndx = VM::memory.size() - 1;

// 		}


// 		/*
// 		 +++++ Command to load ptr to function definiton on stack +++++
// 		 */
// 		bytecodeVec.emplace_back(Bytecode::LOAD, defIndx);


// 		/*
// 		 +++++ Vector of Locals to delete after function returns ++++
// 		 */
// 		std::vector<std::string*> *localsToDelPtr = new std::vector<std::string*>;

// 		/*
// 		 +++++ Compile function definition in its own vector +++++
// 		 */

// 		// TODO: REDUNDANT.
// 		for(const ast_t& astObj : astFunc.getValue().getParamList().getValue())  // Compiling function param list.

// 			compileFuncParamList(*funcDefPtr, *localsToDelPtr, astObj);


// 		for(const ast_t& astObj : astFunc.getValue().getBody().getValue())  // Compiling function body.

// 			compileFuncBody(*funcDefPtr, *localsToDelPtr, astObj);

// 	}, // Compile Function Definition


// 	[this, &bytecodeVec](const AST<Call>& astCall) {

// 		const Call& callObj = astCall.getValue();

// 		/*
// 		 +++++ Iterate Argument List of ast_t objects and compile +++++
// 		 */
// 		for(const ast_t& astObj : callObj.getArgList())

// 			compileCallOperands(bytecodeVec, astObj);

// 		compileCallOperands(callObj.getLeftOperand());

// 		/*
// 		 +++++ Add Number of Arguments to instruction +++++
// 		 */	
// 		(--bytecodeVec.end())->param2 = (callObj.getArgList().size()) - 1;
// 	}

// }; // astOverloads

// #endif