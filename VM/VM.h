#ifndef VM_H

#define VM_H

#include <variant>
#include <vector>
#include "./bytecode/Bytecode.h"
#include "../utility/trie/Trie.h"






class VM {

private:

	static constexpr size_t _1MB = 1024*1024;

	static constexpr size_t STACK_SIZE = _1MB / sizeof(std::vector<size_t>::size_type);



	/*
	 +++++ Used to map variable names to their values in O(1) time complexity +++++
	 */
    Trie< std::vector<size_t>::size_type > declTree;

    /*
     +++++ Bytecode to Execute +++++
     */
   	std::vector<Bytecode>* execVecPtr;

    /*
     +++++ Activation Records (Stack Frames) of called funtions are stored here +++++
     */
    decltype(execVecPtr->size()) stack[STACK_SIZE];

    /*
     +++++ Registers such as stack pointer, base pointer, instruction pointer, etc +++++
     */
    struct Register;

public:
	/*
	 +++++ Types of objects stored in definitions vector +++++ 
	 */
	typedef std::variant< std::nullptr_t, size_t, std::vector<Bytecode>* > type_t;
	

	/* 
	 ++++++ Main C'tor ++++++++
	 */
	VM(std::vector<Bytecode>* bytecodeToExec);

	/*
	 ++++++ Executes the ByteCode in execQ +++++++++
	 */
	void operator()();


	/*
	 +++++ Vector containing indices of free space in definitions vector +++++
	 */
	static std::vector< std::vector<size_t>::size_type > freeSpace;

	/*
	 +++++ Global and Local variable definitions stored here +++++
	 */
	static std::vector<type_t> memory;



}; // VM




#endif