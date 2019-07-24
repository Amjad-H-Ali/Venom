

Stack::Stack()
	:head(nullptr)
{};

/*
 ++++++ Insert object into stack. +++++++
 */

void Stack::push(T *objPtr) {

	Node<T> *newNode = new Node<T>;

	newNode->value = objPtr;

	newNode->next = head;

	/*
		*
		* If there's an object in stack, point its
		* prev pointer to newNode.
		*
	*/
	if(head) head->prev = newNode;

	head = newNode;
};


void Stack::pop() {


};