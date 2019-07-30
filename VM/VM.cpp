
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

	:execQ(byteCodeQ), registers(new Register)
{};


/*
 ++++++ Executes the ByteCode in execQ +++++++++
*/

void VM::operator()() {


};




