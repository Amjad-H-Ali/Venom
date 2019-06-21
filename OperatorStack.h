/*
	This class will behave as a stack of operators that are waiting to
	be processed. With this, we don't have to iterate through the AST 
	again. Once parser is finished doing its job, we can process the 
	operators in this stack.
*/

#ifndef OPERATOR_STACK_H

#define OPERATOR_STACK_H

#include "AST.h"



struct Node {

	AST *AST_Operator;


	Node *next;


};


class OperatorStack {

private:

	Node *stackOfOps;

public:

	OperatorStack()
		:stackOfOps(nullptr)
	{};

	void push(AST *operatorNode) {

		Node *newNode = new Node;

		newNode->AST_Operator = operatorNode;

		newNode->next = stackOfOps;

	}


}

extern OperatorStack *opStack;

#endif