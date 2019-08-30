

/*
 ++++ Lots of Redundancies. Will Fix later ++++
 */

#ifndef BYTECODE_COMPILER_H

#define BYTECODE_COMPILER_H

#include <vector>
#include <string>
#include "Bytecode.h"
#include "astOverloads.h"
#include "../VM.h"
#include "../../ast/ast_t.h"
#include "../../ast/AST.h"



template<typename ... Params> struct Overloads : Params ... {using Params::operator() ...;};

template<typename ... Params> Overloads(Params ...) -> Overloads<Params...>;




class BytecodeCompiler {

public:


	/*
	 +++++ Main C'Tor +++++
	 */
	BytecodeCompiler(const std::vector<ast_t>& astVecToCompile);

	/*
	 ++++ Compiles AST vector +++++
	 */
	std::vector<Bytecode>& operator()();

private:


	/*
	 +++++ AST to compile +++++
	 */
	const std::vector<ast_t>& astVec;


	/*
	 +++++ ID name (std::string value) in AST<ID> node +++++
	 */
	const std::string *getIdNamePtr(const AST<ID>& astID);



	/*
	 +++++ Main Compiler +++++
	 */
	template<typename ... Params>
	void compile(std::vector<Bytecode>& bytecodeVec, Params&& ... ast_tObjs) {

		std::visit( Overloads {

			/*
			 +++++ Compile Assign Operator +++++
			 */
			[this, &bytecodeVec](const AST<Assign>& astAssign) {

				const Assign& assignObj = astAssign.getValue();

				/*
				 +++++   Compile left operand       +++++
				 *
				 +++++ ie. AST<ID> -> {DECL, "foo"} +++++
				 */
				compile(bytecodeVec, assignObj.getLeftOperand());

				/*
				 ++++ Get ID name ptr from last instruction in bytecodeVec ++++
				 */
				const std::string *idNamePtr = (--bytecodeVec.end())->param1;

			

				/*
				 +++++   Compile right operand      +++++
				 *
				 +++++ ie. AST<Func> -> {LOAD, 32}  +++++
				 */
				compile(bytecodeVec, assignObj.getRightOperand());

			


				/*
				 +++++ Instruction for Assign Operator ++++
				 */
				bytecodeVec.emplace_back(Bytecode::STORE, idNamePtr);

			},

			/*
			 +++++ Compile Function Definiton +++++
			 */
			[this, &bytecodeVec](const AST<Func>& astFunc) {

				/*
				 +++++ Function Definition will be separate bytecode vector +++++
				 */
				std::vector<Bytecode> *funcDefPtr = new std::vector<Bytecode>;

				/*
				 +++++ Find a place in memory vector to store funcDefPtr +++++
				 */

				/*
				 +++++ Check if there's unclaimed space in memory vector before creating new one +++++
				 */
				decltype(VM::freeSpace.size()) defIndx; // Index of free space in memory stored here.

				decltype(defIndx) freeSpaceLen = VM::freeSpace.size();

				if(freeSpaceLen > 0) {

					/*
					 ++++ Get index of unused space in memory vector from freeSpace vector +++++
					 */
					defIndx = VM::freeSpace[freeSpaceLen - 1];

					/*
					 +++++ Assign free space in definitons vector +++++
					 */ 
					VM::memory[defIndx] = funcDefPtr;

					VM::freeSpace.pop_back(); // Remove index as it's no longer free.
				}
				else {
					/*
					 +++++ If no free space is already available, create a new one +++++
					 */
					VM::memory.emplace_back(std::in_place_type< std::vector<Bytecode>* >,funcDefPtr);

					defIndx = VM::memory.size() - 1;

				}


				/*
				 +++++ Command to load ptr to function definiton on stack +++++
				 */
				bytecodeVec.emplace_back(Bytecode::LOAD, defIndx);


				/*
				 +++++ Vector of Locals to delete after function returns ++++
				 */
				std::vector<std::string*> *localsToDelPtr = new std::vector<std::string*>;

				/*
				 +++++ Compile function definition in its own vector +++++
				 */

				// TODO: REDUNDANT.
				for(const ast_t& astObj : astFunc.getValue().getParamList().getValue())  // Compiling function param list.

					compileFuncParamList(*funcDefPtr, *localsToDelPtr, astObj);


				for(const ast_t& astObj : astFunc.getValue().getBody().getValue())  // Compiling function body.

					compileFuncBody(*funcDefPtr, *localsToDelPtr, astObj);			    



			}, // Compile Function Definition

			// /*
			//  +++ When Operand is a Number +++
			//  */
			[this, &bytecodeVec](const AST<Num>& astNum) {

				/*
				 +++++ Store number in memory +++++
				 */
				VM::memory.emplace_back(std::in_place_type<size_t>, astNum.getValue().getValue() );


				/*
				 +++++ Insert Instruction and Parameter (the address of number) +++++
				 */
				bytecodeVec.emplace_back(Bytecode::LOAD, VM::memory.size() - 1);


			},


			[this, &bytecodeVec](const AST<Call>& astCall) {

				const Call& callObj = astCall.getValue();

				/*
				 +++++ Iterate Argument List of ast_t objects and compile +++++
				 */
				for(const ast_t& astObj : callObj.getArgList())

					compileCallOperands(bytecodeVec, astObj);

				compileCallLeftOperand(bytecodeVec, callObj.getLeftOperand());

				/*
				 +++++ Add Number of Arguments to instruction +++++
				 */	
				(--bytecodeVec.end())->param2 = (callObj.getArgList().size()) - 1;
			},

			/*
			 +++++ Compile Printing +++++
			 */
			[this, &bytecodeVec](const AST<Write>& astWrite) {

				const Write& writeObj = astWrite.getValue();


				compile(bytecodeVec, writeObj.getValue());

				bytecodeVec.emplace_back(Bytecode::PRINT);

			},

			/*
			 +++++ Compile ID declaration +++++
			 */
			[this, &bytecodeVec](const AST<ID>& astID) {

				/*
				 ++++++ ID -> (ie.) {DECL, "num1"}  ++++++
				 */
				const std::string *idNamePtr = getIdNamePtr(astID);

				/*
				 ++++++ Insert ByteCode instruction in vector +++++
				 */
				bytecodeVec.emplace_back(Bytecode::DECL, idNamePtr);
			},


			[this, &bytecodeVec](const auto&) {/* TODO */}


		}, std::forward<Params>(ast_tObjs)...);

	} // compile

