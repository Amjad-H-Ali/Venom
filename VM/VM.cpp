
// /*
//  +++++ Registers to store information such as Function's return address, current stack frame, etc... +++++++++
//  */

// struct VM::Register {

// 	/*
//      ++++++ Stack Pointer ++++++++
// 	 */

// 	Node<> *esp;

// 	/*
//      ++++++ Base Pointer +++++++++
// 	 */

// 	Node<> *ebp;

// 	/*
//      ++++ Instruction Pointer ++++
// 	 */

// 	Node<> *eip;

// 	/*
// 	 ++++ Accumulator Register ++++
// 	 */

// 	Node<> *eax;

// 	/*
// 	 +++++ Data Register +++++
// 	 */

// 	Node<> *edx;



// 	/*
// 	 +++++ Main C'tor +++++++
// 	 */

// 	Register()

// 		:esp(nullptr), ebp(nullptr), eip(nullptr), eax(nullptr), edx(nullptr)
// 	{};

// }; // Register


// /* 
//  ++++++ Main C'tor ++++++++
//  */

// VM::VM(Queue<> *byteCodeQ)

// 	:execQ(byteCodeQ)
// {};


// /*
//  ++++++ Executes the ByteCode in execQ +++++++++
// */

// void VM::operator()() {

// 	Register rgstr;

// 	/*
// 	 +++++ Set eip register to first instruction in execQ. Loop till no more instructions. ++++++++
// 	 */

// 	for(rgstr.eip = execQ->begin(); rgstr.eip; ) {

// 		/*
// 		 +++++ Declare variable (push to declTree) +++++++
// 		 */

// 		if(*rgstr.eip == DECL) {

// 			rgstr.eip = (rgstr.eip)->next;       			// Increment eip to next instruction. 

// 			declTree.push(*rgstr.eip);     					// Declare name of variable.

// 			rgstr.eip = (rgstr.eip)->next;	   				// Increment eip to next instruction.
// 		}											

// 		/*
// 	     +++++ Push value onto stack ++++++
// 		 */

// 		else if(*rgstr.eip == LOAD) {

// 			rgstr.eip = (rgstr.eip)->next;       			// Increment eip to next instruction.

// 			callStack.push(*rgstr.eip);						// Push value onto stack.

// 			rgstr.esp = callStack.getTop();					// Set stack ptr to top.

// 			rgstr.eip = (rgstr.eip)->next;       			// Increment eip to next instruction.

// 		}	

// 		/*
// 		 +++++ Store value on top of stack into variable. ++++++
// 		 */			
// 			// TODO: setValue() method for Trie.
// 		 else if(*rgstr.eip == STORE) {

// 			rgstr.eip = (rgstr.eip)->next;       			// Increment eip to next instruction. 

// 			declTree.setValue(*rgstr.eip, *rgstr.esp);		// Map variable name and store value from top of stack.

// 			rgstr.esp = (rgstr.esp)->next;					// Decrement stack pointer.

// 			callStack.pop();								// Pop value off top of stack.

// 			rgstr.eip = (rgstr.eip)->next;       			// Increment eip to next instruction. 


// 		 }		

// 		 /*
// 		  +++++ Evaluate a variable +++++
// 		  */		

// 		  else if(*rgstr.eip == EVAL) {

// 			rgstr.eip = (rgstr.eip)->next;       			// Increment eip to next instruction. 

// 		  	rgstr.edx = declTree.map(*rgstr.eip)			// Map to value in string. Temporarly store value.

// 		  	callStack.push(*rgstr.edx);						// Push value onto stack.

// 			rgstr.esp = callStack.getTop();					// Set stack ptr to top.

// 			rgstr.eip = (rgstr.eip)->next;       			// Increment eip to next instruction. 

// 		  }			

		  
// 		   +++++ Add to values +++++
		   

// 		  else if(*rgstr.eip == ADD) {

// 		  	rgstr.eax = *rgstr.esp;							// Temporarly store value from stack into eax.

// 			rgstr.esp = (rgstr.esp)->next;					// Decrement stack pointer.

// 			callStack.pop();								// Pop value off top of stack.

// 			rgstr.eax += (*rgstr.esp);						// Add value from stack to value in eax.

// 			rgstr.esp = (rgstr.esp)->next;					// Decrement stack pointer.

// 			callStack.pop();								// Pop value off top of stack.

// 			callStack.push(*rgstr.eax);						// Push summed value in eax onto stack.

// 			rgstr.esp = callStack.getTop();					// Set stack ptr to top.

// 			rgstr.eip = (rgstr.eip)->next;       			// Increment eip to next instruction. 

// 		  }

// 		  /*
// 		   +++++ Function Call +++++
// 		   */

// 		  else if(*rgstr.eip == CALL) {

// 			rgstr.eip = (rgstr.eip)->next;       			// Increment eip to next instruction. 

// 			rgstr.edx = rgstr.eip;							// Temporarly store function name.

// 			rgstr.eip = (rgstr.eip)->next;       			// Increment eip to next instruction. 

// 			callStack.push(*rgstr.eip);						// Push number of arguments.

// 			rgstr.eip = (rgstr.eip)->next;       			// Increment eip to next instruction. 

// 			callStack.push(rgstr.ebp);						// Push old base pointer.

// 			callStack.push(rgstr.eip);						// Push return address.

// 			rgstr.esp = callStack.getTop();					// Set stack ptr to top.

// 			rgstr.ebp = rgstr.esp;							// Store return address in ebp.

// 			rgstr.eip = declTree.map(*rgstr.edx);			// Map to function instructions.

// 		  }

// 		  /*
// 		   +++++ Returning +++++
// 		   */

// 		  else if(*rgstr.eip == RET) {

// 		  	rgstr.edx = *rgstr.esp; 						// Temporarly Store return value in edx.

// 		  	rgstr.esp = rgstr.ebp;							// Set stack pointer to return address stored in stack.

// 		  	callStack.popTop(rgstr.esp); 					// Pop everything above stack pointer left on stack.

// 		  	rgstr.eip = *rgstr.esp; 						// After returning to old address, Set next instruction.

// 			rgstr.esp = (rgstr.esp)->next;					// Decrement stack pointer.

// 		  	callStack.pop(); 								// Pop off return address from stack.

// 		  	rgstr.ebp = rgstr.esp;							// Restore base pointer.

// 		  	rgstr.esp = (rgstr.esp)->next;					// Decrement stack pointer.

// 		  	callStack.pop(); 								// Pop off base pointer from stack.

// 		  	rgstr.eax = *rgstr.esp;							// Store number of arguments.

// 		  	rgstr.esp = (rgstr.esp)->next;					// Decrement stack pointer.

// 		  	callStack.pop(); 								// Pop off number of arguments from stack.

// 		  	callStack.popLoop(*rgstr.eax);					// Pop arguments off stack.

// 			callStack.push(*rgstr.edx);						// Push return value onto stack.

// 			rgstr.esp = callStack.getTop();					// Set stack ptr to top.

// 		  }

// 	}



// };




