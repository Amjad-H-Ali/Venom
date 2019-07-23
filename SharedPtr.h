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

	SharedPtr(T *tPtr = nullptr);

	/*	
	 +++++++ Copy Constructor +++++++
	 */

	SharedPtr(SharedPtr& sharedPtrObj);

	/*
	 ++++++ Destructor ++++++
	 */

	~SharedPtr();

	/*
	 ++++++++++ Overload Dereference Operator. ++++++++++
	 */

	T &operator *();

	/*
	 ++++++++ Overload Arrow Operator. ++++++++
	 */

	T *operator ->();




private:

	T *ptr;

	/*	
     +++++++++++ Number of ptr(s) resource is shared by. +++++++++++
	 */

	unsigned sharedBy;

}; // SharedPtr

#endif