
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
	 +++++ Main C'tor +++++++
	 */

	Register()

		:esp(nullptr), ebp(nullptr), eip(nullptr), eax(nullptr)
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

	Register registers;

	/*
	 +++++ Set eip register to first instruction in execQ. Loop till no more instructions. ++++++++
	 */

	for(registers.eip = execQ->begin(); registers.eip; ) {

		/*
		 +++++ Declare variable (push to declTree) +++++++
		 */

		if(*eip == DECL) {

			eip = eip->next;       	// Increment eip to next instruction.

			declTree.push(eip)     	// Declare name of variable.

			eip = eip->next;	   	// Increment eip to next instruction.
		}

		/*
	     +++++ Push value onto stack ++++++
		 */

		else if(*eip == LOAD) {

			
		}

	}



};




