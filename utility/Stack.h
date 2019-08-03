#ifndef STACK_H

#define STACK_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * A Stack, implemented using a linked-list, that can  *
 * access elements in O(log n) time complexity.        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

template<typename T>

class SmartStack {

private:

	SharedPtr< Node<T> > head;

	size_t size = 0;

	/*
	 +++++ Uses a given index to map to Node that is located at that index.  ++++++
	 +++++ Allows for accessing a specific node in O(log n) time complexity, ++++++
	 +++++    rather than the O(n) time linked-list are known to have.		 ++++++				 
	 */ 	

	Trie< Node<T> > indexMap;  

public:

    /*
     +++++++ Main C'tor +++++++++++
     */

    SmartStack();

    /*
     +++++ Push T objects emplace. Takes in parameters that construct T object. +++++
     */
    template<typename ... Params>

    void push(Params&& ... params);

    /*
     +++++++ Pop object off stack +++++++++++
     */

    void pop();

  
    /*
    +++++ Overloaded subscript operator to access data in linked-list based on index +++++
    */

    T &operator [](size_t indx) const;

    /*
    +++++ Returns top of stack without popping it off. Return type is SharedPtr to object of type T +++++++
    */

    T &top() const;

}; // SmartStack


#endif