/*
	This class will behave as a stack of operators that are waiting to
	be processed. With this, we don't have to iterate through the AST 
	again. Once parser is finished doing its job, we can process the 
	operators in this stack.
*/

#ifndef OPERATOR_STACK_H

#define OPERATOR_STACK_H

#include "AST.h"
#include <iostream>

// TODO: consider putting this in its own header file for reuse.
template<typename ... Ts> struct Overloads : Ts ... {using Ts::operator()...;};
template<typename ... Ts> Overloads(Ts ...) -> Overloads<Ts ...>;

struct Node {

	AST *op;


	Node *next;

	Node()
		:op(nullptr)
	{};


};


class OperatorStack {

private:

	Node *stackOfOps;


	void process(AST *parent, astPtr_t astPtr) {

		std::visit(Overloads {

			[](auto op) { /* Do Nothing...*/},

			[parent](AST_BinOp *op) {

				std::cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << std::endl;

				std::cout << parent  << "  " << op << "  "<< std::endl;

				std::cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << std::endl;


				AST *lParent = parent->next,

					*rParent = parent->prev;

				std::cout << "lll " <<lParent  << "  " << rParent << "  "<< std::endl;

				op->setValue(lParent->node, rParent->node);

				// Detatch Node from AST link.
				parent->next = lParent->next;

				parent->prev = rParent->prev;

				std::cout << "THIS IS L AND R   " << parent->next<< "   " << parent->prev << std::endl;

				if (parent->next) parent->next->prev = parent;

				if (parent->prev) parent->prev->next = parent;

				std::cout <<"ENDDDDDDD"<< std::endl;

				delete lParent;
				delete rParent;


			}

		}, astPtr);
	}

	void processEach(Node *opNode) {

		if(!opNode) return;

		processEach(opNode->next);

		AST *node = opNode->op;
		std::cout << "IN FUNC, L and R:   " << node->next << "   " << node->prev << std::endl;
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