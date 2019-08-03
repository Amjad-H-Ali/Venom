
/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * A Stack, implemented using a linked-list, that can  *
 * access elements in O(log n) time complexity.        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */


/*
 +++++++ Main C'tor +++++++++++
 */

SmartStack::SmartStack()
    :head(nullptr)
{};

/*
 +++++ Push T objects emplace. Takes in parameters that construct T object. +++++
 */

template<typename ... Params>

void SmartStack::push(Params&& ... params) { 

    /*
     +++++ Constructing a Pointer to a Node, which contains a pointer to Object of type T +++++
     */

    SharedPtr< Node<T> > newNode(new Node<T>(new T(std::forward<Params>(params)...)));


    newNode->next = head;

    head = newNode;

    /*
     +++++ Register the index of the newNode for later access in O(log n). +++++
     */
    indexMap.push(size++, newNode);
};

/*
 +++++++ Pop object off stack +++++++++++
 */

void SmartStack::pop() {

    if(!head) return; // Ensure there's a head to begin with lest we seg. fault.

    /* 
     ++++++ Temporarly hold Node that will detach +++++++++
     */

    SharedPtr< Node<T> > temp = head;

    /*
     ++++++ New head +++++++++++
     */
    head = head->next;

    /*
     ++++++ At this point, no way of referring to original head without temp ++++++++++
     */

    temp->next = nullptr;

    /*
     +++++ Set data to nullptr in Trie +++++
     */

     indexMap.eraseData(--size);

    /*
     +++++++ SharedPtr in this Node deletes if it's the only ptr sharing resource +++++++++++
     */

};



/*
+++++ Overloaded subscript operator to access data in linked-list based on index +++++
*/

T &SmartStack::operator [](size_t indx) const {

    return *(indexMap.map(indx)->value);
}

/*
+++++ Returns top of stack without popping it off. Return type is SharedPtr to object of type T +++++++
*/

T &SmartStack::top() const {

    // TODO: Ensure there's a head to begin with lest we seg. fault.

    return *head->value;
};