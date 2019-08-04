#include "Queue.h"

/* * * * * * * * * * * * * * * * * * * * * * * *
 *											   *
 * 	Queue, implemented using a linked-list,    *
 *	for FIFO growth and shrinkage in O(1)      *
 *  time complexity. Contains a head, tail,    *
 *  and _current pointer.                      *
 *											   *
 * * * * * * * * * * * * * * * * * * * * * * * */


/*
 ++++++ Main C'tor ++++++
 */

Queue::Queue()
    :head(nullptr), tail(nullptr), _current(nullptr)
{}

/*
 +++++ Inserts an object at end of Queue. Params: variable number of arguments  +++++
 +++++    that will be forwarded to T object constructor to create emplace.     +++++
 */

template<typename ... Params>

void Queue::enqueue(Params&& ... params) {

    /*
     ++++++ Create object of type T. Parameters' l-value/r-value +++++++
     ++++++ preserved while passing to T's C'tor. SharedPtr to T +++++++
     ++++++ stored in Node. Address of node stored in SharedPtr  +++++++
     */

    SharedPtr< Node<T> > newNode(new Node<T>(new T(std::forward<Params>(params)...)));

    
    /*
     +++++++ First Node in Queue. Assign all pointers to it. +++++++++
     */

    if(!head) {head = newNode; tail = newNode; _current = newNode;}

    /*
     +++++++ Append Node to Queue. +++++++++
     */

    else {

        tail->next = newNode;

        tail = newNode;
    }


}

/*
 +++++ Remove first object in Queue +++++
 */

void Queue::dequeue() {
    
    if(!head) return; // Ensure there is a head.

    SharedPtr< Node<T> > temp = head; // Temporarly store head for later.

    head = head->next; // Set new head.

    temp->next = nullptr; // Detach old head.

    if(_current == temp)
        _current = head; // Set current to new head if it was old head.
    /*
     +++++ SharedPtr deletes old head (temp) +++++
     */
}


/*
 +++++ Moves "_current" pointer a number of places ahead. +++++
 +++++ Params: Number of places to move in the Queue.     +++++
 */

inline void Queue::jump(unsigned places) {

    for(unsigned i = 0; _current && i < places; ++i, _current = _current->next);
};

/*
 ++++++ Returns Ptr of current object in Queue +++++++
 */

inline SharedPtr<T> Queue::current() const {

    if(!_current) return nullptr;

    return _current->value;
}

/*
 ++++++ Returns Ptr of first object in Queue +++++++
 */

inline SharedPtr<T> Queue::begin() const {

    if(!head) return nullptr;

    return head->value;
}

/*
 ++++++ Returns Ptr of last object in Queue +++++++
 */

inline SharedPtr<T> Queue::end() const {

    if(!tail) return nullptr;

    return tail->value;
}