	/*
	 +++++ Compile Function Parameter List +++++
	 */
	template<typename ... Params>
	void compileFuncParamList(std::vector<Bytecode>& bytecodeVec, std::vector<std::string*>& localsToDel, Params&& ... ast_tObjs) {

		std::visit( Overloads {

			/*
			 +++++ Compile parameter variable of Function +++++
			 */
			[this, &bytecodeVec, &localsToDel](const AST<ID>& astID) {
				
				/*
				 ++++++ ID -> (ie.) {PRAM, "num1"}  ++++++
				 */

				/*
				 ++++++ Insert ByteCode instruction in vector +++++
				 */
				const std::string *idNamePtr = getIdNamePtr(astID);

				bytecodeVec.emplace_back(Bytecode::PRAM, idNamePtr);

				/*
				 +++++ Insert Local variable in Delete stack to delete when function returns +++++
				 */
				// localsToDel.emplace_back(idNamePtr);
			},

			[this, &bytecodeVec](const auto&) {/* TODO */}

		}, std::forward<Params>(ast_tObjs)...);
	}

	/*
	 +++++ Compile Function Block +++++
	 */
	template<typename ... Params>
	void compileFuncBody(std::vector<Bytecode>& bytecodeVec, std::vector<std::string*>& localsToDel, Params&& ... ast_tObjs) {

		std::visit( Overloads {

			/*
			 +++++ Compile Assign Operator +++++
			 */
			[this, &bytecodeVec](const AST<Assign>& astAssign) {

				const Assign& assignObj = astAssign.getValue();

				/*
				 +++++   Compile left operand       +++++
				 *
				 +++++ ie. AST<ID> -> {DECL, "foo"} +++++
				 */
				compile(bytecodeVec, assignObj.getLeftOperand());

				/*
				 ++++ Get ID name ptr from last instruction in bytecodeVec ++++
				 */
				const std::string *idNamePtr = (--bytecodeVec.end())->param1;

				/*
				 +++++   Compile right operand      +++++
				 *
				 +++++ ie. AST<Func> -> {LOAD, 32}  +++++
				 */
				compile(bytecodeVec, assignObj.getRightOperand());

				/*
				 +++++ Instruction for Assign Operator ++++
				 */
				bytecodeVec.emplace_back(Bytecode::STORE, idNamePtr);

			},

			/*
			 +++++ Compile Function Definiton +++++
			 */
			[this, &bytecodeVec](const AST<Func>& astFunc) {

				/*
				 +++++ Function Definition will be separate bytecode vector +++++
				 */
				std::vector<Bytecode> *funcDefPtr = new std::vector<Bytecode>;

				/*
				 +++++ Find a place in memory vector to store funcDefPtr +++++
				 */

				/*
				 +++++ Check if there's unclaimed space in memory vector before creating new one +++++
				 */
				decltype(VM::freeSpace.size()) defIndx; // Index of free space in memory stored here.

				decltype(defIndx) freeSpaceLen = VM::freeSpace.size();

				if(freeSpaceLen > 0) {

					/*
					 ++++ Get index of unused space in memory vector from freeSpace vector +++++
					 */
					defIndx = VM::freeSpace[freeSpaceLen - 1];

					/*
					 +++++ Assign free space in definitons vector +++++
					 */ 
					VM::memory[defIndx] = funcDefPtr;

					VM::freeSpace.pop_back(); // Remove index as it's no longer free.
				}
				else {
					/*
					 +++++ If no free space is already available, create a new one +++++
					 */
					VM::memory.emplace_back(std::in_place_type< std::vector<Bytecode>* >,funcDefPtr);

					defIndx = VM::memory.size() - 1;

				}


				/*
				 +++++ Command to load ptr to function definiton on stack +++++
				 */
				bytecodeVec.emplace_back(Bytecode::LOAD, defIndx);


				/*
				 +++++ Vector of Locals to delete after function returns ++++
				 */
				std::vector<std::string*> *localsToDelPtr = new std::vector<std::string*>;

				/*
				 +++++ Compile function definition in its own vector +++++
				 */

				// TODO: REDUNDANT.
				for(const ast_t& astObj : astFunc.getValue().getParamList().getValue())  // Compiling function param list.

					compileFuncParamList(*funcDefPtr, *localsToDelPtr, astObj);


				for(const ast_t& astObj : astFunc.getValue().getBody().getValue())  // Compiling function body.

					compileFuncBody(*funcDefPtr, *localsToDelPtr, astObj);

			}, // Compile Function Definition


			[this, &bytecodeVec](const AST<Call>& astCall) {

				const Call& callObj = astCall.getValue();

				/*
				 +++++ Iterate Argument List of ast_t objects and compile +++++
				 */
				for(const ast_t& astObj : callObj.getArgList())

					compileCallOperands(bytecodeVec, astObj);

				compileCallLeftOperand(bytecodeVec, callObj.getLeftOperand());

				/*
				 +++++ Add Number of Arguments to instruction +++++
				 */	
				(--bytecodeVec.end())->param2 = (callObj.getArgList().size()) - 1;
			},

			/*
			 +++++ Compile Add Operator in Function +++++
			 */
			[this, &bytecodeVec, &localsToDel](const AST<Add>& astAdd) {

				const Add& addObj = astAdd.getValue();

				compileAddOperands(bytecodeVec, addObj.getLeftOperand(), addObj.getRightOperand());

				/*
				 +++++ For now, we assume operands are IDs +++++
				 */

				/*
				 +++++ Current State of function's bytecodeVec +++++
				 *
				 +++++ {PRAM, "num1", PRAM, "num2", EVAL, "num1", EVAL, "num2"} +++++
				 */


				// const std::string *leftIdName  = (--bytecodeVec.end())->param1,
				// 				  *rightIdName = (bytecodeVec.end()-2)->param1;


				bytecodeVec.emplace_back(Bytecode::ADD);

				// localsToDel.emplace_back(leftIdName);
				// localsToDel.emplace_back(rightIdName);

			},

			/*
			 +++++ Compile return statement +++++
			 */
			[this, &bytecodeVec, &localsToDel](const AST<Output>& astOutput) {

				const Output& outputObj = astOutput.getValue();


				/*
				 ++++ For now, assume return statement is Add operator +++++
				 */
				compileFuncBody(bytecodeVec, localsToDel, outputObj.getValue());

				bytecodeVec.emplace_back(Bytecode::RET);

			},


			/*
			 +++++ Compile local variable of Function +++++
			 */
			[this, &bytecodeVec, &localsToDel](const AST<ID>& astID) {
				
				/*
				 ++++++ ID -> (ie.) {DECL, "num1"}  ++++++
				 */
				const std::string *idNamePtr = getIdNamePtr(astID);

				/*
				 ++++++ Insert ByteCode instruction in vector +++++
				 */
				bytecodeVec.emplace_back(Bytecode::DECL, idNamePtr);

				/*
				 +++++ Insert Local variable in Delete stack to delete when function returns +++++
				 */
				// localsToDel.emplace_back(idNamePtr);
			},


			[this, &bytecodeVec](const auto&) {/* TODO */}


		}, std::forward<Params>(ast_tObjs)...);
	}

