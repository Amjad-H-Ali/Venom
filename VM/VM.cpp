
/*
 +++++ Registers to store information such as Function's return address, current stack frame, etc... +++++++++
 */

struct VM::Register {

	/*
     ++++++ Stack Pointer ++++++++
	 */

	Node<> *esp;

	/*
     ++++++ Base Pointer +++++++++
	 */

	Node<> *ebp;

	/*
     ++++ Instruction Pointer ++++
	 */

	Node<> *eip;

	/*
	 ++++ Accumulator Register ++++
	 */

	Node<> *eax;

	/*
	 +++++ Data Register +++++
	 */

	Node<> *edx;



	/*
	 +++++ Main C'tor +++++++
	 */

	Register()

		:esp(nullptr), ebp(nullptr), eip(nullptr), eax(nullptr), edx(nullptr)
	{};

}; // Register


/* 
 ++++++ Main C'tor ++++++++
 */

VM::VM(Queue<> *byteCodeQ)

	:execQ(byteCodeQ)
{};


/*
 ++++++ Executes the ByteCode in execQ +++++++++
*/

void VM::operator()() {

	Register rgstr;

	/*
	 +++++ Set eip register to first instruction in execQ. Loop till no more instructions. ++++++++
	 */

	for(rgstr.eip = execQ->begin(); rgstr.eip; ) {

		/*
		 +++++ Declare variable (push to declTree) +++++++
		 */

		if(*rgstr.eip == DECL) {

			rgstr.eip = (rgstr.eip)->next;       			// Increment eip to next instruction. 

			declTree.push(*rgstr.eip);     					// Declare name of variable.

			rgstr.eip = (rgstr.eip)->next;	   				// Increment eip to next instruction.
		}											

		/*
	     +++++ Push value onto stack ++++++
		 */

		else if(*rgstr.eip == LOAD) {

			rgstr.eip = (rgstr.eip)->next;       			// Increment eip to next instruction.

			callStack.push(*eip);							// Push value onto stack.

			rgstr.esp = callStack.getTop();					// Set stack ptr to top.

			rgstr.eip = (rgstr.eip)->next;       			// Increment eip to next instruction.

		}	

		/*
		 +++++ Store value on top of stack into variable. ++++++
		 */			
			// TODO: setValue() method for Trie.
		 else if(*rgstr.eip == STORE) {

			rgstr.eip = (rgstr.eip)->next;       			// Increment eip to next instruction. 

			declTree.setValue(*rgstr.eip, *rgstr.esp);		// Map variable name and store value from top of stack.

			rgstr.esp = (rgstr.esp)->next;					// Decrement stack pointer.

			callStack.pop();								// Pop value off top of stack.

			rgstr.eip = (rgstr.eip)->next;       			// Increment eip to next instruction. 


		 }		

		 /*
		  +++++ Evaluate a variable +++++
		  */		

		  else if(*rgstr.eip == EVAL) {

			rgstr.eip = (rgstr.eip)->next;       			// Increment eip to next instruction. 

		  	rgstr.edx = declTree.map(*rgstr.eip)			// Map to value in string. Temporarly store value.

		  	callStack.push(*rgstr.edx);						// Push value onto stack.

			rgstr.esp = callStack.getTop();					// Set stack ptr to top.

			rgstr.eip = (rgstr.eip)->next;       			// Increment eip to next instruction. 

		  }			

	}



};




