#ifndef QUEUE_H

#define QUEUE_H

/* * * * * * * * * * * * * * * * * * * * * * * *
 *											   *
 * 	Queue, implemented using a linked-list,    *
 *	for FIFO growth and shrinkage in O(1)      *
 *  time complexity. Contains a head, tail,    *
 *  and _current pointer.                      *
 *											   *
 * * * * * * * * * * * * * * * * * * * * * * * */

template<typename T>

class Queue {

private:

	SharedPtr< Node<T> > head, 
			             tail, 
			            _current;

public:

	/*
	 ++++++ Main C'tor ++++++
	 */

	Queue();

	/*
	 +++++ Inserts an object at end of Queue. Params: variable number of arguments  +++++
	 +++++    that will be forwarded to T object constructor to create emplace.     +++++
	 */

	template<typename ... Params>

	void enqueue(Params&& ... params);

    /*
     +++++ Remove first object in Queue +++++
     */

    void dequeue();


	/*
	 +++++ Moves "_current" pointer a number of places ahead. +++++
	 +++++ Params: Number of places to move in the Queue.     +++++
	 */

	void jump(unsigned places);

	/*
	 ++++++ Returns Ptr of current object in Queue +++++++
	 */

	SharedPtr<T> current() const;

    /*
	 ++++++ Returns Ptr of first object in Queue +++++++
	 */

	SharedPtr<T> begin() const;

	/*
	 ++++++ Returns Ptr of last object in Queue +++++++
	 */

	SharedPtr<T> end() const;


}; // Queue

#endif