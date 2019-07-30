#ifndef VM_H

#define VM_H

class VM {

private:

	/*
	 +++++++ Activation Records (Stack Frames) of called funtions are stored here +++++++++++
	 */

	Stack<> callStack;

	/*
	 ++++++ ByteCode to execute. ++++++++
	 */

	Queue<> execQ;

	/*
	 ++++++++ Used to map variable names to their values in O(1) time complexity ++++++++++++
	 */

	Trie<> declTree;


	/*
	 +++++ Registers to store information such as Function's return address, current stack frame, etc... +++++++++
	 */

	struct Register;

	Register *registers;


public:

	/* 
	 ++++++ Main C'tor ++++++++
	 */

	VM();

	/*
	 ++++++ Executes the ByteCode in execQ +++++++++
	*/

	void operator()();

}; // VM


#endif