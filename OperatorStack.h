/*
	This class will behave as a stack of operators that are waiting to
	be processed. With this, we don't have to iterate through the AST 
	again. Once parser is finished doing its job, we can process the 
	operators in this stack.
*/

#ifndef OPERATOR_STACK_H

#define OPERATOR_STACK_H

#include "AST.h"

// TODO: consider putting this in its own header file for reuse.
template<typename ... Ts> struct Overloads : Ts ... {using Ts::operator()...;};
template<typename ... Ts> Overloads(Ts ...) -> Overloads<Ts ...>;

struct Node {

	AST *op;


	Node *next;


};


class OperatorStack {

private:

	Node *stackOfOps;


	void process(AST *parent, astPtr_t astPtr) {

		std::visit(Overloads {

			[](auto op) { /* Do Nothing...*/ },

			[parent](AST_BinOp *op) {

				AST *lParent = parent->next,

					*rParent = parent->prev;

				op->setValue(lParent->node, rParent->node);


				parent->next = lParent->next;

				parent->prev = rParent->prev;

				parent->next->prev = parent;

				parent->prev->next = parent;

				delete lParent;
				delete rParent;

			}

		}, astPtr);
	}

	void processEach(Node *opNode) {

		if(!opNode) return;

		processEach(opNode->next);

		AST *node = opNode->op;
		process(node, node->node);
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



	void processEach() {

		processEach(stackOfOps);
		
	}


};

extern OperatorStack *opStack;

#endif