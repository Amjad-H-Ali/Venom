#ifndef SHARED_PTR_H

#define SHARED_PTR_H

/**********************************************
 *											  *
 * 	Smart pointer that keeps track of shared  *
 *	resources and only deletes it if share 	  *
 *	count is 0.								  *
 *											  *
 **********************************************/

template<typename T>

class SharedPtr {

public:

	/* 	
	 +++++++ Main C'tor +++++++
	 */

	explicit SharedPtr(T *tPtr = nullptr);

	/*
	 ++++++++ Rule of 5 ++++++++
	 */


	/* 1	
	 +++++++ Copy C'tor +++++++
	 */

	SharedPtr(const SharedPtr& sharedPtrObj);

	/* 2
	 ++++++ Destructor ++++++
	 */

	~SharedPtr();

	/* 3
	 ++++++ Move C'tor ++++++
	 */

    SmartPtr(SmartPtr&& ptrObj);

    /* 4
	 ++++++ Copy Assignment ++++++
	 */

    SmartPtr& operator =(const SmartPtr& ptrObj);

    /* 5
	 ++++++ Move Assignment ++++++
	 */
    SmartPtr& operator =(SmartPtr&& ptrObj);

	/* 
	 ++++++ Overloads ++++++
	 */

	/*
	 ++++++++++ Overload Dereference Operator. ++++++++++
	 */

	T &operator *() const;

	/*
	 ++++++++ Overload Arrow Operator. ++++++++
	 */

	T *operator ->() const;


	


private:

	T *ptr;

	/*	
     +++++++++++ Keeps track of how many pointers  +++++++++++
     +++++++++++ are sharing resource.             +++++++++++
	 */

	unsigned *sharedBy;


	
	/*
	 ++++++ Deletes resource and sharedBy counter if this ++++++
	 ++++++ instance is only one sharing that resource.   ++++++
	 */
    void cleanUp();

}; // SharedPtr

#endif