	/*
	 +++++ Compile Add operands +++++
	 */
	template<typename ... Params>
	void compileAddOperands(std::vector<Bytecode>& bytecodeVec, Params&& ... ast_tObjs) {

		std::visit( Overloads {

			/*
			 +++++ Both Operands are ID ++++
			 */
			[this, &bytecodeVec](const AST<ID>& leftAstID, const AST<ID>& rightAstID) {

				/*
				 +++++ Create Bytecode Instruction and add to vector +++++
				 */
				bytecodeVec.emplace_back(Bytecode::EVAL, getIdNamePtr(leftAstID));

				bytecodeVec.emplace_back(Bytecode::EVAL, getIdNamePtr(rightAstID));

			},

			[this, &bytecodeVec](const AST<Num>& leftAstNum, const AST<Num>& rightAstNum) {

				/*
				 +++++ Store number in memory +++++
				 */
				VM::memory.emplace_back(std::in_place_type<size_t>, leftAstNum.getValue().getValue() );

				VM::memory.emplace_back(std::in_place_type<size_t>, rightAstNum.getValue().getValue() );

				/*
				 +++++ Insert Instruction and Parameter (the address of number) +++++
				 */
				bytecodeVec.emplace_back(Bytecode::LOAD, VM::memory.size() - 2);

				bytecodeVec.emplace_back(Bytecode::LOAD, VM::memory.size() - 1);

				

			},

			/*
			 +++ When Left Operand is an Add Operator +++
			 */
			[this, &bytecodeVec](const AST<Add>& rightAstAdd, const AST<ID>& leftAstID) {

				// TODO: REDUNDANT ... I'm in a hurry

		
				const Add& addObj = rightAstAdd.getValue();

				compileAddOperands(bytecodeVec, addObj.getLeftOperand(), addObj.getRightOperand());

				bytecodeVec.emplace_back(Bytecode::ADD);

				bytecodeVec.emplace_back(Bytecode::EVAL, getIdNamePtr(leftAstID));
				

			},	

			[](const auto&) {/*TODO*/},

			[](const auto&, const auto&) {/*TODO*/}

		}, std::forward<Params>(ast_tObjs)...);
	}

