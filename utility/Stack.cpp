

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

/*
 +++++++ Pop object off stack +++++++++++
 */

void Stack::pop() {

	/* 
	 ++++++ Temporarly hold Node that will detach +++++++++
	*/

	Node<T> *temp = head;

	/*
	 ++++++ New head +++++++++++
	 */
	head = head->next;

	head->prev = nullptr;

	/*
	 ++++++ At this point, no way of referring to original head without temp ++++++++++
	 */

	temp->next = nullptr;

	/*
	 +++++++ SharedPtr in this Node deletes if it's the only ptr sharing resource +++++++++++
	 */
	
	delete temp;
};