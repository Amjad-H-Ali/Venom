#ifndef SHARED_PTR_H

#define SHARED_PTR_H

/* * * * * * * * * * * * * * * * * * * * * * * *
 *											   *
 * 	Smart pointer that keeps track of shared   *
 *	resources and only deletes it if share 	   *
 *	count is 0.								   *
 *											   *
 * * * * * * * * * * * * * * * * * * * * * * * */

template<typename T>

class SharedPtr {

public:

	
    /* 	
     +++++ Main C'tor +++++
     */

    explicit SharedPtr(T *tPtr = nullptr);

    /*
     +++++ C'tor for Initialization to nullptr +++++
     */

    SharedPtr(const std::nullptr_t &nullObj);


    /*
     ++++++++++++++++
        Rule of 5
     ++++++++++++++++
     */


    /* 1	
     +++++++ Copy C'tor +++++++
     */

    SharedPtr(const SharedPtr &sharedPtrObj);


    /* 2
     ++++++ Destructor ++++++
     */

    ~SharedPtr();



    /* 3
     ++++++ Move C'tor ++++++
     */

    SharedPtr(SharedPtr&& ptrObj);


    /* 4
     ++++++ Copy Assignment ++++++
     */

    SharedPtr& operator =(const SharedPtr &ptrObj);

    /* 5
     +++++ Move Assignment +++++
     */

    SharedPtr& operator =(SharedPtr&& ptrObj);

    /*
     +++++ Assignment to nullptr +++++
     */

    SharedPtr& operator= (const std::nullptr_t &nullObj);


    /*
     ++++++++++++++++
        Overloads
     ++++++++++++++++
     */



    /*
     +++++ Overload Dereference Operator. +++++
     */

    T& operator* () const;

    /*
     +++++ Overload Arrow Operator. +++++
     */

    T* operator-> () const;

    /*
     +++++ Overload Comparison Operator. +++++
     */

    bool operator== (const std::nullptr_t &nullObj) const;

    bool operator== (const SharedPtr &ptrObj) const;

    /*
     +++++ Overload Not Comparison Operator. +++++
     */

    bool operator!= (const std::nullptr_t &nullObj) const;

    /*
     +++++ Bool Convesion +++++
     */

    operator bool() const;


private:

    /*
     +++++ Underlying pointer +++++
     */

	T *ptr;

	/*	
     +++++ Keeps track of how many instances share resource +++++
	 */

	unsigned *sharedBy;


	
   /*
    ++++++ Deletes resource and sharedBy counter if this  ++++++
    ++++++ instance is the only one sharing that resource.++++++
    */

    void cleanUp();

}; // SharedPtr

#endif