	template<typename ... Params>
	void compileCallLeftOperand(std::vector<Bytecode>& bytecodeVec, Params&& ... ast_tObjs) {

		std::visit( Overloads {

			/*
			 +++ When Operand is an Identifier +++
			 */
			[this, &bytecodeVec](const AST<ID>& astID) {

				bytecodeVec.emplace_back(Bytecode::CALL, getIdNamePtr(astID));
			},

			[](const auto&) {/*TODO*/},

			[](const auto&, const auto&) {/*TODO*/}


		}, std::forward<Params>(ast_tObjs)...);
	}	

		


	/*
	 +++++ Compile Argument List of Call operator +++++
	 */
	template<typename ... Params>
	void compileCallOperands(std::vector<Bytecode>& bytecodeVec, Params&& ... ast_tObjs) {

		std::visit( Overloads {
			/*
			 +++ When Operand is a Number +++
			 */
			[this, &bytecodeVec](const AST<Num>& astNum) {

				/*
				 +++++ Store number in memory +++++
				 */
				VM::memory.emplace_back(std::in_place_type<size_t>, astNum.getValue().getValue() );

				/*
				 +++++ Insert Instruction and Parameter (the address of number) +++++
				 */
				bytecodeVec.emplace_back(Bytecode::LOAD, VM::memory.size() - 1);
			},

			/*
			 +++ When Operand is an Add Operator +++
			 */
			[this, &bytecodeVec](const AST<Add>& astAdd) {

				const Add& addObj = astAdd.getValue();
				/*
				 ++++  Produce Bytecode that will push result of "add" expression on stack. ++++ 
				 */
				compileAddOperands(bytecodeVec, addObj.getLeftOperand(), addObj.getRightOperand());

				bytecodeVec.emplace_back(Bytecode::ADD);

			},

			/*
			 +++ When Operand is an Identifier +++
			 */
			[this, &bytecodeVec](const AST<ID>& astID) {

				bytecodeVec.emplace_back(Bytecode::EVAL, getIdNamePtr(astID));
			},

			[](const auto&) {/*TODO*/},

			[](const auto&, const auto&) {/*TODO*/}

		}, std::forward<Params>(ast_tObjs)...);
	}




	
}; // BytecodeCompiler


#endif



