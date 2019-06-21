/*
	This class will behave as a stack of operators that are waiting to
	be processed. With this, we don't have to iterate through the AST 
	again. Once parser is finished doing its job, we can process the 
	operators in this stack.
*/

#ifndef OPERATOR_STACK_H

#define OPERATOR_STACK_H

#include "AST_BinOp.h"



struct Node {

	AST_BinOp *op;


	Node *next;


};


class OperatorStack {

private:

	Node *stackOfOps;



	void process(Node *opNode) {

		if(!opNode) return;

		process(opNode->next);

		opNode->op->process();
	}

public:

	OperatorStack()
		:stackOfOps(nullptr)
	{};

	void push(AST *oper) {

		Node *newNode = new Node;

		newNode->op = oper;

		newNode->next = stackOfOps;

		stackOfOps = newNode;

	}

	void process() {

		process(stackOfOps);
		
	}


};

extern OperatorStack *opStack;

#endif