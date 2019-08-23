
#include "BytecodeCompiler.h"


/* NOTES:

{DECL, "foo", LOAD, 32, STORE, "foo"}

{DECL, "num1", DECL, "num2", DECL, "num1", DECL, "num2"}

*/


/*
 +++++ Main C'Tor +++++
 */
BytecodeCompiler::BytecodeCompiler(const std::vector<ast_t>& astVecToCompile) 

	:astVec(astVecToCompile)
{}

/*
 ++++ Compiles AST vector +++++
 */
std::vector<Bytecode>& BytecodeCompiler::operator()() {

	/*
	 ++++ Compiled AST objects stored here +++++
	 */
	std::vector<Bytecode> *bytecodeVecPtr = new std::vector<Bytecode>;

	/*
	 ++++ Fill bytecodeVec with compiled ast_t objects ++++
	 */
	for(const ast_t& ast_tObj : astVec)

		compile(*bytecodeVecPtr, ast_tObj);

	return *bytecodeVecPtr;
}




/*
 +++++ ID name (std::string value) in AST<ID> node +++++
 */
inline const std::string *BytecodeCompiler::getIdNamePtr(const AST<ID>& astID) {

	/*					
	 +++++ ID Name. AST<ID> -> ID -> std::string value +++++
	 */				   
	return &(astID.getValue().getName());
}







