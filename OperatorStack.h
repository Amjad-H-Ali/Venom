/*
	This class will behave as a stack of operators that are waiting to
	be processed. Once parser is finished doing its job, we can process
	the operators in this stack.

	Also note: this is a Singleton class. Only on instance is allowed of
	this type because I don't see why we would need more than one.

*/

#ifndef OPERATOR_STACK_H

#define OPERATOR_STACK_H

class OperatorStack {

public:


	static OperatorStack *getInstance() {

		static OperatorStack instance;

		return &instance;
	}

private:
	
	// Ensures One Instance.
	OperatorStack() {};

	// Copy or Assignment constructor not allowed in our Singleton.
	OperatorStack(const OperatorStack&)  = delete;
	void operator=(const OperatorStack&) = delete;



};

extern OperatorStack *stackOfOps;

#endif