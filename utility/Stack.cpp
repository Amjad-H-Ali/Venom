
/*
 +++++++ Main C'tor +++++++++++
 */

Stack::Stack()
	:head(nullptr)
{};

/*
 ++++++ Insert ptr to object into stack. +++++++
 */

void Stack::push(const SharedPtr<T> &objPtr) {

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

	if(!head) return; // Ensure there's a head to begin with lest we seg. fault.

	/* 
	 ++++++ Temporarly hold Node that will detach +++++++++
	*/

	Node<T> *temp = head;

	/*
	 ++++++ New head +++++++++++
	 */
	head = head->next;

	if(!head) return; // Ensure new head not equal to nullptr;

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

/*
 +++++++ Pop all objects above given Node in stack +++++++++++
 */
void Stack::popTop(Node<T> *stackPtr) {

	while(head != stackPtr)

    	pop();
};


/*
 +++++ Returns top of stack without popping it off. Return type is SharedPtr to object of type T +++++++
 */

SmartPtr<T> &getTop() const {

	if(!head) return nullptr; // Ensure there's a head to begin with lest we seg. fault.

	return head->value;
};