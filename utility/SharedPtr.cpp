/* 	
 +++++++ Main C'tor +++++++
 */

explicit SharedPtr::SharedPtr(const T *tPtr = nullptr) 
	:sharedBy(nullptr)
{
	/*
 	 ++++++++ If tPtr passed in is an actual resource and ++++++++
     ++++++++ not nullptr, initialize counter to 1. 	  ++++++++
 	 */

	if(tPtr) sharedBy = new unsigned(1);

	ptr = tPtr;
};


/*
 ++++++++ Rule of 5 ++++++++
 */


/* 1	
 +++++++ Copy C'tor +++++++
 */

SharedPtr::SharedPtr(const SharedPtr& sharedPtrObj) {

	/*	
	 +++++++ Copy resource and increment counter because another +++++++
	 +++++++ object now points to same resource. 				 +++++++					
	 */

	ptr = sharedPtrObj.ptr;

	sharedBy = sharedPtrObj.sharedBy;


	/*
	 ++++++ If ptr exist, then gaurenteed sharedBy exist and is 1 or greater. ++++++
	 */

	if(ptr) ++(*sharedBy);
};


/* 2
 ++++++ Destructor ++++++
 */

SharedPtr::~SharedPtr() {

	/*
	 +++++ sharedBy decremented. Resource deleted if instance +++++
	 +++++ is last one sharing resource.                      +++++ 
	*/

	cleanUp();
};



/* 3
 ++++++ Move C'tor ++++++
 */

SharedPtr::SmartPtr(SmartPtr&& ptrObj) {

    /*
     ++++++ Steal resource and counter and set expiring instance data ++++++
     ++++++ to nullptr. Temp obj is safe to DEL with no memory leaks. ++++++
     ++++++ It will not DEL resource shared by others.				  ++++++
     */

    ptr = ptrObj.ptr;

    ptrObj.ptr = nullptr;

    sharedBy = ptrObj.sharedBy;

    ptrObj.sharedBy = nullptr;

    /*
     +++++ Does not increment sharedBy since Temp is DEL and this instance +++++
     +++++ created. sharedBy counter stolen from expiring obj.			   +++++
     */
};


/* 4
 ++++++ Copy Assignment ++++++
 */

SmartPtr& SharedPtr::operator =(const SmartPtr& ptrObj) {

	/*
	 +++++ sharedBy decremented. Resource deleted if instance +++++
	 +++++ is last one sharing resource.                      +++++ 
	*/

	cleanUp()

    /*
     +++++ Copy resources. +++++
     */

    ptr = ptrObj.ptr;

    sharedBy = ptrObj.sharedBy;

    /*
     +++++ Increment as this instance also points to resource. +++++
     */

    if(ptr) ++(*sharedBy);

    return *this;
};

/* 5
 ++++++ Move Assignment ++++++
 */

SmartPtr& SharedPtr::operator =(SmartPtr&& ptrObj) {

	/*
	 +++++ sharedBy decremented. Resource deleted if instance +++++
	 +++++ is last one sharing resource.                      +++++ 
	*/

    cleanUp();

    

    /*
     +++++ Steal resource of Xpiring obj. +++++
     */

    ptr = ptrObj.ptr;

    sharedBy = ptrObj.sharedBy;

    ptrObj.ptr = nullptr;

    ptrObj.sharedBy = nullptr;

    return *this;
};


/* 
 ++++++ Overloads ++++++
 */


/*
 ++++++++++ Overload Dereference Operator. ++++++++++
 */

const T &SharedPtr::operator *() const {
	return *ptr;
};

/*
 ++++++++ Overload Arrow Operator. ++++++++
 */

const T *SharedPtr::operator ->() const {
	
	return ptr;
};


/*
 ++++++ Deletes resource and sharedBy counter if this ++++++
 ++++++ instance is only one sharing that resource.   ++++++
 */

void cleanUp() { 

	/*
	 +++++ sharedBy decremented. Resource deleted if instance +++++
	 +++++ is last one sharing resource.                      +++++ 
	*/

	if(ptr && --(*sharedBy) == 0) {delete ptr; delete sharedBy;}
}
