

Stack::Stack()
	:head(nullptr)
{};

/*
 ++++++ Insert ptr to object into stack. +++++++
 */

void Stack::push(const SharedPtr<Token> &objPtr) {

	Node<T> *newNode = new Node<T>(objPtr);


	newNode->next = head;

	/*
	 ++++++ If exists, point object already in stack's  prev ptr to newNode +++++++
	 */

	if(head) head->prev = newNode;

	head = newNode;
};


void Stack::pop() {

	

};