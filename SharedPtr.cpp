/* 	
 +++++++ Main C'tor +++++++
 */

explicit SharedPtr::SharedPtr(T *tPtr = nullptr) 
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
	 ++++++++ If ptr is some resource, then we have a shared counter. ++++++++ 
	 ++++++++ After decrementing sharedBy and it's 0, then this was   ++++++++
	 ++++++++ the last instance pointing to that resource. So del.    ++++++++
	 */

    if(ptr && --(*sharedBy) == 0) { delete ptr; delete sharedBy;}

    /*
     +++++ An instance was destructed. So sharedBy was -- either way. +++++
     */
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

    shared = ptrObj.shared;

    ptrObj.shared = nullptr;

    /*
     +++++ Does not increment shared since Temp is DEL and this instance +++++
     +++++ created. sharedBy counter stolen from expiring obj.			 +++++
     */
};

/* 4
 ++++++ Copy Assignment ++++++
 */

SmartPtr& SharedPtr::operator =(const SmartPtr& ptrObj) {

};

/* 5
 ++++++ Move Assignment ++++++
 */

SmartPtr& SharedPtr::operator =(SmartPtr&& ptrObj) {

};


/* 
 ++++++ Overloads ++++++
 */


/*
 ++++++++++ Overload Dereference Operator. ++++++++++
 */

T &SharedPtr::operator *() const {
	return *ptr;
};

/*
 ++++++++ Overload Arrow Operator. ++++++++
 */

T *SharedPtr::operator ->() const {
	
	return ptr;
};
